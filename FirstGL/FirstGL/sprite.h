#pragma once
#include "ggl.h"

class Sprite
{
protected:
	GLfloat ambient_material_[4];

	GLfloat diffuse_material_[4];

	GLfloat specular_material_[4];

public:

	Sprite();

	virtual ~Sprite() = default;

	// ����ģ�ͱ�����ʵĻ����ⷴ��ϵ��
	void SetAmbientMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	// ���ò��ʵ������䷴��ϵ��
	void SetDiffuseMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	// ���þ��淴��ķ���ϵ��
	void SetSpecularMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual void Draw() = 0;
};
