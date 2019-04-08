#pragma once

#include "utils.h"
#include "model.h"

/** ��ȡply��ʽ��ģ���ļ� **/
void LoadPly(std::string model_path, Model *model);

/** ��ȡobj��ʽ��ģ���ļ� **/
void LoadObj(std::string model_path, Model *model);

void LoadRGBImage(std::string image_path, unsigned char *&rgb_data, int& width, int &height);
