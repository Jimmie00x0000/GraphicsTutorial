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
	Vertex *vertices_;

	int vertex_count_;

	GLuint vbo_;

public:

	Vertex *GetVertex() 
	{
		return this->vertices_;
	}

	int GetVerticesCount() const
	{
		return this->vertex_count_;
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

class ElementBuffer
{
private:

	unsigned int *indices_buffer_;

	int length_;

	GLuint ebo;
public:

	ElementBuffer();

	void SetBufferLength(int len);

	unsigned int *GetBuffer()
	{
		return indices_buffer_;
	}

	void Bind();

	void UnBind();

	int GetLength() const { return length_; }
};