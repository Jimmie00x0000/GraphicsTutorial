#include "scene.h"

// ����ļ���¼�� OpenGL �ľ���任

void DrawTriangleZero()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES); // ����Ҫ����ͼ�Σ�������
	glColor4ub(255, 255, 255, 255); // ��һ�������ɫ
	glVertex3d(-0.2f, -0.2f, -2.5f); // ��һ���������
	glColor4ub(255, 0, 0, 255); // �ڶ��������ɫ
	glVertex3d(0.2f, -0.2f, -2.5f); // �ڶ����������
	glColor4ub(0, 255, 0, 255);
	glVertex3d(0.f, 0.2f, -2.5f);
	glEnd(); // ����� 3 ���㣬����һ�������Σ���6���㣬��������������, ��ʱ�뷽��
	// ���������棺��ʱ�뷽����Ϊͼ�ε�����
}


void Draw2()
{
	DrawTriangleZero();
	glLoadIdentity();
	// �����ʼ��һ�������������������ƽ�У���ʱ�������������ת��������Ҳ��ת������
	// ԭ����ϵ�� (0, 0, 1) ��ת30�㣬��ѭ���ֶ���
	glRotatef(30.0, 0, 0, 1.); 

	glTranslatef(0.5f, 0.9f, 0.f); // ƽ������
}
