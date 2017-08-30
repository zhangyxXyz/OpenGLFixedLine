#pragma once
#include <windows.h>
#include <gl/GL.h>
class FontManager
{
public:
	FontManager();
	~FontManager();
public:
	static void Init(HDC dc);
	static void Draw(wchar_t*str);
};

