#pragma once

#include <windows.h>
#include <gl/GL.h>
#include "Texture.h"
#include "Vector3f.h"
#include "List.h"

class SequenceSprite:public List
{
public:
	SequenceSprite();
	~SequenceSprite();
public:
	float m_FrameGAP;
	float m_Time;
	int m_FrameCount;
	int m_CurrentFrame;
	GLuint* m_Textures;

	Vector3f m_Mesh[4];
	Vector3f m_Pos;
	GLenum mDstFactor;
	void Init(const char*imageDir, const char *imageName, int startFrame, int EndFrame, int framePerSecond);
	void SetRect(float x, float y, float width, float height);
	void Update(float deltaTime);
	virtual void Draw();
};