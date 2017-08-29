#include "Button.h"



Button::Button() :m_OffsetY(0.0f), m_ClickHandler(nullptr)
{
}


Button::~Button()
{
}

Button * Button::OnTouchBegin(int x, int y)
{
	//printf("%d, %d", x, y);
	if (x > m_MinX&&x<m_MaxX&&
		y>m_MinY&&y < m_MaxY)
	{
		m_OffsetY = -4.0f;
		return this;
	}
	Button*ret = nullptr;
	if (nullptr != m_Next)
	{
		ret = Next<Button>()->OnTouchBegin(x, y);
	}
	return ret;
}

Button * Button::OnTouchEnd(int x, int y)
{
	if (x > m_MinX&&x<m_MaxX&&
		y>m_MinY&&y < m_MaxY)
	{
		if (m_ClickHandler != nullptr)
		{
			m_ClickHandler();
		}
		return this;
	}
	Button*ret = nullptr;
	if (nullptr != m_Next)
	{
		ret = Next<Button>()->OnTouchEnd(x, y);
	}
	return ret;
}

void Button::ResetState()
{
	m_OffsetY = 0.0f;
	if (nullptr != m_Next)
	{
		Next<Button>()->ResetState();
	}
}

void Button::SetOnClick(std::function<void()> foo)
{
	m_ClickHandler = foo;
}

void Button::SetRect(float x, float y, float width, float height)
{
	m_MinX = x - width / 2;
	m_MaxX = x + width / 2;
	m_MinY = y - height / 2;
	m_MaxY = y + height / 2;
	m_DefaultSprite->SetRect(x, y, width, height);
}

void Button::SetDefaultSprite(ImageSprite* sprite)
{
	m_DefaultSprite = sprite;
}

void Button::Draw()
{
	//draw
	glPushMatrix();
	glTranslatef(0.0f, m_OffsetY, 0.0f);
	m_DefaultSprite->Draw();
	glPopMatrix();
	RenderableObject::Draw();
}
