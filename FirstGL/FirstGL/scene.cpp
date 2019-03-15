#include  "scene.h"
#include  "utils.h"

GLuint texture;

/**
 * ��Ļ����������������ϵԭ��
 * z ��ָ����Ļ����, ���� z ����Ҫ�踺ֵ
 */
void Init()
{
	// OpenGl ���ڵ�ǰ����ĸ��ͨ�� glMatrixMode ���õ�ǰ����� ģʽ
	glMatrixMode(GL_PROJECTION);
	// ?, �����Ŀ�߱ȣ� ������Կ����ľ��룬��Զ���Կ����ľ��� 
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.f);
	glMatrixMode(GL_MODELVIEW); // �л���ǰ����ģ���ӿھ���
	glLoadIdentity();

	//// ����ͼƬ����
	//int nFileSize = 0;
	//unsigned char *bmpFileContent = LoadFile("Res/Texture.bmp", nFileSize);
	//int bmpWidth = 0, bmpHeight = 0;
	//unsigned char *bmpImageData = DecodeBMP(bmpFileContent, bmpWidth, bmpHeight);

	//if (bmpWidth > 0 && bmpHeight > 0)
	//{
	//	fprintf(stdout, "Init OK.");
	//	texture = CreateTexture2D(bmpImageData, bmpWidth, bmpHeight, GL_RGB);
	//} else
	//{
	//	fprintf(stderr, "Cannot decode bmp file.\n");
	//}
	texture = CreateTexture2DFromBmp("Res/Texture.bmp");
}

void DrawModel()
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


void Draw()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D); // ��������
	glBindTexture(GL_TEXTURE_2D, texture);
	// ģ�ͱ������ɫ��Ҫ�ǰ�ɫ�����������ɫ��������
	DrawModel();
}
