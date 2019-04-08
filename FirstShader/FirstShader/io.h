#pragma once

#include "utils.h"
#include "vertex.h"
// #include "model.h"

/** ��ȡply��ʽ��ģ���ļ� **/
void LoadPly(const std::string& model_path, VertexBuffer *model, ElementBuffer *element_buffer);
//
// /** ��ȡobj��ʽ��ģ���ļ� **/
// void LoadObj(std::string modelPath, TriMesh *model);

void LoadRGBImage(std::string image_path, unsigned char *&rgbData, int& width, int &height);
