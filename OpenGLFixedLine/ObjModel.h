#pragma once
#include "VertexData.h"
class ObjModel
{
public:
	ObjModel();
	~ObjModel();
public:
	VertexData* m_VertextData;
	int *m_Indices;
	int m_IndexCount;

	void Init(const char* objModel);
	void Draw();
};

