#include "ImageSprite.h"



ImageSprite::ImageSprite()
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
