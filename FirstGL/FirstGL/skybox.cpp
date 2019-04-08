#include "skybox.h"
#include "utils.h"

SkyBox::SkyBox():
textures_{0, 0, 0, 0, 0, 0},
fast_draw_call_(0),
curr_camera_(nullptr)
{
}

void SkyBox::Init(const char* image_dir, Camera *c)
{
	this->curr_camera_ = c;

	char temp[256];
	strcpy(temp, image_dir);
	strcat(temp, "Front.bmp");
	textures_[0] = CreateTexture2DFromBmp(temp);

	strcpy(temp, image_dir);
	strcat(temp, "Back.bmp");
	textures_[1] = CreateTexture2DFromBmp(temp);

	strcpy(temp, image_dir);
	strcat(temp, "Left.bmp");
	textures_[2] = CreateTexture2DFromBmp(temp);

	strcpy(temp, image_dir);
	strcat(temp, "Right.bmp");
	textures_[3] = CreateTexture2DFromBmp(temp);

	strcpy(temp, image_dir);
	strcat(temp, "Top.bmp");
	textures_[4] = CreateTexture2DFromBmp(temp);

	strcpy(temp, image_dir);
	strcat(temp, "Bottom.bmp");
	textures_[5] = CreateTexture2DFromBmp(temp);

	fast_draw_call_ = CreateDisplayList([this]() -> void {DrawCommand();});
}

/**
 */
void SkyBox::DrawCommand()
{
	glDisable(GL_DEPTH_TEST); // ��������ã� ���ܵ�ס�������
	glDisable(GL_LIGHTING); // ��������ã����տ��ܵ�����պб��
	glEnable(GL_TEXTURE_2D);

	// Front
	glBindTexture(GL_TEXTURE_2D, textures_[0]);
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
	glBindTexture(GL_TEXTURE_2D, textures_[1]);
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
	glBindTexture(GL_TEXTURE_2D, textures_[2]);
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
	glBindTexture(GL_TEXTURE_2D, textures_[3]);
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
	glBindTexture(GL_TEXTURE_2D, textures_[4]);
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
	glBindTexture(GL_TEXTURE_2D, textures_[5]);
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
	glTranslatef(curr_camera_->GetPosition().v1,
		curr_camera_->GetPosition().v2, 
		curr_camera_->GetPosition().v3);
	glCallList(fast_draw_call_);
	glPopMatrix();
	//glLoadIdentity();


}