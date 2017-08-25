#include "ObjModel.h"
#include "Utils.h"
#include <string>
#include <sstream>


ObjModel::ObjModel()
{
}


ObjModel::~ObjModel()
{
}

void ObjModel::Init(const char * objModel)
{
	unsigned char* fileContent = LoadFileContent(objModel);
	//printf("%s\n", fileContent);
	std::stringstream ssFileContent((char*)fileContent);
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
				if (szOneLine[1] == 't')
				{
					std::cout << "texcoord : " << szOneLine << std::endl;
				}
				else if (szOneLine[1] == 'n')
				{
					std::cout << "normal : " << szOneLine << std::endl;
				}
				else
				{
					std::cout << "position : " << szOneLine << std::endl;
				}
			}
			else if (szOneLine[0] == 'f')
			{
				std::cout << "face : " << szOneLine << std::endl;
			}
		}
	}
	delete fileContent;
}

void ObjModel::Draw()
{

}
