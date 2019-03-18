#pragma once

#include "ggl.h"

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

class Model
{
private:
	std::vector<Vertex> vertices;

	std::vector<int> faceIndices;

	void LoadObj(const char *filePath);

	void LoadPly(const char *filePath);
public:
	Model();

	void Init(const char *modelPath);

	void Draw();
};
