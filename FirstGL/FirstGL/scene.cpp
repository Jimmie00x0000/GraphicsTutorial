#include "scene.h"
#include "utils.h"
#include "skybox.h"
#include "model.h"
#include "ground.h"
#include "light.h"
#include "camera.h"
#include "particle.h"
#include <iostream>

DirectionLight light(GL_LIGHT0);
PointLight light1(GL_LIGHT1);
PointLight light2(GL_LIGHT2);
Ground ground;
SkyBox skyBox;
Model model;
Camera camera;
//Particle particle;

/**
 * ��Ļ����������������ϵԭ��
 * z ��ָ����Ļ����, ���� z ����Ҫ�踺ֵ
 */
void Init()
{
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	//std::cout << "Render: " << glGetString(GL_RENDER) << std::endl;
	// OpenGl ���ڵ�ǰ����ĸ��ͨ�� glMatrixMode ���õ�ǰ����� ģʽ
	glMatrixMode(GL_PROJECTION);
	// ?, �����Ŀ�߱ȣ� ������Կ����ľ��룬��Զ���Կ����ľ��� 
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.f);
	glMatrixMode(GL_MODELVIEW); // �л���ǰ����ģ���ӿھ���
	glLoadIdentity();
	skyBox.Init("Res/", &camera);
	//model.Init("Res/Box.obj");
	model.Init("Res/Dog.ply");
	ground.Init();

	light.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	light.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	light.SetPosition(0.0f, 1.0f, 0.0f);
	light1.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light1.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	light1.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	light1.SetPosition(0.0f, 0.0f, 0.0f); // ���Դ�ŵ�ԭ��
	light1.SetConstantAttenuation(0.1f);
	light1.SetLinearAttenuation(0.2f);
	// �ڶ������Դ
	light2.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light2.SetDiffuseColor(0.1f, 0.4f, 0.7f, 1.0f);
	light2.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	light2.SetPosition(0.0f, 0.0f, -20.0f); // 
	light2.SetConstantAttenuation(0.5f);
	light2.SetLinearAttenuation(0.2f);
	model.SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
	model.SetDiffuseMaterial(0.4f, 0.4f, 0.4f, 1.0f);
	model.SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);

}



void Draw()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	// ÿһ֡����֮ǰҪ�����ɫ����������Ȼ�����(��ʼ��Ϊ1.0������Զ)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const float frameTime = GetFrameTime();
	camera.Update(frameTime);

	//light.Enable();
	light1.Enable();
	light1.Update(camera.GetPosition().v1, camera.GetPosition().v2, camera.GetPosition().v3);
	light2.Enable();
	light2.Update(camera.GetPosition().v1, camera.GetPosition().v2, camera.GetPosition().v3);

	skyBox.Draw();
	ground.Draw();
	//glEnable(GL_DEPTH_TEST); // ��֤��������ᵲסԶ������
	model.Draw();
	//particle.Draw();
	// DrawModel();
}

void OnKeyDown(char code)
{
	switch (code)
	{
	case 'A':
		camera.SetMovingLeft(true);
		break;
	case 'S':
		camera.SetMovingBackward(true);
		break;
	case 'D':
		camera.SetMovingRight(true);
		break;
	case 'W':
		camera.SetMovingForward(true);
		break;
	}
}

void OnKeyUp(char code)
{
	switch (code)
	{
	case 'A':
		camera.SetMovingLeft(false);
		break;
	case 'S':
		camera.SetMovingBackward(false);
		break;
	case 'D':
		camera.SetMovingRight(false);
		break;
	case 'W':
		camera.SetMovingForward(false);
		break;
	}
}

void OnMouseMove(float deltaX, float deltaY)
{
	// �� x �Ử��������� y��ת����λ��ֵ���Ʊƽ� yaw �ĽǶ�
	float angleRotateByYAxis = deltaX / 1000.0f; 
	// �� y �Ử��������� x��ת����λ��ֵ���Ʊƽ� pitch �ĽǶ�
	float angleRotateByXAxis = deltaY / 1000.0f; 
	camera.Yaw(- angleRotateByYAxis);
	camera.Pitch(- angleRotateByXAxis);
}
