#include "Fbx.h"
#include "Vector3f.h"
#include <vector>
#pragma comment(lib,"libfbxsdk-md.lib")

Fbx::Fbx()
{
}


Fbx::~Fbx()
{
}

void ImportPositions(FbxGeometryBase* geometry, std::vector<Vector3f>& positions)
{
	int controlPointCount = geometry->GetControlPointsCount();
	positions.resize(controlPointCount);
	printf("my control point count %d\n", controlPointCount);
	FbxVector4* controlPoints = geometry->GetControlPoints();
	for (int i = 0;i < controlPointCount;++i)
	{
		positions[i].x = static_cast<float>(controlPoints[i].mData[0]);
		positions[i].y = static_cast<float>(controlPoints[i].mData[1]);
		positions[i].z = static_cast<float>(controlPoints[i].mData[2]);
		//printf("%f,%f,%f\n", positions[i].x, positions[i].y, positions[i].z);
	}
}

void GetMaterialPath(char *path)
{
	memset(path + strlen(path) - 4, 0, 4);
	strcat(path, ".fbm/");
}

void Fbx::Init(const char * filePath)
{
	memset(m_FBXPath, 0, 256);
	strcpy_s(m_FBXPath, filePath);
	FbxManager* fbxManager = FbxManager::Create();
	FbxIOSettings* fbxIOSetting = FbxIOSettings::Create(fbxManager, IOSROOT);
	FbxImporter* fbxImporter = FbxImporter::Create(fbxManager, "");
	fbxManager->SetIOSettings(fbxIOSetting);
	if (fbxImporter->Initialize(filePath, -1, fbxManager->GetIOSettings()))
	{
		FbxScene* scene = FbxScene::Create(fbxManager, "");
		fbxImporter->Import(scene);

		FbxNode* rootNode = scene->GetRootNode();
		ImportNode(rootNode);
		scene->Destroy();
	}
	fbxImporter->Destroy();
	fbxIOSetting->Destroy();
	fbxManager->Destroy();
}

void Fbx::Draw()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glScalef(0.01f, 0.01f, 0.01f);
	for (int i = 0;i < m_Materials.size();i++)
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.01f);
		glBindTexture(GL_TEXTURE_2D, m_Materials[i]->m_Texture->m_textureID);
		glBegin(GL_TRIANGLES);
		for (int j = 0;j < m_Indices[i].size();++j)
		{
			glTexCoord2fv(m_Vertices[m_Indices[i][j]].texcoord);
			glVertex3fv(m_Vertices[m_Indices[i][j]].position);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_ALPHA_TEST);
}

void Fbx::ImportNode(FbxNode * node)
{
	// decode per node
	//printf("decode %s\n", node->GetName());
	if (node->GetMesh())
	{
		//printf("decode mesh of %s\n", node->GetName());
		ImportMaterial(node);
		ImportMesh(node->GetMesh());
		for (int i = 0;i < m_Materials.size();++i)
		{
			printf("%d %s %u\n", m_Materials[i]->m_Type, m_Materials[i]->m_DiffuseColorTexture, m_Indices[i].size());
		}
		for (auto iter = m_MaterialIndexes.begin();iter != m_MaterialIndexes.end();++iter)
		{
			printf("mat index %d -> %d\n", iter->first, iter->second);
		}
	}
	//decode child
	int nChildNode = node->GetChildCount();
	for (int i = 0;i < nChildNode;++i)
	{
		ImportNode(node->GetChild(i));
	}
}

void Fbx::ImportMaterial(FbxNode * node)
{
	char szFBXTextureDir[256] = { 0 };
	strcpy_s(szFBXTextureDir, m_FBXPath);
	GetMaterialPath(szFBXTextureDir);
	int materialCount = node->GetMaterialCount(); 
	printf("material count %d\n", materialCount);
	FbxProperty property;
	int nType = 0;
	for (int i = 0;i < materialCount;++i)
	{
		FbxSurfaceMaterial*surfaceMat = node->GetMaterial(i);
		if (FbxSurfaceLambert::ClassId == surfaceMat->GetClassId())
		{
			nType = 0;
			printf("%d lambert material %s\n", i, surfaceMat->GetName());
		}
		else if (FbxSurfacePhong::ClassId == surfaceMat->GetClassId())
		{
			nType = 1;
			printf("%d phong material %s\n", i, surfaceMat->GetName());
		}
		else
		{
			printf("i cannot understand why you do that\n");
		}
		property = surfaceMat->FindProperty(FbxLayerElement::sTextureChannelNames[0]);//diffuse texture
		if (property.IsValid())
		{
			int textureCount = property.GetSrcObjectCount<FbxTexture>();
			int nCurrenMaterialIndex = -1;
			FbxTexture* texture = property.GetSrcObject<FbxTexture>();
			if (texture)
			{
				printf("texture name %s\n", texture->GetName());
				int currentMatCount = (int)m_Materials.size();
				for (int k = 0;k < currentMatCount;++k)
				{
					if (nType == m_Materials[k]->m_Type)
					{
						if (strcmp(texture->GetName(), m_Materials[k]->m_DiffuseColorTexture) == 0)
						{
							nCurrenMaterialIndex = k;
							break;
						}
					}
					else if (nType == m_Materials[k]->m_Type)
					{
						if (strcmp(texture->GetName(), m_Materials[k]->m_DiffuseColorTexture) == 0)
						{
							nCurrenMaterialIndex = k;
							break;
						}
					}
				}
				if (nCurrenMaterialIndex == -1)
				{
					//
					Mat*mat = new Mat;
					mat->m_Type = nType;
					memset(mat->m_DiffuseColorTexture, 0, 256);
					strcpy_s(mat->m_DiffuseColorTexture, texture->GetName());
					char temp[256] = { 0 };
					strcpy_s(temp, szFBXTextureDir);
					strcat(temp, texture->GetName());
					mat->m_Texture = Texture::LoadTexture(temp);
					nCurrenMaterialIndex = (int)m_Materials.size();
					m_Materials.push_back(mat);
				}
				m_MaterialIndexes.insert(std::pair<int, int>(i, nCurrenMaterialIndex));
			}
		}
	}
}

