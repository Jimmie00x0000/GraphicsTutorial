#include "utils.h"
#include "io.h"
#include "iostream"


unsigned char* DecodeBMP(unsigned char* bmp_data, int& width, int& height)
{
	if (0x4D42 == *reinterpret_cast<unsigned short*>(bmp_data))
	{
		const auto pixel_data_offset = *reinterpret_cast<int*>(bmp_data + 10);
		width = *reinterpret_cast<int*>(bmp_data + 18);
		height = *reinterpret_cast<int*>(bmp_data + 22);
		const auto bmp_img_data = bmp_data + pixel_data_offset;
		// BGR -> RGB
		for (int i = 0; i < width * height * 3; i += 3)
		{
			unsigned char temp = bmp_img_data[i];
			bmp_img_data[i] = bmp_img_data[i + 2];
			bmp_img_data[i + 2] = temp;
		}
		return bmp_img_data;
	}
	return nullptr;
}

GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type)
{
	GLuint texture;
	glGenTextures(1, &texture); // ���� 1 �������ַ
	glBindTexture(GL_TEXTURE_2D, texture); // 2d ���� 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // �����С��ô�죬���Բ�ֵ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // ���Բ�ֵ
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // UV���곬��1.0��ô�죬 ȥ����߽磨1.0����ȡ
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // UV���곬��1.0��ô�� 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // UV���곬��1.0��ô�죬�ظ����� 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // UV���곬��1.0��ô�� 
	// ���ڴ����ͼƬ���ݿ������Դ���
	// �ڶ������� 0�� ��ָ mipmap �� level
	// border ����Ϊ 0
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0); // ���õ�ǰ����Ϊ0���������Ƶ�ǰ����ĸ��
	return texture;
}

GLuint CreateTexture2DFromBmp(const char *bmp_path)
{
	int n_file_size = 0;
	const auto bmp_file_data = LoadFile(bmp_path, n_file_size);
	if (bmp_file_data == nullptr)
	{
		fprintf(stderr, "Error, cannot open file.\n");
		return 0; // �������� 0 �ź�ɫ����Ԫ
	}
	auto width = 0, height = 0;
	unsigned char *bmp_image_data = nullptr;
	LoadRGBImage(bmp_path, bmp_image_data, width, height);
	//= DecodeBMP(bmpFileData, width, height);
	if (width <= 0 || height <= 0)
	{
		fprintf(stderr, "Error, cannot decode image.\n");
		delete bmp_file_data;
		return 0;
	}

	const GLuint texture_id = CreateTexture2D(bmp_image_data, width, height, GL_RGB);
	//	delete bmpFileData;
	delete bmp_image_data;
	return texture_id;
}

/**
 * �����л���ָ�glBegin(xxxx)) �������ʾ�б�
 */
GLuint CreateDisplayList(std::function<void()> foo)
{
	const GLuint display_list = glGenLists(1); // ���� OpenGL ����ʾ�б�
	glNewList(display_list, GL_COMPILE);
	foo();
	glEndList();
	return display_list;
}

// �������� size x size ������
GLuint CreateProcedureTexture(int size)
{
	unsigned char *image_data = new unsigned char[size * size * 4];
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			int i = (x + y * size) * 4;
			image_data[i + 0] = 255;
			image_data[i + 1] = 255;
			image_data[i + 2] = 255;
			image_data[i + 3] = 255;
		}
	}
	GLuint texture = CreateTexture2D(image_data, size, size, GL_RGBA);
	delete[] image_data;
	return texture;
}

float GetFrameTime()
{
	static unsigned long latest_time = 0;
	static unsigned long time_since_boot = 0;
	time_since_boot = timeGetTime();
	const unsigned long frame_time = latest_time == 0 ? 0 : time_since_boot - latest_time;
	latest_time = time_since_boot;
	return static_cast<float>(frame_time) / 1000.0f;
}

GLuint CompileShader(const GLenum shader_type, const char* shader_code)
{
	GLuint shader = glCreateShader(shader_type);
	// �ڶ������� 1 ��ʾ�� shader�ļ������ݷ�Ϊ���ٸ��ַ�����һ������ĸ������� null
	// shader �ļ��п��Է�Ϊ����ַ���, �����Ļ������ĸ�������һ�����飬����ÿ���ַ����ĳ���
	glShaderSource(shader, 1, &shader_code, nullptr);
	glCompileShader(shader);// ���Կ��������� shader�����������ʱ��������£�
	GLint compile_result = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result); // ��ȡ������

	if (compile_result == GL_FALSE)
	{
		char sz_log[1024] = { 0 };
		GLsizei log_length = 0;
		glGetShaderInfoLog(shader, 1024, &log_length, sz_log);
		std::cerr << "Fail to compile shader: " << shader_code << " , log: " << sz_log << std::endl;
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}

GLuint CreateShaderProgram(const GLuint vs_shader, const GLuint fs_shader)
{
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vs_shader);
	glAttachShader(program_id, fs_shader);
	// ��������shader
	glLinkProgram(program_id);
	glDetachShader(program_id, vs_shader);
	glDetachShader(program_id, fs_shader);
	GLint n_result = GL_TRUE;
	glGetProgramiv(program_id, GL_LINK_STATUS, &n_result);
	if (n_result == GL_FALSE) // ����ʧ�ܣ��ͷ���Դ����ӡ��־
	{
		char sz_log[1024] = { 0 };
		GLsizei log_length = 0;
		glGetShaderInfoLog(program_id, 1024, &log_length, sz_log);
		std::cerr << "Fail to link program, log: " << sz_log << std::endl;
		glDeleteProgram(program_id);
		program_id = 0;
	}
	return program_id;
}

GLuint CreateBufferObject(const GLenum buffer_type, GLsizeiptr size, GLenum usage, void* data)
{
	GLuint buffer_object;
	glGenBuffers(1, &buffer_object);
	glBindBuffer(buffer_type, buffer_object);
	glBufferData(buffer_type, size, data, usage);
	// ���õ�ǰ������ָ��
	glBindBuffer(buffer_type, 0);
	return buffer_object;
}
