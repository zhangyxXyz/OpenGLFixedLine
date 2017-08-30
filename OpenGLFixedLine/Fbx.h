#pragma once
#include <windows.h>
#include <gl/GL.h>
#include "VertexData.h"
#include "Texture.h"
#include "fbxsdk.h"
#include <unordered_map>

struct Mat
{
	int m_Type;//0 lambert 1 phong other : lambert
	char m_DiffuseColorTexture[256];
	Texture *m_Texture;
};


class Fbx
{
public:
	Fbx();
	~Fbx();
public:
	char m_FBXPath[256];
	std::vector<Mat*> m_Materials;//unique mat
	std::vector<std::vector<int>> m_Indices;
	std::unordered_map<int, int> m_MaterialIndexes;
	VertexData* m_Vertices;
	void Init(const char *filePath);
	void Draw();
protected:
	void ImportNode(FbxNode* node);
	void ImportMaterial(FbxNode* node);
	void ImportMesh(FbxMesh* mesh);
};

