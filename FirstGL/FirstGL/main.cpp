#include "ggl.h"
#include "scene.h"
#include <Windows.h>
#include "utils.h"
// ָʾ���� opengl32.lib �����, VS Ĭ�ϴ������
#pragma comment (lib, "opengl32.lib") 
//#pragma comment (lib, "glew32.lib") 
#pragma comment (lib, "glu32.lib") 
#pragma comment (lib, "winmm.lib") 

POINT originalPos;

bool rotateView = false;

unsigned char* LoadFile(const char* filePath, int& fileSize)
{
	unsigned char *fileContent = nullptr;
	fileSize = 0;

	FILE *fp = fopen(filePath, "rb");
	if (fp == nullptr)
	{
		return fileContent;
	}
	fseek(fp, 0, SEEK_END); // �ƶ��ļ�ָ�뵽β��
	int nlen = ftell(fp);
	if (nlen > 0)
	{
		rewind(fp); // �Ƶ�ͷ��
		fileContent = new unsigned char[nlen + 1];
		fread(fileContent, sizeof(unsigned char), nlen, fp);
		fileContent[nlen] = 0;
		fileSize = nlen;
	}
	fclose(fp);
	return fileContent;
}

/**
 * @param msg: 1 ��ʾ�û��ر��˴��ڣ� 2 ��ʾ�û��û���ק�˴���
 * @param wParam: �������Ϣ 
 */
LRESULT CALLBACK GLWindowProc(HWND hwn, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		OnKeyDown(wParam);
		return 0;
	case WM_KEYUP:
		OnKeyUp(wParam);
		return 0;
	case WM_RBUTTONDOWN:
		GetCursorPos(&originalPos);
		ShowCursor(false);
		rotateView = true;
		return 0;
	case WM_RBUTTONUP:
		SetCursorPos(originalPos.x, originalPos.y);
		ShowCursor(true);
		rotateView = false;
		return 0;
	case WM_MOUSEMOVE:
		if (rotateView)
		{
			POINT currentPos;
			GetCursorPos(&currentPos);
			int deltaX = currentPos.x - originalPos.x;
			int deltaY = currentPos.y - originalPos.y;
			OnMouseMove(deltaX, deltaY);
			SetCursorPos(originalPos.x, originalPos.y);
		}
			return 0;
	case WM_CLOSE:
		// ���ڹرգ����� QUIT ��Ϣ
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwn, msg, wParam, lParam);
}

void SetWindowContent(WNDCLASSEX *windowClass, HINSTANCE hInstance)
{
	windowClass -> cbClsExtra = 0;
	windowClass -> cbSize = sizeof(WNDCLASSEX);
	windowClass -> cbWndExtra = 0;
	windowClass -> hbrBackground = nullptr;
	windowClass -> hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass -> hIcon = nullptr;
	windowClass -> hIconSm = nullptr;
	windowClass -> hInstance = hInstance;
	windowClass -> lpfnWndProc = GLWindowProc; // �û���������ص�����ָ��
	windowClass -> lpszClassName = "GLWindow"; // ClassName �����Ҹ�?
	windowClass -> lpszMenuName = nullptr;
	windowClass -> style = CS_VREDRAW | CS_HREDRAW; // ��ֱ�ػ� + ˮƽ�ػ�
	
}

/**
 * ���� OpenGL ��Ⱦ����
 *
 */
HDC SetOpenGlEnv(HWND hwnd)
{
	// ==================
	HDC hdc = GetDC(hwnd); // ��ȡ�豸������
	PIXELFORMATDESCRIPTOR pfd; // ���ظ�ʽ������
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32; // RGBA ��ռ8bit
	pfd.cDepthBits = 24; // ��Ȼ�����
	pfd.cStencilBits = 8; // �ɰ滺����
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	int pixelFormat = ChoosePixelFormat(hdc, &pfd); // windows ������ѡ�� pixelFormat
	SetPixelFormat(hdc, pixelFormat, &pfd);
	HGLRC rc = wglCreateContext(hdc);// handle GL render context ������Ⱦ����
	wglMakeCurrent(hdc, rc); // ʹ��Ⱦ������Ч
	Init();
	
	return hdc;
}


/**
 * windows ���ڳ������ں���
 */
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR cmdLine, int nShowCommand) {
	// ע�ᴰ��
	WNDCLASSEX windowClass; // ����һ���ṹ��, ����������Ϣ
	SetWindowContent(&windowClass, hInstance);
	auto atom = RegisterClassEx(&windowClass); // ע�ᴰ��

	RECT rect;
	rect.left = 0;
	rect.right = 800;
	rect.top = 0;
	rect.bottom = 600;
	// ���������֤�ӿڵ�rect Ϊ 800 x 600�����ϱ����������߰���ģ����µõ� rect �Ĵ�С
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	const int windowWidth = rect.right - rect.left;
	const int windowHeight = rect.bottom - rect.top;

	if (atom == 0) {
		MessageBox(nullptr, "notice", "Error", MB_OK);
		return 0;
	}

	HWND hwnd = CreateWindowEx(NULL, "GLWindow", "GL", WS_OVERLAPPEDWINDOW, 
		100, 100, windowWidth, windowHeight, 
		nullptr, nullptr, hInstance, nullptr);
	const auto hdc = SetOpenGlEnv(hwnd); // ��ʼ�� OpenGL ��Ⱦ����
	ShowWindow(hwnd, SW_SHOW); //
	UpdateWindow(hwnd); // �����������ģ���Ҫ����ˢ��һ��

	MSG msg;
	// �Լ������¼��� �ó����˳�
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Draw();
		SwapBuffers(hdc); // ���� OpenGl �Ļ��������Ѻ���Ļ�����������ǰ����
	}
	return 0;
}

