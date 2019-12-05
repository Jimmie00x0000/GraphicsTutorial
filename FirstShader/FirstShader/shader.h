#pragma once

#include "ggl.h"
#include <unordered_map>

struct UniformTexture
{
	GLint location_; // ��������Ĳ��

	GLuint texture_; // �����Ψһ��ʶ��

	UniformTexture(): location_(-1), texture_(0){}
};

/**
 * ��ʾ shader �ļ���һ�� uniform vec4 ���͵ı���
 */
struct UniformVector4f
{
	GLint location_; // ������Ӧ���

	float value_[4];

	UniformVector4f();

	UniformVector4f(float x, float y, float z, float w, GLint location);
};

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

	/** ���� shader �е� vec4 ���͵ı����� **/
	std::unordered_map<std::string, UniformVector4f*> vec4_map_;

	std::unordered_map<std::string, UniformTexture*> textures_map_;

public:
	Shader() = default;
	Shader(const Shader&);
	Shader& operator= (const Shader&);

	~Shader();

	int GetProgramId() const { return program_id_; }

	int GetPositionLocation() const { return position_location_; }

	int GetColorLocation() const { return color_location_; }

	int GetTexcoordLocation() const { return texcoord_location_; }

	int GetNormalLocation() const { return normal_location_; }
		
	void Init(const std::string& vs, const std::string& fs);

	void Bind(float *M, float *V, float *P);

	void SetVector4(const std::string & name, float x, float y, float z, float w);

	void SetTexture(const std::string & name, const std::string & texture_image_path);
};
