#pragma once

#include "ggl.h"

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