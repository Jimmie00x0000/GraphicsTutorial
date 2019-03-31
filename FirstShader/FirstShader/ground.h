#pragma once

#include "utils.h"
#include "vertex.h"
#include "shader.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"

class Ground
{
private:
	//GLuint vbo;
	VertexBuffer *buffer;
	Shader *shader;
	glm::mat4 modelMatrix;

public:
	// �������ݣ��������� Shader
	void Init();

	void Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
};

