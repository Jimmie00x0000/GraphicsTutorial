#pragma once

#include "utils.h"
#include "vertex.h"
// #include "model.h"

/** ��ȡply��ʽ��ģ���ļ� **/
void LoadPly(std::string modelPath, VertexBuffer *model, ElementBuffer *element_buffer);
//
// /** ��ȡobj��ʽ��ģ���ļ� **/
// void LoadObj(std::string modelPath, TriMesh *model);

void LoadRGBImage(std::string imagePath, unsigned char *&rgbData, int& width, int &height);
