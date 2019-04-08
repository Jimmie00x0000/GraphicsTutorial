#pragma once

#include "ggl.h"

/** �����ļ����ݵ��ڴ� **/
unsigned char* LoadFile(const char* file_path, int& file_Size);

/** ���� BMP ͼƬ **/
unsigned char* DecodeBMP(unsigned char* bmp_data, int& width, int& height);

/** 
 * ������ά���� 
 * @param type: ��������
 * @return �����������ı�ʶ��
 **/
GLuint CreateTexture2D(unsigned char* pixel_data, int width, int height, GLenum type);

GLuint CreateTexture2DFromBmp(const char *bmp_Path);

GLuint CreateDisplayList(std::function<void()> foo);

/** ���ɳ������� **/
GLuint CreateProcedureTexture(int size);

/** ͳ����Ⱦÿһ֡��ʱ�䣬��Ҫ���� winmm.lib **/
float GetFrameTime();

