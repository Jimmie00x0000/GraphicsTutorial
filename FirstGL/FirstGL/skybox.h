#pragma once

#include "ggl.h"

class SkyBox final
{

private:
	GLuint mTextures[6];

	GLuint mFastDrawCall;

public:
	/**
	 * @param: ��պе�6��ͼƬ���ڵ�Ŀ¼·�� 
	 **/
	void Init(const char *imageDir);

	/** ������պ� **/
	void DrawCommand();

	void Draw();

};
