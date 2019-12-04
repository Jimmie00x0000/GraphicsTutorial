#pragma once

#include "ggl.h"

class Light {
protected:
	// ����ȷ�������Դ���� GL_LIGHT0 - GL_LIGHT7 �е���һ��
	GLenum light_identifier_;

	Light();

public:

	// ������
	void SetAmbientColor(float r, float g, float b, float a);

	// ������
	void SetDiffuseColor(float r, float g, float b, float a);

	// ���淴��
	void SetSpecularColor(float r, float g, float b, float a);

	void Enable();

};

/**
 * ������������������Ϊ0�����´�������Զ��
 * �����*����˥��*
 ***/
class DirectionLight : public Light
{
public:

	DirectionLight(GLenum light);

	/**
	 * �����Ĺ�Դ���������ȷ����ķ��򣬶��ǹ�Դλ��
	 */
	void SetPosition(float x, float y, float z);
};


/**
 * ���Դ��������˥����ԽԶ����Խ��
 */
class PointLight : public Light
{
private:
	float position_[3];

public:
	PointLight(GLenum light);

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);

	// ���ó���˥��ϵ��
	void SetConstantAttenuation(float v);

	// ��������˥��ϵ��
	void SetLinearAttenuation(float v);

	// ���ö��η�˥��ϵ��
	void SetQuadricAttenuation(float v);

	/**
	 * �������������λ��
	 */
	void Update(float x, float y, float z);
};

// �۹��
class SpotLight : public PointLight
{
public:
	SpotLight(GLenum light);

	// �۹�Ʒ���
	void SetDirection(float x, float y, float z);

	// �۹��
	void SetExponent(float v);

	// ���䷶Χ
	void SetCufoff(float v);
};
