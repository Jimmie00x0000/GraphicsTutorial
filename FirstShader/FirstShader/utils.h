#pragma once

#include "ggl.h"
#include "Include/glm/gtx/string_cast.hpp"
#include "iostream"

/** �����ļ����ݵ��ڴ� **/
unsigned char* LoadFile(const char* file_path, int& file_size);

/** ���� BMP ͼƬ **/
unsigned char* DecodeBMP(unsigned char* bmp_data, int& width, int& height);

/**
 * ������ά����
 * @param type: ��������
 * @return �����������ı�ʶ��
 **/
GLuint CreateTexture2D(unsigned char* pixelData, int with, int height, GLenum type);

GLuint CreateTexture2DFromBmp(const char *bmp_path);

GLuint CreateDisplayList(std::function<void()> foo);

/** ���ɳ������� **/
GLuint CreateProcedureTexture(int size);

/** ͳ����Ⱦÿһ֡��ʱ�䣬��Ҫ���� winmm.lib **/
float GetFrameTime();


/**
 * ���� shader
 * @param shader_type: �� VertexShader ���� FragmentShader
 * @param shader_code: d
 */
GLuint CompileShader(GLenum shader_type, const char *shader_code);

/**
 * ���� vertexShader �� fragmentShader
 * @param vs_shader: vertex shader
 * @param fs_shader: fragment shader
 */
GLuint CreateShaderProgram(GLuint vs_shader, GLuint fs_shader);

/**
 * ���� Buffer Object
 * @param buffer_type ����������
 * @param size �������Ĵ�С
 * @param usage static_draw ���� dynamic_draw
 * @param data ���������
 */
GLuint CreateBufferObject(GLenum buffer_type, GLsizeiptr size, GLenum usage, void *data = nullptr);

template<typename T>
void PrintGLMMatrix(T const& m, const std::string  prompt = "")
{
	// ������ת������������۲�
	const auto tm = glm::transpose(m);
	std::string str = glm::to_string(tm);
	std::string log = prompt;
	int prev_index = 0;
	for (int i = 0; i < str.length(); i ++)
	{
		if (str[i] == '(' && prev_index == 0) {
			log += std::string(str.begin() + prev_index, str.begin() + i + 1);
			log += "\n";
			prev_index = i + 1;
		} else if (i + 1 < str.length() && str[i] == ')' && str[i + 1] == ',')
		{
			log += std::string(str.begin() + prev_index, str.begin() + i + 2);
			log += "\n";
			prev_index = i + 2;
		}
	}
	log += std::string(str.begin() + prev_index,str.end());
	std::cout << log << std::endl;
}
