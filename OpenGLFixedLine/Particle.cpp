#include "Particle.h"
#include "Utils.h"

static Vector3f speeds[100];
Particle::Particle()
{
}

Particle::Particle(bool bRoot) :m_Root(bRoot)
{
	m_LifeTime = 4.0f + 2.0f*randf();
	m_DelayTime = 4.0f*randf();
	m_ExistTime = 0.0f;
	m_OriginalPos.x = 640.0f*srandf();//-640.0f~640.0f
	m_OriginalPos.y = -360.0f + 20.0f*randf();//-360.0f~-340.0f
	m_Pos = m_OriginalPos;
	m_R = 120;
	m_G = 80;
	m_B = 25;
	m_DstFactor = GL_ONE;
	m_Alpha = 0;
}


Particle::~Particle()
{
}

void Particle::Update(float deltaTime)
{
	if (!m_Root)
	{
		m_ExistTime += deltaTime;
		if (m_ExistTime > m_DelayTime)
		{
			m_Alpha = 255;
			int speedIndex = int(100 * randf());
			speedIndex = speedIndex >= 100 ? 99 : speedIndex;
			m_Pos = m_Pos + speeds[speedIndex] * deltaTime*100.0f;
			if (m_ExistTime > (m_LifeTime + m_DelayTime))
			{
				m_Pos = m_OriginalPos;
				m_ExistTime = 0.0f;
			}
		}
	}

	if (m_Next != nullptr)
	{
		Next<Particle>()->Update(deltaTime);
	}
}

void Particle::Draw()
{
	if (!m_Root)
	{
		ImageSprite::Draw();
	}
	if (m_Next != nullptr)
	{
		Next<Particle>()->Draw();
	}
}

void Particle::InitSpeeds()
{
	for (int i = 0;i < 100;++i)
	{
		speeds[i] = Vector3f(srandf(), randf(), 0.0f);
	}
}