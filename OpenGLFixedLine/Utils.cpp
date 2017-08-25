#include "Utils.h"

unsigned char * LoadFileContent(const char * filePath)
{
	unsigned char* fileContent = nullptr;
	FILE* pFile = nullptr;
	if (0 == fopen_s(&pFile, filePath, "rb"))
	{
		//read
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);
		if (nLen > 0)
		{
			rewind(pFile);
			fileContent = new unsigned char[nLen + 1];
			fread(fileContent, sizeof(unsigned char), nLen, pFile);
			fileContent[nLen] = '\0';
		}
		fclose(pFile);
	}
	else
	{
		cout << "file open failed" << endl;
	}
	return fileContent;
}
