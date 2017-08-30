#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Texture.h"
#include "Utils.h"
#include "ObjModel.h"
#include "Camera.h"
#include "SkyBox.h"
#include "ImageSprite.h"
#include "Ground.h"
#include "Button.h"
#include "Particle.h"
#include "Fbx.h"
#include "FontManager.h"
#include "SequenceSprite.h"
#include "SequenceSprite3D.h"

#include <iostream>
using namespace std;
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")

Camera camera;
SkyBox skybox;
Texture* texture;
ObjModel model;
Ground ground;
//ImageSprite sprite;
Button* headButton;
ImageSprite* headSprite;
Particle* rootPartical;
Fbx fbxmodel;
SequenceSprite sequenceSprite;
SequenceSprite3D sequenceSprite3D;

POINT originalPos;
bool bRotateView = false;

void RenderOneFrame(float deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.SwitchTo3D();
	glLoadIdentity();

	// set up camera
	camera.Update(deltaTime);// 60 frames per second (0.016)

	glEnable(GL_TEXTURE_2D);
	// skybox
	skybox.Draw(camera.m_Pos.x, camera.m_Pos.y, camera.m_Pos.z);
	//ground;
	ground.Draw();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_ONE);
	glPushMatrix();
	glTranslatef(0.0f, -2.0f, 0.0f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	model.Draw();

	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	model.Draw();


	sequenceSprite3D.Update(deltaTime);
	sequenceSprite3D.Draw();

	// fbx model
	fbxmodel.Draw();

	// viewport 
	//glViewport(viewportWidth/2, viewportHeight / 2, viewportWidth / 2, viewportHeight / 2);
	//glLoadIdentity();
	//gluLookAt(5.0f, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//skybox.Draw(camera.m_Pos.x, camera.m_Pos.y, camera.m_Pos.z);
	////ground;
	//ground.Draw();
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
	//glDisable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_COLOR, GL_ONE);
	//glPushMatrix();
	//glTranslatef(0.0f, -2.0f, 0.0f);
	//glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	//model.Draw();
	//glPopMatrix();
	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_BLEND);
	//model.Draw();

	// draw UI
	camera.SwitchTo2D();
	glLoadIdentity();
	headButton->Draw();

	rootPartical->Update(deltaTime);
	rootPartical->Draw();
	headSprite->Update(deltaTime);
	headSprite->Draw();

	sequenceSprite.Update(deltaTime);
	sequenceSprite.Draw();

	// present scene
}

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
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam) - camera.m_ViewPortWidth / 2;
		int y = camera.m_VIewPortHeight / 2 - HIWORD(lParam);
		headButton->OnTouchBegin(x, y);
	}
	break;
	case WM_LBUTTONUP:
	{
		int x = LOWORD(lParam) - camera.m_ViewPortWidth / 2;
		int y = camera.m_VIewPortHeight / 2 - HIWORD(lParam);
		headButton->OnTouchEnd(x, y);
		headButton->ResetState();
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
	camera.m_ViewPortWidth = viewportWidth;
	camera.m_VIewPortHeight = viewportHeight;
	
	texture = Texture::LoadTexture("./res/earth.bmp");
	//texture.Init("./res/earth.bmp");// init openGL texture
	ground.Init();
	model.Init("./res/Sphere.obj");
	skybox.Init("./res/skybox");
	fbxmodel.Init("./res/tauren.fbx");
	sequenceSprite.Init("res/ss/", "a", 31, 240, 30);
	sequenceSprite.SetRect(0.0f, 200.0f, 256.0f, 256.0f);

	sequenceSprite3D.Init("res/ss/", "a", 31, 240, 30);
	sequenceSprite3D.SetRect(0.0f, 0.0f, 2.0f, 2.0f);

	glClearColor(0.1f, 0.4f, 0.6f, 1.0f); // set "clear color" for background
	FontManager::Init(dc);
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

	//GLuint mTexts;
	//mTexts = glGenLists(96);
	//HFONT hFont = CreateFontA(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
	//SelectObject(dc, hFont);

	//wglUseFontBitmapsA(dc, 32, 96, mTexts);

	//front face : ccw -> counter clock wind
	Texture* spriteImage = Texture::LoadTexture("./res/head.png");

	ImageSprite* sprite = new ImageSprite();
	sprite->SetTexture(spriteImage);
	headButton = new Button();
	headButton->SetDefaultSprite(sprite);
	headButton->SetRect(-400.0f, 280.0f, 100.0f, 100.0f);
	headButton->SetOnClick([]()->void 
	{
		printf("I have be clicked!\n");
		headSprite->FadeOut(1.0f);
	});

	sprite = new ImageSprite;
	sprite->SetTexture(Texture::LoadTexture("./res/fight.png"));
	Button* btn = new Button();
	btn->SetDefaultSprite(sprite);
	btn->SetRect(480, 280.0f, 40.0f, 40.0f);
	btn->SetOnClick([]()->void 
	{
		printf("fight!!\n"); 
		headSprite->FadeIn(1.0f);
	});
	headButton->Push(btn);

	sprite = new ImageSprite;
	sprite->SetTexture(Texture::LoadTexture("./res/icon.png"));
	btn = new Button();
	btn->SetDefaultSprite(sprite);
	btn->SetRect(400, 280.0f, 100.0f, 100.0f);
	btn->SetOnClick([]()->void {printf("gift!!\n"); });
	headButton->Push(btn);

	Texture* particleTexture = new Texture();
	particleTexture->m_textureID = CreateTexture(256);
	
	// fadein fadeout
	headSprite = new ImageSprite();
	headSprite->SetTexture(particleTexture);
	headSprite->SetRect(0.0f, 0.0f, 100.0f, 100.0f);
	

	rootPartical = new Particle(true);
	Particle::InitSpeeds();
	for (int i = 0;i < 2000;++i)
	{
		Particle* particle = new Particle(false);
		particle->SetTexture(particleTexture);
		particle->SetRect(0.0f, 0.0f, 20.0f, 20.0f);
		rootPartical->Push(particle);
	}

	/*char szBuffer[256] = {0};
	strcpy_s(szBuffer, "Hello Font");*/

	SaveScreenPixelToFile(viewportWidth,viewportHeight,[]()->void
	{
		RenderOneFrame(0.0f);
	}, "screenshot.bmp");
	//Texture*screenTexture = new Texture();
	//screenTexture->m_textureID = CaptureScreen(viewportWidth, viewportHeight, []()->void
	//{
	//	RenderOneFrame(0.0f);
	//});
	//sprite.SetTexture(screenTexture);

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
		float currentTime = timeGetTime() / 1000.0f;
		float timeElapse = currentTime - sTimeSinceStartUp;
		sTimeSinceStartUp = currentTime;
		/*glEnable(GL_SCISSOR_TEST);
		glScissor(0, 0, viewportWidth / 2, viewportHeight);*/
		RenderOneFrame(timeElapse);

		glColor4ub(255, 0, 0, 255);
		glRasterPos2f(-600.0f, 0.0f);
		FontManager::Draw(L"ÄãºÃÂð? OpenGL");

		/*memset(szBuffer, 0, 256);
		_strtime(szBuffer);
		glListBase(mTexts - 32);
		glColor4ub(255, 0, 0, 255);
		glRasterPos2f(-600.0f, 0.0f);
		glCallLists(strlen(szBuffer), GL_BYTE, szBuffer);*/
		SwapBuffers(dc);
	}
	return 0;
}