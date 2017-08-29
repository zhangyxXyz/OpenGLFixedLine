#pragma once
#include <windows.h>
#include <gl/GL.h>
#include "Texture.h"
#include "DisplayList.h"

class SkyBox
{
public:
	SkyBox();
	~SkyBox();
public:
	DisplayList m_SkyBox;
	Texture* front;
	Texture* back;
	Texture* right;
	Texture* left;
	Texture* top;
	Texture* bottom;
	void Init(const char* path);
	void Draw(float x, float y, float z);
};

