#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <iostream>
#include <functional>
using namespace std;

unsigned char* LoadFileContent(const char* filePath);

GLuint CaptureScreen(int width, int height, std::function<void()> foo);
void SaveScreenPixelToFile(int width, int height, std::function<void()> foo, const char*filePath);