#pragma once
#include <windows.h>
#include <gl/GL.h>
class VertexData
{
public:
	VertexData();
	~VertexData();
public:
	float position[3];
	float normal[3];
	float texcoord[3];
};

