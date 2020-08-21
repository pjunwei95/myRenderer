#pragma once

#define FPS 30

BOOL isDone = FALSE;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char * argsv[]);

void runFrameController();

void getKeyInput();

void drawScreen(SDL_Surface * screenSurface);

