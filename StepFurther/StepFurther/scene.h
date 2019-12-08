#pragma once
#include "ggl.h"
#include "ground.h"
#include "mesh.h"
#include "model.h"
#include "camera.h"
#include <vector>

class Scene {
private:
	Ground ground;
	//TriMesh mesh;
	Camera camera;
	// std::vector<zjl::TriMesh> meshes;
	std::vector<Model> models;

	bool w_pressing;
	bool s_pressing;
	bool a_pressing;
	bool d_pressing;

	bool draw_wireframe_;

	int tick_cnt_;

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
