#include "DisplayList.h"



DisplayList::DisplayList()
{
}


DisplayList::~DisplayList()
{
}

void DisplayList::Init(std::function<void()> foo)
{
	m_DisplayList = glGenLists(1);
	glNewList(m_DisplayList, GL_COMPILE);
	foo();
	glEndList();
}

void DisplayList::Draw()
{
	glCallList(m_DisplayList);
}
