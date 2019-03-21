#pragma once

#include "linearmath.h"

class Camera
{

private:
	/** 相机位置 **/
	Vector3f mPos;

	/** 相机看向哪个点 **/
	Vector3f mViewCenter;

	/** 相机头顶向量 **/
	Vector3f mUp;

	// 控制相机在 XoZ 平面上的移动
	bool movingLeft;

	bool movingRight;

	bool movingForwards;

	bool movingBackwards;

public:
	Camera();
	
	void Update(float deltaTime);

	void SetMovingLeft(const bool& l) { this->movingLeft = l; }

	void SetMovingRight(const bool& l) { this->movingRight = l; }

	void SetMovingForward(const bool& l) { this->movingForwards= l; }

	void SetMovingBackward(const bool& l) { this->movingBackwards = l; }

	Vector3f GetPosition() const { return this->mPos; }

	void Pitch(float angle);

	void Yaw(float angle);

	/**
	 * 让摄像机任意角度旋转， 相机的位置不变，相当于相机的视点改变了
	 */
	void RotateView(float angle, float x, float y, float z);
};

