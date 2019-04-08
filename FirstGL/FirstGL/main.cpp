#include "ggl.h"
#include "scene.h"
#include <Windows.h>
#include "utils.h"
// ָʾ���� opengl32.lib �����, VS Ĭ�ϴ������
#pragma comment (lib, "opengl32.lib") 
//#pragma comment (lib, "glew32.lib") 
#pragma comment (lib, "glu32.lib") 
#pragma comment (lib, "winmm.lib") 

POINT original_pos;

bool is_rotating_view = false;

unsigned char* LoadFile(const char* file_path, int& file_Size)
{
	unsigned char *file_content = nullptr;
	file_Size = 0;

	FILE *fp = fopen(file_path, "rb");
	if (fp == nullptr)
	{
		return file_content;
	}
	fseek(fp, 0, SEEK_END); // �ƶ��ļ�ָ�뵽β��
	int nlen = ftell(fp);
	if (nlen > 0)
	{
		rewind(fp); // �Ƶ�ͷ��
		file_content = new unsigned char[nlen + 1];
		fread(file_content, sizeof(unsigned char), nlen, fp);
		file_content[nlen] = 0;
		file_Size = nlen;
	}
	fclose(fp);
	return file_content;
}

/**
 * @param msg: 1 ��ʾ�û��ر��˴��ڣ� 2 ��ʾ�û��û���ק�˴���
 * @param w_param: �������Ϣ 
 */
LRESULT CALLBACK GLWindowProc(HWND hwn, UINT msg, WPARAM w_param, LPARAM l_param)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		OnKeyDown(w_param);
		return 0;
	case WM_KEYUP:
		OnKeyUp(w_param);
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
		if (is_rotating_view)
		{
			POINT current_pos;
			GetCursorPos(&current_pos);
			const int delta_x = current_pos.x - original_pos.x;
			const int delta_y = current_pos.y - original_pos.y;
			OnMouseMove(delta_x, delta_y);
			SetCursorPos(original_pos.x, original_pos.y);
		}
			return 0;
	case WM_CLOSE:
		// ���ڹرգ����� QUIT ��Ϣ
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwn, msg, w_param, l_param);
}

void SetWindowContent(WNDCLASSEX *window_class, HINSTANCE h_instance)
{
	window_class -> cbClsExtra = 0;
	window_class -> cbSize = sizeof(WNDCLASSEX);
	window_class -> cbWndExtra = 0;
	window_class -> hbrBackground = nullptr;
	window_class -> hCursor = LoadCursor(nullptr, IDC_ARROW);
	window_class -> hIcon = nullptr;
	window_class -> hIconSm = nullptr;
	window_class -> hInstance = h_instance;
	window_class -> lpfnWndProc = GLWindowProc; // �û���������ص�����ָ��
	window_class -> lpszClassName = "GLWindow"; // ClassName �����Ҹ�?
	window_class -> lpszMenuName = nullptr;
	window_class -> style = CS_VREDRAW | CS_HREDRAW; // ��ֱ�ػ� + ˮƽ�ػ�
	
}

/**
 * ���� OpenGL ��Ⱦ����
 *
 */
HDC SetOpenGlEnv(HWND hwnd)
{
	// ==================
	auto hdc = GetDC(hwnd); // ��ȡ�豸������
	PIXELFORMATDESCRIPTOR pfd; // ���ظ�ʽ������
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32; // RGBA ��ռ8bit
	pfd.cDepthBits = 24; // ��Ȼ�����
	pfd.cStencilBits = 8; // �ɰ滺����
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	int pixel_format = ChoosePixelFormat(hdc, &pfd); // windows ������ѡ�� pixelFormat
	SetPixelFormat(hdc, pixel_format, &pfd);
	const auto rc = wglCreateContext(hdc);// handle GL render context ������Ⱦ����
	wglMakeCurrent(hdc, rc); // ʹ��Ⱦ������Ч
	Init();
	
	return hdc;
}


/**
 * windows ���ڳ������ں���
 */
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR cmdLine, int nShowCommand) {
	// ע�ᴰ��
	WNDCLASSEX window_class; // ����һ���ṹ��, ����������Ϣ
	SetWindowContent(&window_class, hInstance);
	const auto atom = RegisterClassEx(&window_class); // ע�ᴰ��

	RECT rect;
	rect.left = 0;
	rect.right = 800;
	rect.top = 0;
	rect.bottom = 600;
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

