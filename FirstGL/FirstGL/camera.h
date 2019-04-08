#pragma once

#include "linearmath.h"

class Camera
{

private:
	/** ���λ�� **/
	Vector3f position_;

	/** ��������ĸ��� **/
	Vector3f view_center_;

	/** ���ͷ������ **/
	Vector3f up_;

	// ��������� XoZ ƽ���ϵ��ƶ�
	bool is_moving_left_;

	bool is_moving_right_;

	bool is_moving_forwards_;

	bool is_moving_backwards_;

public:
	Camera();
	
	void Update(float delta_time);

	void SetMovingLeft(const bool& l) { this->is_moving_left_ = l; }

	void SetMovingRight(const bool& l) { this->is_moving_right_ = l; }

	void SetMovingForward(const bool& l) { this->is_moving_forwards_= l; }

	void SetMovingBackward(const bool& l) { this->is_moving_backwards_ = l; }

	Vector3f GetPosition() const { return this->position_; }

	void Pitch(float angle);

	void Yaw(float angle);

	/**
	 * �����������Ƕ���ת�� �����λ�ò��䣬�൱��������ӵ�ı���
	 */
	void RotateView(float angle, float x, float y, float z);
};

