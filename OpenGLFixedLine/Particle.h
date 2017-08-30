#pragma once
#include "ImageSprite.h"
class Particle:public ImageSprite
{
public:
	Particle();
	Particle(bool bRoot = false);
	~Particle();
public:
	bool m_Root;
	float m_LifeTime;
	float m_ExistTime;
	float m_DelayTime;
	Vector3f m_OriginalPos;
	void Update(float deltaTime);
	void Draw();
	static void InitSpeeds();
};