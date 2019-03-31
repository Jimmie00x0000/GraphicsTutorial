#include "scene.h"
#include "utils.h"
#include <iostream>
#include "ground.h"
#include "mesh.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/type_ptr.hpp"

Ground ground;
TriMesh mesh;

GLuint vbo;
// 指示如何组织顶点数据来绘制图元
GLuint ebo;
GLuint program;
GLuint textureID;
GLint positionLocation;
GLint texcoordLocation; // 纹理UV坐标的插槽
GLint textureLocation; // 纹理信息的插槽
GLint colorLocation;
GLint modelMatrixLocation;
GLint viewMatrixLocation;
GLint projectionMatrixLocation;

glm::mat4 modelMatrix;
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;


void SetViewPortSize(float width, float height)
{
	glViewport(0, 0, width, height);
	// 最新API中，第一个参数 角度改成了弧度。
	projectionMatrix = glm::perspective(60.0f / 180.0f * PI, width / height, 0.1f, 1000.0f);
}

/**
 * 屏幕正中心是世界坐标系原点
 * z 轴指向屏幕外面, 所以 z 坐标要设负值
 */
void Init()
{
	ground.Init();
	mesh.Init("Res/Dog.ply");
	// InitVBO();
	// InitEBO();
	// InitShader();
	modelMatrix = glm::identity<glm::mat4>();
	viewMatrix = glm::lookAt<float, glm::defaultp>({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f});

	// printGLMMatrix(modelMatrix, "model ");
	// printGLMMatrix(viewMatrix, "view ");
	// printGLMMatrix(projectionMatrix, "projection ");


	// light.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	// light.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	// light.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	// light.SetPosition(0.0f, 1.0f, 0.0f);
	// light1.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	// light1.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	// light1.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	// light1.SetPosition(0.0f, 0.0f, 0.0f); // 点光源放到原点
	// light1.SetConstantAttenuation(0.1f);
	// light1.SetLinearAttenuation(0.2f);
	// // 第二个点光源
	// light2.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	// light2.SetDiffuseColor(0.1f, 0.4f, 0.7f, 1.0f);
	// light2.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	// light2.SetPosition(0.0f, 0.0f, -20.0f); // 
	// light2.SetConstantAttenuation(0.5f);
	// light2.SetLinearAttenuation(0.2f);

}


// void InitEBO()
// {
// 	unsigned short indices[] = { 0, 1, 2 };
// 	ebo = CreateBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3, GL_STATIC_DRAW, indices);
// }

//
// void InitShader()
// {
// 	int fileSize = 0;
// 	unsigned char *shaderCode = LoadFile("Res/test.vs", fileSize);
// 	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)shaderCode);
// 	delete shaderCode;
// 	
// 	shaderCode = LoadFile("Res/test.fs", fileSize);
// 	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)shaderCode);
// 	delete shaderCode;
// 	program = CreateShaderProgram(vsShader, fsShader);
// 	glDeleteShader(vsShader);
// 	glDeleteShader(fsShader);
// 	positionLocation = glGetAttribLocation(program, "position");
// 	colorLocation = glGetAttribLocation(program, "color");
// 	texcoordLocation = glGetAttribLocation(program, "texcoord");
// 	modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
// 	viewMatrixLocation = glGetUniformLocation(program, "ViewMatrix");
// 	textureLocation = glGetUniformLocation(program, "U_Texture");
// 	projectionMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
//
// 	textureID = CreateTexture2DFromBmp("Res/Texture.bmp");
// }


void Draw()
{
	glClearColor(0.1f, 0.3f, 0.5f, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	// 每一帧绘制之前要清除颜色缓冲区和深度缓冲区(初始化为1.0，即最远)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const float frameTime = GetFrameTime();

//	gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
	//viewMatrix = glm::scale(viewMatrix, { 1.0, -1.0, 1.0 });

	// ground.Draw(viewMatrix, projectionMatrix);
	mesh.Draw(viewMatrix, projectionMatrix);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("error: 0x%x\n", error);
	}

	// glUseProgram(program);	
	// // 为 GPU 上的顶点着色程序传递数据（几个matrix)
	// // 第一个传插槽， 第二个参数 几个矩阵， 第三个参数 需不需要转置， 第四个，矩阵的位置
	// glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	// glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	// glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	// glBindTexture(GL_TEXTURE_2D, textureID);
	// glUniform1i(textureLocation, 0);
	//
	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// glEnableVertexAttribArray(positionLocation);
	// // 第一个传插槽， 第二个 数据有几个分量， 第三个 数据类型， 第四个 是否归一化， 第五个 数据大小， 第六个 
	// glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, nullptr);
	// glEnableVertexAttribArray(colorLocation);
	// glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 4));
	// glEnableVertexAttribArray(texcoordLocation);
	// glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 8));
	// // glDrawArrays(GL_TRIANGLES, 0, 3);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// // 传递数据到显卡进行绘制，每 3 个顶点画一个三角形， 最后一个参数是数据的起始位置
	// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// glUseProgram(0);


	// camera.Update(frameTime);

	// light1.Enable();
	// light1.Update(camera.GetPosition().v1, camera.GetPosition().v2, camera.GetPosition().v3);
	// light2.Enable();
	// light2.Update(camera.GetPosition().v1, camera.GetPosition().v2, camera.GetPosition().v3);

	//glEnable(GL_DEPTH_TEST); // 保证近的物体会挡住远的物体
	//particle.Draw();
	// DrawModel();
}

void OnKeyDown(char code)
{
	// switch (code)
	// {
	// case 'A':
	// 	camera.SetMovingLeft(true);
	// 	break;
	// case 'S':
	// 	camera.SetMovingBackward(true);
	// 	break;
	// case 'D':
	// 	camera.SetMovingRight(true);
	// 	break;
	// case 'W':
	// 	camera.SetMovingForward(true);
	// 	break;
	// }
}

void OnKeyUp(char code)
{
	// switch (code)
	// {
	// case 'A':
	// 	camera.SetMovingLeft(false);
	// 	break;
	// case 'S':
	// 	camera.SetMovingBackward(false);
	// 	break;
	// case 'D':
	// 	camera.SetMovingRight(false);
	// 	break;
	// case 'W':
	// 	camera.SetMovingForward(false);
	// 	break;
	// }
}

void OnMouseMove(float deltaX, float deltaY)
{
	// 在 x 轴滑动，相机沿 y轴转动，位移值近似逼近 yaw 的角度
	float angleRotateByYAxis = deltaX / 1000.0f; 
	// 在 y 轴滑动，相机沿 x轴转动，位移值近似逼近 pitch 的角度
	float angleRotateByXAxis = deltaY / 1000.0f; 
	// camera.Yaw(- angleRotateByYAxis);
	// camera.Pitch(- angleRotateByXAxis);
}