void Fbx::ImportMesh(FbxMesh * mesh)
{
	std::vector<Vector3f> positions;
	ImportPositions(mesh, positions);
	//indices
	int polygonCount = mesh->GetPolygonCount();//triangle count

	FbxStringList uvSetNames;
	mesh->GetUVSetNames(uvSetNames);

	int polygonIndexCount = 0;
	for (int i = 0;i < polygonCount;++i)
	{
		polygonIndexCount += mesh->GetPolygonSize(i);
	}

	FbxLayerElementArrayTemplate<int>*pMaterialIndices;
	mesh->GetMaterialIndices(&pMaterialIndices);
	FbxGeometryElement::EMappingMode mode = mesh->GetElementMaterial()->GetMappingMode();
	m_Indices.resize(m_Materials.size());
	switch (mode)
	{
	case fbxsdk::FbxLayerElement::eNone:
		break;
	case fbxsdk::FbxLayerElement::eByControlPoint:
		break;
	case fbxsdk::FbxLayerElement::eByPolygonVertex:
		break;
	case fbxsdk::FbxLayerElement::eByPolygon:
	{
		for (int i = 0;i < polygonCount;++i)
		{
			//0~13
			int materialIndex = pMaterialIndices->GetAt(i);
			int materialRef = m_MaterialIndexes[materialIndex];
			m_Indices[materialRef].push_back(i * 3);
			m_Indices[materialRef].push_back(i * 3 + 1);
			m_Indices[materialRef].push_back(i * 3 + 2);
		}
	}
	break;
	case fbxsdk::FbxLayerElement::eByEdge:
		break;
	case fbxsdk::FbxLayerElement::eAllSame:
		break;
	}

	m_Vertices = new VertexData[polygonIndexCount];
	int currentVerticeIndex = 0;
	for (int i = 0;i < polygonCount;++i)
	{
		int currentPolygonIndexCount = mesh->GetPolygonSize(i);//3
		for (int j = 0;j < currentPolygonIndexCount;++j)
		{
			int vertexIndex = mesh->GetPolygonVertex(i, j);
			// fbx positions -> our position
			m_Vertices[currentVerticeIndex].position[0] = positions[vertexIndex].x;
			m_Vertices[currentVerticeIndex].position[1] = positions[vertexIndex].y;
			m_Vertices[currentVerticeIndex].position[2] = positions[vertexIndex].z;
			//printf("position:\n%f,%f,%f\n", positions[vertexIndex].x, positions[vertexIndex].y, positions[vertexIndex].z);
			// pos,normal,texcoord
			FbxVector4 normal;
			if (mesh->GetPolygonVertexNormal(i, j, normal))
			{
				// fbx normal -> our normal
				m_Vertices[currentVerticeIndex].normal[0] = static_cast<float>(normal.mData[0]);
				m_Vertices[currentVerticeIndex].normal[1] = static_cast<float>(normal.mData[1]);
				m_Vertices[currentVerticeIndex].normal[2] = static_cast<float>(normal.mData[2]);
				//printf("normal:\n%f,%f,%f\n", static_cast<float>(normal.mData[0]), static_cast<float>(normal.mData[1]), static_cast<float>(normal.mData[2]));
			}

			FbxVector2 uv;
			bool bFlag = true;
			if (mesh->GetPolygonVertexUV(i, j, uvSetNames.GetItemAt(0)->mString.Buffer(), uv, bFlag))
			{
				// fbx texcoord -> our texcoord
				m_Vertices[currentVerticeIndex].texcoord[0] = static_cast<float>(uv.mData[0]);
				m_Vertices[currentVerticeIndex].texcoord[1] = static_cast<float>(uv.mData[1]);
				//printf("texcoord:\n%f,%f\n", static_cast<float>(uv.mData[0]), static_cast<float>(uv.mData[1]));
			}
			currentVerticeIndex++;
		}
	}
}
