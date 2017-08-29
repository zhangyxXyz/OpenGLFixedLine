#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <string>
#include <unordered_map>
class Texture
{
public:
	Texture();
	~Texture();
public:
	std::string m_Path;
	GLuint m_textureID;// gpu only know texture id same as textrue name
	static Texture*LoadTexture(const char*imagePath, bool invertY = true);
	static void UnloadTexture(Texture*texture);
protected:
	void Init(const char* imgPath, bool invertY);
};
static std::unordered_map<std::string, Texture*> m_CachedTextures;