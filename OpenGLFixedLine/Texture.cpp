#include "Texture.h"
#include "Utils.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

unsigned char* DecodeBmp(unsigned char* bmpFileData, int& width, int& height)
{
	// if data at the beginning is 0x4D42, this is a bmp format file
	if (0x4D42 == *((unsigned short*)bmpFileData))
	{
		int pixelDataOffset = *((int*)(bmpFileData + 10));
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));
		unsigned char* pixelData = bmpFileData + pixelDataOffset;
		// bgr bgr bgr ... transcoding to rgb rgb rgb
		for (int i = 0;i < width*height * 3;i += 3)
		{
			pixelData[i] ^= pixelData[i + 2] ^= pixelData[i] ^= pixelData[i + 2];
		}
		return pixelData;
	}
	else
	{
		return nullptr;
	}
}

void Texture::Init(const char * imgPath)
{
	// load image file from disk to memory
	unsigned char* imageFileContent = LoadFileContent(imgPath);
	// decode image
	int width = 0, height = 0;
	unsigned char* pixelData = DecodeBmp(imageFileContent, width, height);
	// generate an openGL image
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	// operation on current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete imageFileContent;
}
