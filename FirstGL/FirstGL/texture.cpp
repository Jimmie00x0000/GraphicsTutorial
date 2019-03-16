#include  "scene.h"
#include  "utils.h"

GLuint texture;

// ����ļ���¼�� OpenGL ��������ͼ��ʵ��

// �� Init() ����������������
void DoAfterInit()
{
	// ����ͼƬ����
	texture = CreateTexture2DFromBmp("Res/Texture.bmp");
}

void DrawModelWithUV()
{
	glBegin(GL_QUADS); 
	// ��һ��������꣬ ��ɫ����������
	glColor4ub(255, 255, 255, 255); 
	glVertex3d(-0.0f, -0.0f, -2.5f); 
	glTexCoord2f(0.0f, 0.0f);
	// �ڶ���������꣬ ��ɫ����������
	glColor4ub(255, 255, 255, 255); 
	glVertex3d(-0.0f, +0.2f, -2.5f); 
	glTexCoord2f(0.0f, 1.0f);
	// ������������꣬ ��ɫ����������
	glColor4ub(255, 255, 255, 255); 
	glVertex3d(0.2f, +0.2f, -2.5f); 
	glTexCoord2f(1.0f, 1.0f);
	// ���ĸ�������꣬ ��ɫ����������
	glColor4ub(255, 255, 255, 255); 
	glVertex3d(0.2f, 0.0f, -2.5f); 
	glTexCoord2f(1.0f, 0.0f);
	glEnd(); 
}


void DrawWithTexture()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D); // ��������
	glBindTexture(GL_TEXTURE_2D, texture);
	// ģ�ͱ������ɫ��Ҫ�ǰ�ɫ�����������ɫ��������
	DrawModelWithUV();
}

