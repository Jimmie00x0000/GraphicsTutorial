#pragma once
#include "ggl.h"


void SetViewPortSize(float width, float height);

void Init();

void Draw();

// ���̰����¼�
void OnKeyDown(char code);

// ���̵����¼�
void OnKeyUp(char code);

void OnMouseMove(float deltaX, float deltaY);
