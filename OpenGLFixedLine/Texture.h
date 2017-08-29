#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <string>
#include <unordered_map>

#define GL_CLAMP_TO_EDGE 0x812f
class Texture
{
public:
	Texture();
	~Texture();
public:
	std::string m_Path;
	GLuint m_textureID;// gpu only know texture id same as textrue name
	static Texture*LoadTexture(const char*imagePath, bool invertY = true, GLenum warpMode = GL_CLAMP_TO_EDGE);
	static void UnloadTexture(Texture*texture);
protected:
	void Init(const char* imgPath, bool invertY, GLenum wrapMode);
};
static std::unordered_map<std::string, Texture*> m_CachedTextures;