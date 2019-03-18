#include "scene.h"
#include "utils.h"
#include "skybox.h"
#include "model.h"

SkyBox skyBox;
Model model;

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
	skyBox.Init("Res/");
	//model.Init("Res/Box.obj");
	model.Init("Res/Dog.ply");
}

void DrawModel()
{
	glBegin(GL_QUADS); 
	glColor4ub(255, 50, 0, 255); glVertex3d(-0.0f, -0.0f, -2.5f); 

	glColor4ub(255, 50, 0, 255); glVertex3d(-0.0f, +0.2f, -2.5f); 

	glColor4ub(255, 50, 0, 255); glVertex3d(0.2f, +0.2f, -2.5f); 

	glColor4ub(255, 50, 0, 255); glVertex3d(0.2f, 0.0f, -2.5f); 
	// �����˵�һ���ı���

	glColor4ub(255, 250, 0, 255); glVertex3d(-0.0f, -0.0f, -3.5f); 

	glColor4ub(255, 250, 0, 255); glVertex3d(-0.0f, +0.2f, -3.5f); 

	glColor4ub(255, 250, 0, 255); glVertex3d(0.2f, +0.2f, -3.5f); 

	glColor4ub(255, 250, 0, 255); glVertex3d(0.2f, 0.0f, -3.5f); 
	// �����˵�һ���ı���
	glEnd(); 
}



void Draw()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	// ÿһ֡����֮ǰҪ�����ɫ����������Ȼ�����(��ʼ��Ϊ1.0������Զ)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	skyBox.DrawCommand();
	glEnable(GL_DEPTH_TEST); // ��֤��������ᵲסԶ������
	model.Draw();
	// DrawModel();
}
