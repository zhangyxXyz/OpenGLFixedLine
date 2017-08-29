#pragma once
#include "ImageSprite.h"
#include <functional>

class Button:public RenderableObject
{
public:
	Button();
	~Button();
public:
	float m_MinX;
	float m_MaxX;
	float m_MinY;
	float m_MaxY;
	float m_OffsetY;
	ImageSprite* m_DefaultSprite;
	std::function<void()> m_ClickHandler;

	Button* OnTouchBegin(int x, int y);
	Button* OnTouchEnd(int x, int y);
	void ResetState();
	void SetOnClick(std::function<void()> foo);

	void SetRect(float x, float y, float width, float height);
	void SetDefaultSprite(ImageSprite* sprite);
	void Draw();
};

