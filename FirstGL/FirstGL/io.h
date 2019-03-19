#pragma once

#include "utils.h"
#include "model.h"

/** ��ȡply��ʽ��ģ���ļ� **/
void LoadPly(std::string modelPath, Model *model);

/** ��ȡobj��ʽ��ģ���ļ� **/
void LoadObj(std::string modelPath, Model *model);

void LoadRGBImage(std::string imagePath, unsigned char *&rgbData, int& width, int &height);
