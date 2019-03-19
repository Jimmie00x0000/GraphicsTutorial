#pragma once
#include "ggl.h"

class Sprite
{
protected:
	GLfloat mAmbientMaterial[4];

	GLfloat mDiffuseMaterial[4];

	GLfloat mSpecularMaterial[4];

public:

	Sprite();

	virtual ~Sprite()
	{
	}

	// ����ģ�ͱ�����ʵĻ����ⷴ��ϵ��
	void SetAmbientMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	// ���ò��ʵ������䷴��ϵ��
	void SetDiffuseMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	// ���þ��淴��ķ���ϵ��
	void SetSpecularMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual void Draw() = 0;
};
