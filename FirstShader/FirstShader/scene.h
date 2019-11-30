#pragma once
#include "ggl.h"
#include "ground.h"
#include "mesh.h"
#include "camera.h"
#include "wireframe.h"
#include <vector>

class Scene {
private:
	Ground ground;
	//TriMesh mesh;
	Camera camera;
	WireFrame wire_frame;
	std::vector<TriMesh> meshes;

	bool w_pressing;
	bool s_pressing;
	bool a_pressing;
	bool d_pressing;

public:
	Scene();

	void SetViewPortSize(float width, float height);

	void Init();

	void UpdateScene();

	void Draw();

	// ���̰����¼�
	void OnKeyDown(char code);

	// ���̵����¼�
	void OnKeyUp(char code);

	void OnMouseMove(float delta_x, float delta_y);

};
