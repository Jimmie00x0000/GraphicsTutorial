#include "camera.h"
#include "ggl.h"
#include "iostream"

/** ��ʼ��ΪOpenGL Ĭ���ӿھ����״̬ **/
Camera::Camera() :
mPos(0.0f, 0.0f, 0.0f),
mViewCenter(0.0f, 0.0f, -1.0f),
mUp(0.0f, 1.0f, 0.0f),
movingLeft(false),
movingRight(false),
movingForwards(false),
movingBackwards(false)
{
}

void Camera::Update(float deltaTime)
{
	float moveSpeed = 2.0f;
	Vector3f forwardDirection = mViewCenter - mPos;
	forwardDirection.normalize();
	Vector3f rightDirection = forwardDirection.cross(mUp);
	rightDirection.normalize();

	if (movingLeft)
	{
		const auto& delta = rightDirection * deltaTime * moveSpeed;
		mPos = mPos - delta;
		mViewCenter = mViewCenter - delta;
	}
	if (movingRight)
	{
		const auto& delta = rightDirection * deltaTime * moveSpeed;
		mPos = mPos + delta;
		mViewCenter = mViewCenter + delta;
	}
	if (movingForwards)
	{
		const auto& delta = forwardDirection * deltaTime * moveSpeed;
		std::cout << "x: " << delta.position[0] << " y: " << delta.position[1] << " z: " << delta.position[2] << std::endl;
		mPos = mPos + delta;
		mViewCenter = mViewCenter + delta;
	}
	if (movingBackwards)
	{
		const auto& delta = forwardDirection * deltaTime * moveSpeed;
		std::cout << "x: " << delta.position[0] << " y: " << delta.position[1] << " z: " << delta.position[2] << std::endl;
		mPos = mPos - delta;
		mViewCenter = mViewCenter - delta;
	}
	glLoadIdentity();
	gluLookAt(mPos.position[0], mPos.position[1], mPos.position[2],
		mViewCenter.position[0], mViewCenter.position[1], mViewCenter.position[2],
		mUp.position[0], mUp.position[1], mUp.position[2]);
}

void Camera::Pitch(float angle)
{
	auto viewDirection = mViewCenter - mPos;
	viewDirection.normalize();
	auto rightDirection = viewDirection.cross(mUp);
	rightDirection.normalize();
	RotateView(angle, rightDirection.position[0], rightDirection.position[1], rightDirection.position[2]);
}

void Camera::Yaw(float angle)
{
	RotateView(angle, mUp.position[0], mUp.position[1], mUp.position[2]);
}

/**
 * �� (x,y,z) ��ת angle �Ƕ�
 */
void Camera::RotateView(float angle, float x, float y, float z)
{
	Vector3f viewDirection = mViewCenter - mPos;

	float C = cosf(angle);
	float S = sinf(angle);
	// �����������ת����
	Matrix33f matrix33(
		{x * x * (1 - C) + C, x * y * (1 - C) - z * S, x * z * (1 - C) + y * S,
	y * x * (1 - C) + z * S, y * y * (1 - C) + C, y * z * (1 - C) - x * S,
	z * x * (1 - C) - y * S, z * y * (1 - C) + x * S, z * z * (1 - C) + C});
	const auto& newDirection = matrix33 * viewDirection;
	mViewCenter = mPos + newDirection;
}



