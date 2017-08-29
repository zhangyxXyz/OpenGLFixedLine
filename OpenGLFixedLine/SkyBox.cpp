#include "SkyBox.h"



SkyBox::SkyBox()
{
}


SkyBox::~SkyBox()
{
}

void SkyBox::Init(const char * path)
{
	char tmp[128] = { 0 };
	strcpy(tmp, path);
	strcat(tmp, "/front.bmp");
	front = Texture::LoadTexture(tmp);
	strcpy(tmp, path);
	strcat(tmp, "/back.bmp");
	back = Texture::LoadTexture(tmp);
	strcpy(tmp, path);
	strcat(tmp, "/top.bmp");
	top = Texture::LoadTexture(tmp);
	strcpy(tmp, path);
	strcat(tmp, "/bottom.bmp");
	bottom = Texture::LoadTexture(tmp);
	strcpy(tmp, path);
	strcat(tmp, "/left.bmp");
	left = Texture::LoadTexture(tmp);
	strcpy(tmp, path);
	strcat(tmp, "/right.bmp");
	right = Texture::LoadTexture(tmp);
}

void SkyBox::Draw(float x, float y, float z)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor4ub(255, 255, 255, 255);
	//front
	glBindTexture(GL_TEXTURE_2D, front->m_textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
	//left
	glBindTexture(GL_TEXTURE_2D, left->m_textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();
	//right
	glBindTexture(GL_TEXTURE_2D, right->m_textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();
	//top
	glBindTexture(GL_TEXTURE_2D, top->m_textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();
	//bottom
	glBindTexture(GL_TEXTURE_2D, bottom->m_textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glEnd();
	//back
	glBindTexture(GL_TEXTURE_2D, back->m_textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();
}
