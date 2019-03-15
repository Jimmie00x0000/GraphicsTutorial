#include "scene.h"


/**
 * 屏幕正中心是世界坐标系原点
 * z 轴指向屏幕外面, 所以 z 坐标要设负值
 */
void Init()
{
	// OpenGl 存在当前矩阵的概念，通过 glMatrixMode 设置当前矩阵的 模式
	glMatrixMode(GL_PROJECTION);
	// ?, 画布的宽高比， 最近可以看到的距离，最远可以看到的距离 
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.f);
	glMatrixMode(GL_MODELVIEW); // 切换当前矩阵到模型视口矩阵
	glLoadIdentity();
}

void DrawModel()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS); 
	glColor4ub(255, 255, 255, 255); glVertex3d(-0.0f, -0.0f, -2.5f); // 第一个点的坐标
	glColor4ub(255, 255, 255, 255); glVertex3d(-0.0f, +0.2f, -2.5f); // 第一个点的坐标
	glColor4ub(255, 255, 255, 255); glVertex3d(0.2f, +0.2f, -2.5f); // 第一个点的坐标
	glColor4ub(255, 255, 255, 255); glVertex3d(0.2f, 0.0f, -2.5f); // 第一个点的坐标
	glEnd(); 
}

void EnableDirectionLight()
{
	DrawModel();
	glEnable(GL_LIGHTING); // 开启光照算法，白色的四边形会变黑，没有法线信息会导致变黑
	// OpenGL 里面有八盏灯，从 0 - 7
	glEnable(GL_LIGHT0); // 开启第一盏灯，
	// 光源坐标，是齐次坐标 (x, y, z, w) -> (x/w, y/w, z/w, 1)
	const GLfloat lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // 设置 LIGHT0 的位置

}


void EnableDirectionAmbient()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LIGHT0); // 开启第一盏灯，
	glEnable(GL_CULL_FACE); 
	const GLfloat lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // 设置 LIGHT0 的位置

	const GLfloat whiteColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // 白色光
	const GLfloat blackColor[] = {0.0f, 0.0f, 0.0f, 1.0f}; // 黑色光 
	const GLfloat ambientMat[] = {0.07f, 0.07f, 0.07f, 1.0f}; // 物体表面材质的反射系数
	const GLfloat diffuseMat[] = {0.4f, 0.4f, 0.4f, 1.0f}; // 物体表面材质的漫反射系数
	const GLfloat specularMat[] = {0.9f, 0.9f, 0.9f, 1.0f}; // 物体表面材质的镜面反射系数

	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor); // 设置环境光
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMat); // 物体正面对环境光的反射系数

	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor); // 设置漫反射
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat); // 物体正面漫反射系数

	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor); // 设置镜面反射
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat); // 物体正面镜面反射系数
	
	DrawModel();
}
