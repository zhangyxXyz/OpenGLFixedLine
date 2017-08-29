#pragma once

#include <windows.h>
#include <gl/GL.h>
#include "Texture.h"
#include "Vector3f.h"
#include "List.h"

class ImageSprite :List
{
public:
	ImageSprite();
	~ImageSprite();
public:
	Texture* m_Texture;
	Vector3f m_Mesh[4];
	void SetTexture(Texture* texture);
	void SetRect(float x, float y, float width, float height);
	void Draw();
};