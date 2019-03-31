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
// ָʾ�����֯��������������ͼԪ
GLuint ebo;
GLuint program;
GLuint textureID;
GLint positionLocation;
GLint texcoordLocation; // ����UV����Ĳ��
GLint textureLocation; // ������Ϣ�Ĳ��
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
	// ����API�У���һ������ �Ƕȸĳ��˻��ȡ�
	projectionMatrix = glm::perspective(60.0f / 180.0f * PI, width / height, 0.1f, 1000.0f);
}

/**
 * ��Ļ����������������ϵԭ��
 * z ��ָ����Ļ����, ���� z ����Ҫ�踺ֵ
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

	// printGLMMatrix(model_matrix_, "model ");
	// printGLMMatrix(viewMatrix, "view ");
	// printGLMMatrix(projectionMatrix, "projection ");


	// light.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	// light.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	// light.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	// light.SetPosition(0.0f, 1.0f, 0.0f);
	// light1.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	// light1.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	// light1.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	// light1.SetPosition(0.0f, 0.0f, 0.0f); // ���Դ�ŵ�ԭ��
	// light1.SetConstantAttenuation(0.1f);
	// light1.SetLinearAttenuation(0.2f);
	// // �ڶ������Դ
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
// 	position_location_ = glGetAttribLocation(program, "position");
// 	color_location_ = glGetAttribLocation(program, "color");
// 	texcoord_location_ = glGetAttribLocation(program, "texcoord");
// 	model_matrix_location_ = glGetUniformLocation(program, "ModelMatrix");
// 	view_matrix_location_ = glGetUniformLocation(program, "ViewMatrix");
// 	textureLocation = glGetUniformLocation(program, "U_Texture");
// 	projection_matrix_location_ = glGetUniformLocation(program, "ProjectionMatrix");
//
// 	textureID = CreateTexture2DFromBmp("Res/Texture.bmp");
// }


void Draw()
{
	glClearColor(0.1f, 0.3f, 0.5f, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	// ÿһ֡����֮ǰҪ�����ɫ����������Ȼ�����(��ʼ��Ϊ1.0������Զ)
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
	// // Ϊ GPU �ϵĶ�����ɫ���򴫵����ݣ�����matrix)
	// // ��һ������ۣ� �ڶ������� �������� ���������� �費��Ҫת�ã� ���ĸ��������λ��
	// glUniformMatrix4fv(model_matrix_location_, 1, GL_FALSE, glm::value_ptr(model_matrix_));
	// glUniformMatrix4fv(view_matrix_location_, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	// glUniformMatrix4fv(projection_matrix_location_, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	// glBindTexture(GL_TEXTURE_2D, textureID);
	// glUniform1i(textureLocation, 0);
	//
	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// glEnableVertexAttribArray(position_location_);
	// // ��һ������ۣ� �ڶ��� �����м��������� ������ �������ͣ� ���ĸ� �Ƿ��һ���� ����� ���ݴ�С�� ������ 
	// glVertexAttribPointer(position_location_, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, nullptr);
	// glEnableVertexAttribArray(color_location_);
	// glVertexAttribPointer(color_location_, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 4));
	// glEnableVertexAttribArray(texcoord_location_);
	// glVertexAttribPointer(texcoord_location_, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 8));
	// // glDrawArrays(GL_TRIANGLES, 0, 3);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// // �������ݵ��Կ����л��ƣ�ÿ 3 �����㻭һ�������Σ� ���һ�����������ݵ���ʼλ��
	// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// glUseProgram(0);


	// camera.Update(frameTime);

	// light1.Enable();
	// light1.Update(camera.GetPosition().v1, camera.GetPosition().v2, camera.GetPosition().v3);
	// light2.Enable();
	// light2.Update(camera.GetPosition().v1, camera.GetPosition().v2, camera.GetPosition().v3);

	//glEnable(GL_DEPTH_TEST); // ��֤��������ᵲסԶ������
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
	// �� x �Ử��������� y��ת����λ��ֵ���Ʊƽ� yaw �ĽǶ�
	float angleRotateByYAxis = deltaX / 1000.0f; 
	// �� y �Ử��������� x��ת����λ��ֵ���Ʊƽ� pitch �ĽǶ�
	float angleRotateByXAxis = deltaY / 1000.0f; 
	// camera.Yaw(- angleRotateByYAxis);
	// camera.Pitch(- angleRotateByXAxis);
}
