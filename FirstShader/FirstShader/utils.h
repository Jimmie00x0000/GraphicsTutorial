#pragma once

#include "ggl.h"
#include "Include/glm/gtx/string_cast.hpp"
#include "iostream"

/** �����ļ����ݵ��ڴ� **/
unsigned char* LoadFile(const char* filePath, int& fileSize);

/** ���� BMP ͼƬ **/
unsigned char* DecodeBMP(unsigned char* bmpData, int& width, int& height);

/**
 * ������ά����
 * @param type: ��������
 * @return �����������ı�ʶ��
 **/
GLuint CreateTexture2D(unsigned char* pixelData, int with, int height, GLenum type);

GLuint CreateTexture2DFromBmp(const char *bmpPath);

GLuint CreateDisplayList(std::function<void()> foo);

/** ���ɳ������� **/
GLuint CreateProcedureTexture(int size);

/** ͳ����Ⱦÿһ֡��ʱ�䣬��Ҫ���� winmm.lib **/
float GetFrameTime();


/**
 * ���� shader
 * @param shaderType: �� VertexShader ���� FragmentShader
 * @param shaderCode: d
 */
GLuint CompileShader(GLenum shaderType, const char *shaderCode);

/**
 * ���� vertexShader �� fragmentShader
 * @param vsShader: vertex shader
 * @param fsShader: fragment shader
 */
GLuint CreateShaderProgram(GLuint vsShader, GLuint fsShader);

/**
 * ���� Buffer Object
 * @param bufferType ����������
 * @param size �������Ĵ�С
 * @param usage static_draw ���� dynamic_draw
 * @param data ���������
 */
GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void *data = nullptr);

template<typename T>
void printGLMMatrix(T const& m, const std::string  prompt = "")
{
	// ������ת������������۲�
	const auto tm = glm::transpose(m);
	std::string str = glm::to_string(tm);
	std::string log = prompt;
	//log += "???";
	int prevIndex = 0;
	for (int i = 0; i < str.length(); i ++)
	{
		if (str[i] == '(' && prevIndex == 0) {
			log += std::string(str.begin() + prevIndex, str.begin() + i + 1);
			log += "\n";
			prevIndex = i + 1;
		} else if (i + 1 < str.length() && str[i] == ')' && str[i + 1] == ',')
		{
			log += std::string(str.begin() + prevIndex, str.begin() + i + 2);
			log += "\n";
			prevIndex = i + 2;
		}
	}
	log += std::string(str.begin() + prevIndex,str.end());
	std::cout << log << std::endl;
}
