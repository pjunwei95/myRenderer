#pragma once
#include <Windows.h>

#define FPS 30

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void setGlobals();

void setIsDone(bool value);

bool getIsDone();

void setSystemFrequency();

LARGE_INTEGER getSystemFrequency();

