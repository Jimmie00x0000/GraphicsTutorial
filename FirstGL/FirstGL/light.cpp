#include "scene.h"

#include "light.h"


void DrawModel2()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS); 
	glColor4ub(255, 255, 255, 255); glVertex3d(-0.0f, -0.0f, -2.5f); // ��һ���������
	glColor4ub(255, 255, 255, 255); glVertex3d(-0.0f, +0.2f, -2.5f); // ��һ���������
	glColor4ub(255, 255, 255, 255); glVertex3d(0.2f, +0.2f, -2.5f); // ��һ���������
	glColor4ub(255, 255, 255, 255); glVertex3d(0.2f, 0.0f, -2.5f); // ��һ���������
	glEnd(); 
}

void EnableDirectionLight()
{
	DrawModel2();
	glEnable(GL_LIGHTING); // ���������㷨����ɫ���ı��λ��ڣ�û�з�����Ϣ�ᵼ�±��
	// OpenGL �����а�յ�ƣ��� 0 - 7
	glEnable(GL_LIGHT0); // ������һյ�ƣ�
	// ��Դ���꣬��������� (x, y, z, w) -> (x/w, y/w, z/w, 1)
	const GLfloat lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // ���� LIGHT0 ��λ��

}


void EnableDirectionAmbient()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LIGHT0); // ������һյ�ƣ�
	glEnable(GL_CULL_FACE); 
	const GLfloat lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // ���� LIGHT0 ��λ��

	const GLfloat whiteColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // ��ɫ��
	const GLfloat blackColor[] = {0.0f, 0.0f, 0.0f, 1.0f}; // ��ɫ�� 
	const GLfloat ambientMat[] = {0.07f, 0.07f, 0.07f, 1.0f}; // ���������ʵķ���ϵ��
	const GLfloat diffuseMat[] = {0.4f, 0.4f, 0.4f, 1.0f}; // ���������ʵ�������ϵ��
	const GLfloat specularMat[] = {0.9f, 0.9f, 0.9f, 1.0f}; // ���������ʵľ��淴��ϵ��

	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor); // ���û�����
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMat); // ��������Ի�����ķ���ϵ��

	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor); // ����������
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat); // ��������������ϵ��

	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor); // ���þ��淴��
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat); // �������澵�淴��ϵ��
	
	DrawModel2();
}

Light::Light()
{
	
}


void Light::SetAmbientColor(float r, float g, float b, float a)
{
	GLfloat ambientColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_AMBIENT, ambientColor);
}

void Light::SetDiffuseColor(float r, float g, float b, float a)
{
	GLfloat diffuseColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_DIFFUSE, diffuseColor);
}

void Light::SetSpecularColor(float r, float g, float b, float a)
{
	int ab = 0;
	int c = ab;
	GLfloat specularColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_SPECULAR, specularColor);
}

void Light::Enable()
{
	glEnable(GL_LIGHTING);
	glEnable(mLightIdentifier);
}

DirectionLight::DirectionLight(GLenum light)
{
}

void DirectionLight::SetPosition(float x, float y, float z)
{
	GLfloat pos[] = { x, y, z, 0 };
	glLightfv(mLightIdentifier, GL_POSITION, pos);
}

PointLight::PointLight(GLenum light)
{
	mLightIdentifier = light;
}

void PointLight::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat pos[] = { x, y, z, 1.00 };
	glLightfv(mLightIdentifier, GL_POSITION, pos);
}

void PointLight::SetConstantAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_CONSTANT_ATTENUATION, v);
}

void PointLight::SetLinearAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_LINEAR_ATTENUATION, v);
}

void PointLight::SetQuadricAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_QUADRATIC_ATTENUATION, v);
}

SpotLight::SpotLight(GLenum light) : PointLight(light)
{
}

void SpotLight::SetDirection(float x, float y, float z)
{
	float dir[] = { x, y, z };
	glLightfv(mLightIdentifier, GL_SPOT_DIRECTION, dir);
}

void SpotLight::SetExponent(float v)
{
	glLightf(mLightIdentifier, GL_SPOT_EXPONENT, v);
}

void SpotLight::SetCufoff(float v)
{
	glLightf(mLightIdentifier, GL_SPOT_CUTOFF, v);
}



