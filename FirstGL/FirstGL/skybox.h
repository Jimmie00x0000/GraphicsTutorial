#pragma once

#include "ggl.h"
#include "camera.h"

class SkyBox final
{

private:
	GLuint textures_[6];

	GLuint fast_draw_call_;

	Camera* curr_camera_;

public:
	SkyBox();

	/**
	 * @param: ��պе�6��ͼƬ���ڵ�Ŀ¼·�� 
	 **/
	void Init(const char *image_dir, Camera *camera);

	/** ������պ� **/
	void DrawCommand();

	void Draw();

};
