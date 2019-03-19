#pragma once

#include "ggl.h"

class Light
{
protected:
	// ����ȷ�������Դ���� GL_LIGHT0 - GL_LIGHT7 �е���һ��
	GLenum mLightIdentifier;

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
 * ����ⲻ��˥��
 ***/
class DirectionLight: public Light
{
public:

	DirectionLight(GLenum light);

	/**
	 * �����Ĺ�Դ���������ȷ����ķ��򣬶��ǹ�Դλ��
	 */
	void SetPosition(float x, float y, float z);
};
