#include "scene.h"
#include "ggl.h"
#include <Windows.h>
#include <cstdio>
#include "utils.h"
#include <iostream>
// // ָʾ���� opengl32.lib �����, VS Ĭ�ϴ������
#pragma comment (lib, "glew32.lib") 
#pragma comment (lib, "glu32.lib") 
#pragma comment (lib, "opengl32.lib") 
#pragma comment (lib, "winmm.lib") 

POINT original_pos;

bool is_rotating_view = false;

Scene scene;

int default_viewport_width = 1200;
int default_viewport_height = 800;


/**
 * @param msg: 1 ��ʾ�û��ر��˴��ڣ� 2 ��ʾ�û��û���ק�˴���
 * @param wParam: �������Ϣ
 */
LRESULT CALLBACK GLWindowProc(HWND hwn, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYDOWN:
		scene.OnKeyDown(wParam);
		return 0;
	case WM_KEYUP:
		scene.OnKeyUp(wParam);
		return 0;
	case WM_RBUTTONDOWN:
		GetCursorPos(&original_pos);
		ShowCursor(false);
		is_rotating_view = true;
		return 0;
	case WM_RBUTTONUP:
		SetCursorPos(original_pos.x, original_pos.y);
		ShowCursor(true);
		is_rotating_view = false;
		return 0;
	case WM_MOUSEMOVE:
		if (is_rotating_view) {
			POINT current_pos;
			GetCursorPos(&current_pos);
			const int delta_x = current_pos.x - original_pos.x;
			const int delta_y = current_pos.y - original_pos.y;
			scene.OnMouseMove(delta_x, delta_y);
			SetCursorPos(original_pos.x, original_pos.y);
		}
		return 0;
	case WM_CLOSE:
		// ���ڹرգ����� QUIT ��Ϣ
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		int curr_width = LOWORD(lParam);
		int curr_height = HIWORD(lParam);
		//AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
		const int canvas_width = curr_width;
		const int canvas_height = curr_height;
		// std::cout << "canvas, width: " << canvas_width << ", height: " << canvas_height << std::endl;
		scene.SetViewPortSize(canvas_width * 1.0f, canvas_height * 1.0f);
		return 0;
	}

	return DefWindowProc(hwn, msg, wParam, lParam);
}

void SetWindowContent(WNDCLASSEX *windowClass, HINSTANCE hInstance) {
	windowClass->cbClsExtra = 0;
	windowClass->cbSize = sizeof(WNDCLASSEX);
	windowClass->cbWndExtra = 0;
	windowClass->hbrBackground = nullptr;
	windowClass->hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass->hIcon = nullptr;
	windowClass->hIconSm = nullptr;
	windowClass->hInstance = hInstance;
	windowClass->lpfnWndProc = GLWindowProc; // �û���������ص�����ָ��
	windowClass->lpszClassName = "GLWindow"; // ClassName �����Ҹ�?
	windowClass->lpszMenuName = nullptr;
	windowClass->style = CS_VREDRAW | CS_HREDRAW; // ��ֱ�ػ� + ˮƽ�ػ�

}

/**
 * ���� OpenGL ��Ⱦ����
 *
 */
HDC SetOpenGlEnv(HWND hwnd)
{
	// ==================
	const auto hdc = GetDC(hwnd); // ��ȡ�豸������
	PIXELFORMATDESCRIPTOR pfd; // ���ظ�ʽ������
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32; // RGBA ��ռ8bit
	pfd.cDepthBits = 24; // ��Ȼ�����
	pfd.cStencilBits = 8; // �ɰ滺����
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	const int pixel_format = ChoosePixelFormat(hdc, &pfd); // windows ������ѡ�� pixelFormat
	SetPixelFormat(hdc, pixel_format, &pfd);
	HGLRC rc = wglCreateContext(hdc);// handle GL render context ������Ⱦ����
	wglMakeCurrent(hdc, rc); // ʹ��Ⱦ������Ч
	glewInit();
	if (glewInit()) {
		std::cerr 
		<< "Unable to initialize GLEW ... exiting" 
		<< std::endl; 
		exit(EXIT_FAILURE);
	}
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	scene.SetViewPortSize(default_viewport_width * 1.0f, default_viewport_height * 1.0f);

	scene.Init();

	return hdc;
}


/**
 * windows ���ڳ������ں���
 */
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR cmdLine, int nShowCommand) {
	char temp[2048];
	GetSystemDirectory(temp, 2048);
	printf("system directory: %s\n", temp);
	// ע�ᴰ��
	WNDCLASSEX window_class; // ����һ���ṹ��, ����������Ϣ
	SetWindowContent(&window_class, hInstance);
	const auto atom = RegisterClassEx(&window_class); // ע�ᴰ��
		
	RECT rect;
	rect.left = 0;
	rect.right = default_viewport_width;
	rect.top = 0;
	rect.bottom = default_viewport_height;
	// ���������֤�ӿڵ�rect Ϊ 800 x 600�����ϱ����������߰���ģ����µõ� rect �Ĵ�С
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	const int window_width = rect.right - rect.left;
	const int window_height = rect.bottom - rect.top;
	
	if (atom == 0) {
		MessageBox(nullptr, "notice", "Error", MB_OK);
		return 0;
	}
	
	HWND hwnd = CreateWindowEx(NULL, "GLWindow", "GL", WS_OVERLAPPEDWINDOW,
		100, 100, window_width, window_height,
		nullptr, nullptr, hInstance, nullptr);
	const auto hdc = SetOpenGlEnv(hwnd); // ��ʼ�� OpenGL ��Ⱦ����
	ShowWindow(hwnd, SW_SHOW); //
	UpdateWindow(hwnd); // �����������ģ���Ҫ����ˢ��һ��
	
	MSG msg;
	// �Լ������¼��� �ó����˳�
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		scene.UpdateScene();
		scene.Draw();
		SwapBuffers(hdc); // ���� OpenGl �Ļ��������Ѻ���Ļ�����������ǰ����
	}
	return 0;
}

