#pragma once
typedef SDL_Window * WindowHandle;
typedef SDL_Surface * SurfaceHandle;

void initWindow();

bool createWindow();

void drawWindow();

void updateWindow();

void destroyWindow();
