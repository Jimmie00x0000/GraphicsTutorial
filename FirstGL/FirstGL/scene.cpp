#include  "scene.h"

/**
 * ��Ļ����������������ϵԭ��
 * z ��ָ����Ļ����, ���� z ����Ҫ�踺ֵ
 */
void Init()
{
	// OpenGl ���ڵ�ǰ����ĸ��ͨ�� glMatrixMode ���õ�ǰ����� ģʽ
	glMatrixMode(GL_PROJECTION);
	// ?, �����Ŀ�߱ȣ� ������Կ����ľ��룬��Զ���Կ����ľ��� 
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.f);
	glMatrixMode(GL_MODELVIEW); // �л���ǰ����ģ���ӿھ���
	glLoadIdentity();
}

void DrawTriangle()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES); // ����Ҫ����ͼ�Σ�������
	glColor4ub(255, 255, 255, 255); // ��һ�������ɫ
	glVertex3d(-0.2f, -0.2f, -1.5f); // ��һ���������
	glColor4ub(255, 0, 0, 255); // �ڶ��������ɫ
	glVertex3d(0.2f, -0.2f, -1.5f); // �ڶ����������
	glColor4ub(0, 255, 0, 255);
	glVertex3d(0.f, 0.2f, -1.5f);
	glEnd(); // ����� 3 ���㣬����һ�������Σ���6���㣬��������������, ��ʱ�뷽��
	// ���������棺��ʱ�뷽����Ϊͼ�ε�����
}

void DrawTriangleStrip()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_STRIP); // ����Ҫ����ͼ�Σ�������
	//
	glColor4ub(0, 0, 255, 255); glVertex3d(-0.0f, +0.2f, -1.5f); 
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.0f, -0.0f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.2f, +0.2f, -1.5f); 
	// �������� ��������һ��������
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.3f, -0.1f, -1.5f); 
	// �������� ������������������

	glEnd(); 
}

void DrawTriangleFan()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN); 
	//
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.0f, -0.0f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.2f, +0.0f, -1.5f); 
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.1f, +0.15f, -1.5f); 
	// �������� ��������һ��������
	glColor4ub(0, 255, 255, 255); glVertex3d(-0.1f, +0.15f, -1.5f); 
	// �������� ������������������, �Ե�һ������Ϊ���ĳ����ηֲ�

	glEnd(); 
}

/**
 * ���Ʒ��εĵ㣬��ԭ��, ����Ĭ������´�СΪ 1.0
 */
void DrawVertex()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	//glPointSize(3); // Ĭ��Ϊ1
	glBegin(GL_POINTS); 
	// 
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.0f, -0.0f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.2f, +0.0f, -1.5f); 
	glEnd(); 
}

void DrawLine()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(10.); // �����߶ο��
	glBegin(GL_LINES); 
	// ÿ����������һ���߶�
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, -0.2f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	// ����һ���߶�
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.7f, -0.0f, -1.5f); 
	// ���������߶�
	glEnd(); 
	
}

void DrawLineLoop()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(7.); // �����߶ο��
	glBegin(GL_LINE_LOOP); 
	// ÿN��������(N)���߶�, �Զ���β���
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, -0.2f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	// ����һ���߶�
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.7f, -0.0f, -1.5f); 
	// ���������߶�
	glEnd(); 
}

void DrawLineStrip()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(7.); // �����߶ο��
	glBegin(GL_LINE_STRIP); 
	// ÿN��������(N- 1)���߶�
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, -0.2f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	// ����һ���߶�
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.7f, -0.0f, -1.5f); 
	// ���������߶�
	glEnd(); 
}

/**
 * �����ı���
 */
void DrawQuads()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS); 
	// ÿN��������(N- 1)���߶�
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, -0.2f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.7f, -0.0f, -1.5f); 
	glColor4ub(0, 255, 255, 255); glVertex3d(-0.2f, -0.1f, -1.5f); 
	glEnd(); 
}

/**
 * �����ı�������
 */
void DrawQuadStrip()
{
	glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUAD_STRIP); 
	// ÿN��������(N- 1)���߶�
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, -0.2f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	glColor4ub(0, 255, 255, 255); glVertex3d(-0.2f, +0.1f, -1.5f); 
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.7f, +0.1f, -1.5f); 
	// ������һ���ı���
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, 0.5f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.4f, 0.5f, -1.5f); 
	// �����������ı���

	glEnd(); 
}

void Draw()
{
	DrawQuadStrip();
	//glClearColor(0, 0, 0, 1.); // ��������ʹ�õ���ɫ, ����Ĳ���Ϊ��Ƥ������ɫ
	//glClear(GL_COLOR_BUFFER_BIT);
	//glBegin(GL_TRIANGLE_STRIP); // ����Ҫ����ͼ�Σ�������

	//glEnd(); // ����� 3 ���㣬����һ�������Σ���6���㣬��������������, ��ʱ�뷽��
}