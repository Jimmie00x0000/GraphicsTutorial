#pragma once
#include "ggl.h"


void SetViewPortSize(float width, float height);

void Init();

void UpdateScene();

void Draw();

// ���̰����¼�
void OnKeyDown(char code);

// ���̵����¼�
void OnKeyUp(char code);

void OnMouseMove(float delta_x, float delta_y);
