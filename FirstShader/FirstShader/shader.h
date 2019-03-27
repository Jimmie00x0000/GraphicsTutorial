#pragma once

#include "ggl.h"

/**
 * ����һ��Ҫ�������壬����ͨ��Ҫд���� VertexShader �� FragmentShader
 * ����Ķ�ȡ�����롢���ӣ����Խ�һ����װ
 */
class Shader
{
private:
	GLuint programId;

	GLint positionLocation;

	GLint colorLocation;

	GLint texcoordLocation;

	GLint normalLocation;

	GLint modelMatrixLocation;
	GLint viewMatrixLocation;
	GLint projectionMatrixLocation;

public:
	int GetPositionLocation() const { return positionLocation; }

	int GetColorLocation() const { return colorLocation; }

	int GetTexcoordLocation() const { return texcoordLocation; }

	int GetNormalLocation() const { return normalLocation; }
		
	void Init(const std::string& vs, const std::string& fs);

	void Bind(float *M, float *V, float *P);
};
