#pragma once
#include "utils.h"
#include "vertex.h"
#include "shader.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"


class TriMesh// : public Sprite
{
private:

	VertexBuffer *vertex_buffer_;

	ElementBuffer *element_buffer_;

	Shader *shader;

	glm::mat4 modelMatrix;

public:
	TriMesh();

	void Init(std::string modelPath);

	void Draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	//TriMesh();

	//void Translate(float x, float y, float z);
};
