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

GLuint CaptureScreen(int width, int height, std::function<void()> foo)
{
	foo();
	unsigned char * screenPixel = new unsigned char[width*height * 3];
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, screenPixel);
	GLuint texture;
	//generate an opengl texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//operation on current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, screenPixel);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete screenPixel;
	return texture;
}

// save screenshot
void SaveScreenPixelToFile(int width, int height, std::function<void()> foo, const char * filePath)
{
	foo();
	unsigned char * screenPixel = new unsigned char[width*height * 3];
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, screenPixel);

	FILE*pFile = nullptr;
	if (0 == fopen_s(&pFile, filePath, "wb"))
	{
		BITMAPFILEHEADER bfh;
		memset(&bfh, 0, sizeof(BITMAPFILEHEADER));
		bfh.bfType = 0x4D42;
		bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + width*height * 3;
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, pFile);

		BITMAPINFOHEADER bih;
		memset(&bih, 0, sizeof(BITMAPINFOHEADER));
		bih.biWidth = width;
		bih.biHeight = height;
		bih.biBitCount = 24;
		bih.biSize = sizeof(BITMAPINFOHEADER);
		fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, pFile);

		//rgb -> bgr
		for (int i = 0; i < width*height * 3; i += 3)
		{
			screenPixel[i] ^= screenPixel[i + 2] ^= screenPixel[i] ^= screenPixel[i + 2];
		}
		fwrite(screenPixel, 1, width*height * 3, pFile);
		fclose(pFile);
	}
	printf("save success\n");
}
