#include "FontManager.h"
#include <unordered_map>

HDC sDC = nullptr;
GLuint text;
static std::unordered_map<wchar_t, GLuint> sCachedChars;

FontManager::FontManager()
{
}


FontManager::~FontManager()
{
}

void FontManager::Init(HDC dc)
{
	sDC = dc;
	HFONT hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"ËÎÌו");
	SelectObject(dc, hFont);
}

void FontManager::Draw(wchar_t*str)
{
	int len = lstrlen(str);
	for (int i = 0;i < len;++i)
	{
		auto iter = sCachedChars.find(str[i]);
		if (iter == sCachedChars.end())
		{
			text = glGenLists(1);
			wglUseFontBitmaps(sDC, str[i], 1, text);
			sCachedChars.insert(std::pair<wchar_t, GLuint>(str[i], text));
		}
		glCallList(sCachedChars[str[i]]);
	}
}