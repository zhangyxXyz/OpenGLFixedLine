#pragma once

#include <windows.h>
#include <gl/GL.h>
#include "Texture.h"
#include "Vector3f.h"
#include "List.h"

class ImageSprite:public List
{
public:
	ImageSprite();
	~ImageSprite();
public:
	GLenum m_DstFactor;
	Texture* m_Texture;
	Vector3f m_Mesh[4];
	Vector3f m_Pos;
	unsigned char m_Alpha;
	unsigned char m_R;
	unsigned char m_G;
	unsigned char m_B;
	bool m_FadeIn;
	bool m_FadeOut;
	int m_FadeSpeed;
	void SetTexture(Texture* texture);
	void SetRect(float x, float y, float width, float height);
	void FadeIn(float duration);
	void FadeOut(float duration);
	void Update(float deltaTime);
	virtual void Draw();
};