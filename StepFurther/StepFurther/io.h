#pragma once

#include "utils.h"
#include "vertex.h"
// #include "model.h"

/** ��ȡply��ʽ��ģ���ļ� **/
void LoadPly(const std::string& model_path, VertexBuffer *model, ElementBuffer *element_buffer);

//namespace zjl { class TriMesh; };
class Model;
bool LoadObj(const std::string& model_path, Model& meshes);

// /** ��ȡobj��ʽ��ģ���ļ� **/
void LoadObj(std::string modelPath, VertexBuffer& model, ElementBuffer& element_buffer);

void LoadModel(const std::string& modelPath, VertexBuffer& model, ElementBuffer& element_buffer);

void LoadRGBImage(std::string image_path, unsigned char *&rgbData, int& width, int &height);

void LoadRGBAImage(std::string image_path, unsigned char*& data, int& width, int& height);
