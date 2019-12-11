#pragma once

#include "ggl.h"

class Light {
private:

protected:
	// ����ȷ�������Դ���� GL_LIGHT0 - GL_LIGHT7 �е���һ��
	GLenum light_identifier_;

	bool enabled_;

	glm::vec4 position_;
	glm::vec4 ambient_rgba_;
	glm::vec4 diffuse_rgba_;
	glm::vec4 specular_rgba_;

	Light();

public:

	// ������
	void SetAmbientColor(float r, float g, float b, float a) {
		this->ambient_rgba_ = { r, g, b, a };
	}

	// ������
	void SetDiffuseColor(float r, float g, float b, float a) {
		this->diffuse_rgba_ = { r, g, b, a };
	}

	// ���淴��
	void SetSpecularColor(float r, float g, float b, float a) {
		this->specular_rgba_ = { r, g, b, a };
	}

	void Enable() {}
};

/**
 * ������������������Ϊ0�����´�������Զ��
 * �����*����˥��*
 ***/
class DirectionLight : public Light {
private:
	glm::vec4 direction_;

public:

	DirectionLight(GLenum light) {}

	/**
	 * �����Ĺ�Դ���������ȷ����ķ��򣬶��ǹ�Դλ��
	 */
	void SetPosition(float x, float y, float z) {
		this->direction_ = { x, y, z, 0 };
	}
};


/**
 * ���Դ��������˥����ԽԶ����Խ��
 */
class PointLight : public Light {
private:
	float position_[3];

public:
	PointLight(GLenum light) {}

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
