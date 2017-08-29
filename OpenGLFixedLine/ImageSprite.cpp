#include "ImageSprite.h"



ImageSprite::ImageSprite():m_Alpha(255), m_FadeIn(false), m_FadeOut(false)
{
}


ImageSprite::~ImageSprite()
{
}

void ImageSprite::SetTexture(Texture * texture)
{
	m_Texture = texture;
}

void ImageSprite::SetRect(float x, float y, float width, float height)
{
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	m_Mesh[0].x = x - halfWidth;
	m_Mesh[0].y = y - halfHeight;

	m_Mesh[1].x = x + halfWidth;
	m_Mesh[1].y = y - halfHeight;

	m_Mesh[2].x = x + halfWidth;
	m_Mesh[2].y = y + halfHeight;

	m_Mesh[3].x = x - halfWidth;
	m_Mesh[3].y = y + halfHeight;
}

void ImageSprite::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glColor4ub(255, 255, 255, m_Alpha);
	glBindTexture(GL_TEXTURE_2D, m_Texture->m_textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Mesh[0].v);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Mesh[1].v);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Mesh[2].v);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Mesh[3].v);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}

void ImageSprite::FadeIn(float duration)
{
	if (!(m_FadeIn || m_FadeOut))
	{
		m_FadeIn = true;
		m_FadeSpeed = int(255.0f / duration);
	}
}

void ImageSprite::FadeOut(float duration)
{
	if (!(m_FadeIn || m_FadeOut))
	{
		m_FadeOut = true;
		m_FadeSpeed = int(255.0f / duration);
	}
}

void ImageSprite::Update(float deltaTime)
{
	if (m_FadeIn)
	{
		int alpha = m_Alpha;
		alpha += int(m_FadeSpeed*deltaTime);
		m_Alpha = alpha > 255 ? 255 : alpha;
		if (m_Alpha == 255)
		{
			m_FadeIn = false;
		}
		
	}
	else if (m_FadeOut)
	{
		int alpha = m_Alpha;
		alpha -= int(m_FadeSpeed*deltaTime);
		m_Alpha = alpha < 0 ? 0 : alpha;
		if (m_Alpha == 0)
		{
			m_FadeOut = false;
		}
	}
}
