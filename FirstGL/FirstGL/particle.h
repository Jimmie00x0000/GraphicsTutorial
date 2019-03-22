#pragma once

#include "ggl.h"
#include "linearmath.h"

class Particle
{
private:
	GLuint mTexture;

	// ����λ��
	Vector3f mPosition;

	// ���Ӵ�С
	float mHalfSize;

public:
	Particle();

	void Draw();

	GLuint getTexture() const { return mTexture; }

	Vector3f getPosition() const { return mPosition; }

	float getHalfSize() const { return mHalfSize; }
};

