#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Texture.h"
#include "Utils.h"
#include "ObjModel.h"
#include "Camera.h"
#include <iostream>
using namespace std;
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")

Camera camera;
POINT originalPos;
bool bRotateView = false;

LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		if (bRotateView)
		{
			POINT currentPos;
			currentPos.x = LOWORD(lParam);
			currentPos.y = HIWORD(lParam);
			ClientToScreen(hwnd, &currentPos);
			int deltaX = currentPos.x - originalPos.x;
			int deltaY = currentPos.y - originalPos.y;
			// limit x/sinx --> angle
			float angleRotatedByRight = (float)deltaY / 1000.0f;
			float angleRotatedByUp = (float)deltaX / 1000.0f;
			camera.Yaw(-angleRotatedByUp);
			camera.Pitch(-angleRotatedByRight);
			SetCursorPos(originalPos.x, originalPos.y);
		}
		break;
	case WM_RBUTTONDOWN:
		originalPos.x = LOWORD(lParam);
		originalPos.y = HIWORD(lParam);
		ClientToScreen(hwnd, &originalPos);
		SetCapture(hwnd);
		ShowCursor(false);
		bRotateView = true;
		break;
	case WM_RBUTTONUP:
		bRotateView = false;
		SetCursorPos(originalPos.x, originalPos.y);
		ReleaseCapture();
		ShowCursor(true);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			camera.m_MoveLeft = true;
			break;
		case 'D':
			camera.m_MoveRight = true;
			break;
		case 'W':
			camera.m_MoveForward = true;
			break;
		case 'S':
			camera.m_MoveBackward = true;
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'A':
			camera.m_MoveLeft = false;
			break;
		case 'D':
			camera.m_MoveRight = false;
			break;
		case 'W':
			camera.m_MoveForward = false;
			break;
		case 'S':
			camera.m_MoveBackward = false;
			break;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// register window
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = GLWindowProc; // callback function
	wndclass.lpszClassName = L"GLWindow";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;

	// create window
	ATOM atom = RegisterClassEx(&wndclass);
	if (!atom)
	{
		return -1;
	}
	RECT rect = { 0, 0, 1280, 720 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGL Window", WS_OVERLAPPEDWINDOW, 
		100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
	GetClientRect(hwnd, &rect);
	int viewportWidth = rect.right - rect.left;
	int viewportHeight = rect.bottom - rect.top;
	// create opencl render context
	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);

	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);// set opebgl context complete

	glViewport(0, 0, viewportWidth, viewportHeight);

	//openGL init
	glMatrixMode(GL_PROJECTION);// tell the GPU processer that i would select the project Matrix
	gluPerspective(50.0f, (float)viewportWidth / (float)viewportHeight, 0.1f, 1000.0f); // set some value to project matrix
	glMatrixMode(GL_MODELVIEW);// tel .. modle view matrix
	glLoadIdentity();
	//char* str = (char*)LoadFileContent("test.txt");
	//printf("%s\n", str);
	Texture* texture = Texture::LoadTexture("./res/earth.bmp");
	//texture.Init("./res/earth.bmp");// init openGL texture
	ObjModel model;
	model.Init("./res/Sphere.obj");
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f); // set "clear color" for background
	// show window
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	// init light
	float blackColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float whiteColor[] = { 1.0f,1.0f,1.0f,1.0f };
	float lightPos[] = { 0.0f,1.0f,0.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	float blackMat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float ambientMat[] = { 0.1f,0.1f,0.1f,1.0f };
	float diffuseMat[] = { 0.8f,0.8f,0.8f,1.0f };
	float specularMat[] = { 0.9f,0.9f,0.9f,1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, blackMat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackMat);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	MSG msg;
	static float sTimeSinceStartUp = timeGetTime() / 1000.0f;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// draw scene
		glLoadIdentity();
		float currentTime = timeGetTime() / 1000.0f;
		float timeElapse = currentTime - sTimeSinceStartUp;
		sTimeSinceStartUp = currentTime;

		// set up camera
		camera.Update(0.016f);// 60 frames per second
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
		model.Draw();
		//present scene
		SwapBuffers(dc);
	}
	return 0;
}