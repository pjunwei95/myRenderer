#pragma once
#include <windows.h>

#define FPS 30

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void setIsDone(BOOL value);

BOOL getIsDone();
