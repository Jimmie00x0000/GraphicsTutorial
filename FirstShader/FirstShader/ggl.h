#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
//#define GL_GLEXT_PROTOTYPES

// Windows ���ṩ glew.h���Լ����أ�����ͷ�ļ���lib�ļ��� VC++ ��include Ŀ¼�� libĿ¼��
// ��Ҫ���� glew32.lib
#include "GL/glew.h"
#include "GL/GL.h"

// Windows Ĭ���ṩ "gl/GL.h", ��Ҫ���� opengl32.lib
// ��ͷ�ļ�ȱʧһЩ������ö��ֵ�Ķ��壬������ʹ�� glew.h
#include <gl/GLU.h> // ������

//#define GL_CLAMP_TO_EDGE 0X812F

#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <functional>

