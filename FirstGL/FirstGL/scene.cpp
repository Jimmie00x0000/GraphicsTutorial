#include  "scene.h"

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
}


void Draw()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES); // ����Ҫ����ͼ�Σ�������
	glColor4ub(255, 255, 255, 255); // ��һ�������ɫ
	glVertex3d(-0.2f, -0.2f, -1.5f); // ��һ���������
	glColor4ub(255, 0, 0, 255); // �ڶ��������ɫ
	glVertex3d(0.2f, -0.2f, -1.5f); // �ڶ����������
	glColor4ub(0, 255, 0, 255);
	glVertex3d(0.f, 0.2f, -1.5f);
	glEnd(); // ����� 3 ���㣬����һ�������Σ���6���㣬��������������, ��ʱ�뷽��
	// ���������棺��ʱ�뷽����Ϊͼ�ε�����
}