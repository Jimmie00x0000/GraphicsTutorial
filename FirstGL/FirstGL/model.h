#pragma once

#include "ggl.h"
#include "sprite.h"

/**
 * һ�����񶥵�
 */
struct Vertex
{
	/** x,y,z���� **/
	GLfloat position[3];

	/** UV �������� **/
	GLfloat texcoord[2];

	/** ������Ϣ **/
	GLfloat normal[3];
};

class Model : public Sprite
{
private:
	std::vector<Vertex> vertices;

	std::vector<int> faceIndices;


public:

	Model();

	void Init(const char *modelPath);

	void Draw() override;

	std::vector<Vertex>& GetVertices()
	{
		return this->vertices;
	}

	std::vector<int>& GetFaces()
	{
		return this->faceIndices;
	}
};
