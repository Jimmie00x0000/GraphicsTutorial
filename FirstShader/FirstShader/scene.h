#pragma once
#include "ggl.h"


class A
{
public:
	template<class T> T function_m() { };
};

template<typename  U> void function_n(U argument)
{
	char object_x = argument.template function_m<char>();  // ill-formed
}

void SetViewPortSize(float width, float height);

void Init();

void Draw();

// ���̰����¼�
void OnKeyDown(char code);

// ���̵����¼�
void OnKeyUp(char code);

void OnMouseMove(float deltaX, float deltaY);
