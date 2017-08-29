#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <functional>

class DisplayList
{
public:
	DisplayList();
	~DisplayList();
public:
	GLuint m_DisplayList;
	void Init(std::function<void()>foo);
	void Draw();
};

