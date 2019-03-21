#pragma once

#include "ggl.h"
#include "camera.h"

class SkyBox final
{

private:
	GLuint mTextures[6];

	GLuint mFastDrawCall;

	Camera* currCamera = nullptr;

public:
	/**
	 * @param: ��պе�6��ͼƬ���ڵ�Ŀ¼·�� 
	 **/
	void Init(const char *imageDir, Camera *camera);

	/** ������պ� **/
	void DrawCommand();

	void Draw();

};
