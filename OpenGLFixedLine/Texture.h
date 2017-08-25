#pragma once
#include <windows.h>
#include <gl/GL.h>
class Texture
{
public:
	Texture();
	~Texture();
public:
	GLuint m_textureID;// gpu only know texture id same as textrue name
	void Init(const char* imgPath);
	
};

