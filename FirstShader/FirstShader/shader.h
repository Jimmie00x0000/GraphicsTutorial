#pragma once

#include "ggl.h"

/**
 * ����һ��Ҫ�������壬����ͨ��Ҫд���� VertexShader �� FragmentShader
 * ����Ķ�ȡ�����롢���ӣ����Խ�һ����װ
 */
class Shader
{
private:
	GLuint program_id_;

	GLint position_location_;

	GLint color_location_;

	GLint texcoord_location_;

	GLint normal_location_;

	GLint model_matrix_location_;
	GLint view_matrix_location_;
	GLint projection_matrix_location_;

public:
	int GetPositionLocation() const { return position_location_; }

	int GetColorLocation() const { return color_location_; }

	int GetTexcoordLocation() const { return texcoord_location_; }

	int GetNormalLocation() const { return normal_location_; }
		
	void Init(const std::string& vs, const std::string& fs);

	void Bind(float *M, float *V, float *P);
};
