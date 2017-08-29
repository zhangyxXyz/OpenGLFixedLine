#pragma once
#include <windows.h>
#include <gl/GL.h>
class Ground
{
public:
	Ground();
	~Ground();
public:
	GLuint m_Ground;
	void Init();
	void Draw();
};

