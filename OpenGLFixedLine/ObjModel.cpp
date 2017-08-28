#include "ObjModel.h"
#include "Utils.h"
#include <string>
#include <sstream>
#include <vector>

ObjModel::ObjModel()
{
}


ObjModel::~ObjModel()
{
}

void ObjModel::Init(const char * objModel)
{
	struct FloatData
	{
		float v[3];
	};

	// face
	struct VerticeDefine
	{
		int posIndex;
		int texcoordIndex;
		int normalIndex;
	};

	std::vector<FloatData> positions, texcoords, normals;
	std::vector<VerticeDefine> vertexes;//unique vertex
	std::vector<int> indexes;
	unsigned char* fileContent = LoadFileContent(objModel);
	//printf("%s\n", fileContent);
	std::stringstream ssFileContent((char*)fileContent);
	std::string tmp;
	char szOneLine[256];
	while (!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);
		//std::cout<< ">" << szOneLine << std::endl;
		if (strlen(szOneLine) > 0)
		{
			if (szOneLine[0] == 'v')
			{
				std::stringstream ssOneLine(szOneLine);
				if (szOneLine[1] == 't')
				{
					ssOneLine >> tmp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					texcoords.push_back(floatData);
					//printf("texcoord : %f,%f\n", floatData.v[0], floatData.v[1]);
				}
				else if (szOneLine[1] == 'n')
				{
					ssOneLine >> tmp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normals.push_back(floatData);
					//printf("normal : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
				else
				{
					ssOneLine >> tmp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					positions.push_back(floatData);
					//printf("position : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
			}
			else if (szOneLine[0] == 'f')
			{
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> tmp;
				std::string vertexStr;// 1/1/1
				for (int i = 0;i < 3;++i)
				{
					ssOneLine >> vertexStr;
					size_t pos = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos);
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
					VerticeDefine vd;
					vd.posIndex = atoi(posIndexStr.c_str());
					vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
					vd.normalIndex = atoi(normalIndexStr.c_str());
					//printf("f : %d,%d,%d\n", vd.posIndex, vd.texcoordIndex, vd.normalIndex);
					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int)vertexes.size();
					for (int j = 0;j < nCurrentVertexCount;++j)
					{
						if (vertexes[j].posIndex == vd.posIndex&&
							vertexes[j].normalIndex == vd.normalIndex&&
							vertexes[j].texcoordIndex == vd.texcoordIndex)
						{
							nCurrentVertexIndex = j;
							break;
						}
					}
					if (nCurrentVertexIndex == -1)
					{
						nCurrentVertexIndex = (int)vertexes.size();
						vertexes.push_back(vd);
					}
					indexes.push_back(nCurrentVertexIndex);
				}
				//std::cout << "face : " << szOneLine << std::endl;
			}
		}
	}
	printf("unique vertex count %u index count %u\n", vertexes.size(), indexes.size());
	m_IndexCount = (int)indexes.size();
	m_Indices = new int[m_IndexCount];
	for (int i = 0;i < m_IndexCount;++i)
	{
		m_Indices[i] = indexes[i];
	}
	int vertexCount = (int)vertexes.size();
	m_VertextData = new VertexData[vertexCount];
	for (int i = 0;i < vertexCount;++i)
	{
		memcpy(m_VertextData[i].position, positions[vertexes[i].posIndex - 1].v, sizeof(float) * 3);
		memcpy(m_VertextData[i].texcoord, texcoords[vertexes[i].texcoordIndex - 1].v, sizeof(float) * 2);
		memcpy(m_VertextData[i].normal, normals[vertexes[i].normalIndex - 1].v, sizeof(float) * 3);
	}
	delete fileContent;
}

void ObjModel::Draw()
{
	static float angle = 0.0f;
	angle += 0.3f;
	if (angle >= 360.0f)
	{
		angle = 0.0f;
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < m_IndexCount; ++i)
	{
		glTexCoord2fv(m_VertextData[m_Indices[i]].texcoord);
		glNormal3fv(m_VertextData[m_Indices[i]].normal);
		glVertex3fv(m_VertextData[m_Indices[i]].position);
	}
	glEnd();
	glPopMatrix();
}