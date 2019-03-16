#include "utils.h"

unsigned char* DecodeBMP(unsigned char* bmpData, int& width, int& height)
{
	if (0x4D42 == *reinterpret_cast<unsigned short*>(bmpData))
	{
		auto pixelDataOffset = *reinterpret_cast<int*>(bmpData + 10);
		width = *reinterpret_cast<int*>(bmpData + 18);
		height = *reinterpret_cast<int*>(bmpData + 22);
		auto bmpImgData = bmpData + pixelDataOffset;
		// BGR -> RGB
		for (int i = 0; i < width * height * 3; i += 3)
		{
			unsigned char temp = bmpImgData[i];
			bmpImgData[i] = bmpImgData[i + 2];
			bmpImgData[i + 2] = temp;
		}
		return bmpImgData;
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
	// ����ָ�����˷�ʽ�� �ڶ�������������Ϊ GL_REPEAT, UV ������ 1.0�� ���ظ���������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // UV���곬��1.0��ô�죬 ȥ����߽磨1.0����ȡ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // UV���곬��1.0��ô�� 
	// ���ڴ����ͼƬ���ݿ������Դ���
	// �ڶ������� 0�� ��ָ mipmap �� level
	// border ����Ϊ 0
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0); // ���õ�ǰ����Ϊ0���������Ƶ�ǰ����ĸ��
	return texture;
}

GLuint CreateTexture2DFromBmp(const char *bmpPath)
{
	int nFileSize = 0;
	unsigned char *bmpFileData = LoadFile(bmpPath, nFileSize);
	if (bmpFileData == nullptr)
	{
		fprintf(stderr, "Error, cannot open file.\n");
		return 0; // �������� 0 �ź�ɫ����Ԫ
	}
	int width = 0, height = 0;
	unsigned char *bmpImageData = DecodeBMP(bmpFileData, width, height);
	if (width <= 0 || height <= 0)
	{
		fprintf(stderr, "Error, cannot decode image.\n");
		delete bmpFileData;
		return 0;
	}

	GLuint textureID = CreateTexture2D(bmpImageData, width, height, GL_RGB);
	delete bmpFileData;
	return textureID;
}

/**
 * �����л���ָ�glBegin(xxxx)) �������ʾ�б�
 */
GLuint CreateDisplayList(std::function<void()> foo)
{
	GLuint displayList = glGenLists(1); // ���� OpenGL ����ʾ�б�
	glNewList(displayList, GL_COMPILE);
	foo();
	glEndList();
	return displayList;
}
