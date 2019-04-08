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
	const GLfloat light_pos[] = {0.0f, 1.0f, 0.0f, 0.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); // ���� LIGHT0 ��λ��

}


void EnableDirectionAmbient()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LIGHT0); // ������һյ�ƣ�
	glEnable(GL_CULL_FACE); 
	const GLfloat lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // ���� LIGHT0 ��λ��

	const GLfloat white_color[] = {1.0f, 1.0f, 1.0f, 1.0f}; // ��ɫ��
	const GLfloat black_color[] = {0.0f, 0.0f, 0.0f, 1.0f}; // ��ɫ�� 
	const GLfloat ambient_mat[] = {0.07f, 0.07f, 0.07f, 1.0f}; // ���������ʵķ���ϵ��
	const GLfloat diffuse_mat[] = {0.4f, 0.4f, 0.4f, 1.0f}; // ���������ʵ�������ϵ��
	const GLfloat specular_mat[] = {0.9f, 0.9f, 0.9f, 1.0f}; // ���������ʵľ��淴��ϵ��

	glLightfv(GL_LIGHT0, GL_AMBIENT, white_color); // ���û�����
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_mat); // ��������Ի�����ķ���ϵ��

	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_color); // ����������
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_mat); // ��������������ϵ��

	glLightfv(GL_LIGHT0, GL_SPECULAR, white_color); // ���þ��淴��
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_mat); // �������澵�淴��ϵ��
	
	DrawModel2();
}

Light::Light()
{
	
}


void Light::SetAmbientColor(float r, float g, float b, float a)
{
	GLfloat ambient_color[] = { r, g, b, a };
	glLightfv(light_identifier_, GL_AMBIENT, ambient_color);
}

void Light::SetDiffuseColor(float r, float g, float b, float a)
{
	GLfloat diffuse_color[] = { r, g, b, a };
	glLightfv(light_identifier_, GL_DIFFUSE, diffuse_color);
}

void Light::SetSpecularColor(float r, float g, float b, float a)
{
	GLfloat specular_color[] = { r, g, b, a };
	glLightfv(light_identifier_, GL_SPECULAR, specular_color);
}

void Light::Enable()
{
	glEnable(GL_LIGHTING);
	glEnable(light_identifier_);
}

DirectionLight::DirectionLight(GLenum light)
{
}

void DirectionLight::SetPosition(float x, float y, float z)
{
	GLfloat pos[] = { x, y, z, 0 };
	glLightfv(light_identifier_, GL_POSITION, pos);
}

PointLight::PointLight(GLenum light)
{
	light_identifier_ = light;
	position_[0] = 0.0;
	position_[1] = 0.0;
	position_[2] = 0.0;
}

void PointLight::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	position_[0] = x;
	position_[1] = y;
	position_[2] = z;
}

void PointLight::SetConstantAttenuation(float v)
{
	glLightf(light_identifier_, GL_CONSTANT_ATTENUATION, v);
}

void PointLight::SetLinearAttenuation(float v)
{
	glLightf(light_identifier_, GL_LINEAR_ATTENUATION, v);
}

void PointLight::SetQuadricAttenuation(float v)
{
	glLightf(light_identifier_, GL_QUADRATIC_ATTENUATION, v);
}

void PointLight::Update(float x, float y, float z)
{
	GLfloat pos[] = {position_[0] - x, position_[1] - y, position_[2] - z, 1.00 };
	glLightfv(light_identifier_, GL_POSITION, pos);
}

SpotLight::SpotLight(GLenum light) : PointLight(light)
{
}

void SpotLight::SetDirection(float x, float y, float z)
{
	float dir[] = { x, y, z };
	glLightfv(light_identifier_, GL_SPOT_DIRECTION, dir);
}

void SpotLight::SetExponent(float v)
{
	glLightf(light_identifier_, GL_SPOT_EXPONENT, v);
}

void SpotLight::SetCufoff(float v)
{
	glLightf(light_identifier_, GL_SPOT_CUTOFF, v);
}



