#include "utils.h"
#include "io.h"
#include <iostream>
#include <unordered_set>

GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}

unsigned char* LoadFile(const char* file_path, int& file_size) {
	unsigned char *file_content = nullptr;
	file_size = 0;

	FILE *fp = fopen(file_path, "rb");
	if (fp == nullptr)
	{
		std::cerr << "Warning: Fail to open file: " << file_path << std::endl;
		return file_content;
	}
	fseek(fp, 0, SEEK_END); // �ƶ��ļ�ָ�뵽β��
	int nlen = ftell(fp);
	if (nlen > 0)
	{
		rewind(fp); // �Ƶ�ͷ��
		file_content = new unsigned char[nlen + 1];
		fread(file_content, sizeof(unsigned char), nlen, fp);
		file_content[nlen] = 0;
		file_size = nlen;
	}
	fclose(fp);
	return file_content;
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

GLuint CreateTexture2DFromImage(const char *bmp_path) {
	auto width = 0, height = 0;
	unsigned char *bmp_image_data = nullptr;
	LoadRGBImage(bmp_path, bmp_image_data, width, height);
	//= DecodeBMP(bmpFileData, width, height);
	if (width <= 0 || height <= 0) {
		fprintf(stderr, "Error, cannot decode image.\n");
		delete bmp_image_data;
		return 0;
	}
	// std::cerr << "Debug: load image, width " << width << ", height " << height << std::endl;

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
	glCheckError();
	return buffer_object;
}

void ConvertFaces2Edges( ElementBuffer& face_buffer, ElementBuffer& target_buffer)
{
	// ......
	using namespace std;
	// declare equal and hash for customized struct
	auto edge_hash = [](const Edge& edge) {return 31 * edge.vi + edge.vj; };
	auto edge_equal = [](const Edge& lhs, const Edge& rhs) {
		return (lhs.vi == rhs.vi && lhs.vj == rhs.vj) || (lhs.vi == rhs.vj && lhs.vj == rhs.vi);
	};
	// use a hashset to skip duplicate edges when visiting edges in Graph
	unordered_set<Edge, decltype(edge_hash), decltype(edge_equal)> edges(20, edge_hash, edge_equal);
	for (int i = 0; i < face_buffer.GetLength() / 3; i++) {
		edges.insert({ face_buffer.GetBuffer()[i * 3 + 0], face_buffer.GetBuffer()[i * 3 + 1] });
		edges.insert({ face_buffer.GetBuffer()[i * 3 + 0], face_buffer.GetBuffer()[i * 3 + 2] });
		edges.insert({ face_buffer.GetBuffer()[i * 3 + 2], face_buffer.GetBuffer()[i * 3 + 1] });
	}
	target_buffer.SetBufferLength(edges.size() * 2);
	int edge_i = 0;
	for (auto edge : edges) {
		target_buffer.GetBuffer()[edge_i + 0] = edge.vi;
		target_buffer.GetBuffer()[edge_i + 1] = edge.vj;
		edge_i += 2;
	}
	// ......
}
