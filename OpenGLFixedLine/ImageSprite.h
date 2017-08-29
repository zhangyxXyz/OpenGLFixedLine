#pragma once

#include <windows.h>
#include <gl/GL.h>
#include "Texture.h"
#include "Vector3f.h"
#include "List.h"

class ImageSprite
{
public:
	ImageSprite();
	~ImageSprite();
public:
	Texture* m_Texture;
	Vector3f m_Mesh[4];
	unsigned char m_Alpha;
	bool m_FadeIn;
	bool m_FadeOut;
	int m_FadeSpeed;
	void SetTexture(Texture* texture);
	void SetRect(float x, float y, float width, float height);
	void Draw();
	void FadeIn(float duration);
	void FadeOut(float duration);
	void Update(float deltaTime);
};