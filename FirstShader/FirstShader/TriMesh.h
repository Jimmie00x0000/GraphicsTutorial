#pragma once

#include "ggl.h"
#include <iostream>

//#include "sprite.h"

/**
 * һ�����񶥵�
 */
struct Vertex
{
	/** x,y,z���� **/
	GLfloat position[4];

	/** r,g,b,a **/
	GLfloat color[4];

	/** UV �������� **/
	GLfloat texcoord[4];

	/** ������Ϣ **/
	GLfloat normal[4];
};

class VertexBuffer
{
private:
	Vertex *mVertices;

	int mVertexCount;

	GLuint mVBO;

public:

	Vertex *getVertex() 
	{
		return this->mVertices;
	}

	int getVerticesCount() const
	{
		return this->mVertexCount;
	}

	void SetVertexCount(int c);

	void SetPosition(int index, float x, float y, float z, float w = 1.0f);

	void SetColor(int index, float r, float g, float b, float a = 1.0f);

	void SetNormal(int index, float x, float y, float z, float a = 1.0f);

	void SetTexcoord(int index, float u, float v);

	void Bind();

	void UnBind();

	Vertex& Get(int index);
};

class TriMesh// : public Sprite
{
private:
	std::vector<Vertex> vertices;

	std::vector<int> faceIndices;


public:

	TriMesh();

	//void Init(const char *modelPath);

	//void Draw() override;

	std::vector<Vertex>& GetVertices()
	{
		return this->vertices;
	}

	std::vector<int>& GetFaces()
	{
		return this->faceIndices;
	}
};
