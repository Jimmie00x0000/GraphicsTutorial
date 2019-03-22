#include "skybox.h"
#include "utils.h"

void SkyBox::Init(const char* imageDir, Camera *c)
{
	this->currCamera = c;

	char temp[256];
	strcpy(temp, imageDir);
	strcat(temp, "Front.bmp");
	mTextures[0] = CreateTexture2DFromBmp(temp);

	strcpy(temp, imageDir);
	strcat(temp, "Back.bmp");
	mTextures[1] = CreateTexture2DFromBmp(temp);

	strcpy(temp, imageDir);
	strcat(temp, "Left.bmp");
	mTextures[2] = CreateTexture2DFromBmp(temp);

	strcpy(temp, imageDir);
	strcat(temp, "Right.bmp");
	mTextures[3] = CreateTexture2DFromBmp(temp);

	strcpy(temp, imageDir);
	strcat(temp, "Top.bmp");
	mTextures[4] = CreateTexture2DFromBmp(temp);

	strcpy(temp, imageDir);
	strcat(temp, "Bottom.bmp");
	mTextures[5] = CreateTexture2DFromBmp(temp);

	mFastDrawCall = CreateDisplayList([this]() -> void {DrawCommand();});
}

/**
 */
void SkyBox::DrawCommand()
{
	glDisable(GL_DEPTH_TEST); // ��������ã� ���ܵ�ס�������
	glDisable(GL_LIGHTING); // ��������ã����տ��ܵ�����պб��
	glEnable(GL_TEXTURE_2D);

	// Front
	glBindTexture(GL_TEXTURE_2D, mTextures[0]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(+0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(+0.5f, +.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-0.5f, +.5f, -0.5f);
	glEnd();

	// Back
	glBindTexture(GL_TEXTURE_2D, mTextures[1]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-0.5f, -.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(+0.5f, -.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(+0.5f, +.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-0.5f, +.5f, +0.5f);
	glEnd();

	// Left ��
	glBindTexture(GL_TEXTURE_2D, mTextures[2]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(-0.5f, +.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(-0.5f, +.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-0.5f, -.5f, +0.5f);
	glEnd();

	// Right ��
	glBindTexture(GL_TEXTURE_2D, mTextures[3]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(+0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(+0.5f, +.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(+0.5f, +.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(+0.5f, -.5f, +0.5f);
	glEnd();

	// Top ��
	glBindTexture(GL_TEXTURE_2D, mTextures[4]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-0.5f, +.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(+0.5f, +.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(+0.5f, +.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-0.5f, +.5f, +0.5f);
	glEnd();

	// Bottom ��
	glBindTexture(GL_TEXTURE_2D, mTextures[5]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(+0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(+0.5f, -.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-0.5f, -.5f, +0.5f);
	glEnd();

	glEnable(GL_DEPTH_TEST); // ��������ã� ���ܵ�ס�������
	glEnable(GL_LIGHTING); // ��������ã����տ��ܵ�����պб��
	glEnable(GL_TEXTURE_2D);
}

/*
 * �ѻ��ƹ��̴洢���أ�Init() ������ʼ�������浽һ��������
 * ���ǲ����ã��õ�һ�� GLuint ���͵�������xx��Draw() �׶�ͨ�� glCallList(xx) ����
 * ��ʾ�б�����Ż���ͼ����
 */
void SkyBox::Draw()
{
	glPushMatrix();
	glTranslatef(currCamera->GetPosition().v1,
		currCamera->GetPosition().v2, 
		currCamera->GetPosition().v3);
	glCallList(mFastDrawCall);
	glPopMatrix();
	//glLoadIdentity();


}