#define SDL_MAIN_HANDLED
#include "sdl/SDL.h"
#include <windows.h>
#include <stdio.h>

//#pragma comment (lib, "opengl32.lib")
#define FPS 30
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

BOOL isDone = FALSE;


void runFrameController();

void drawScreen(SDL_Surface * screenSurface);

void drawTriangles();

void drawWindow();



int main()
{
	runFrameController();
	return 0;
}



void runFrameController()
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	LARGE_INTEGER nFrequency;
	QueryPerformanceFrequency(&nFrequency);

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			while (!isDone)
			{
				// get start
				LARGE_INTEGER nStartTime;

				// get elapsed time
				// 1s = 1 000 000 micro s = 30 frames
				LARGE_INTEGER  frameTime;
				frameTime.QuadPart = 1000000 / FPS;

				QueryPerformanceCounter(&nStartTime);

				//Get window surface
				screenSurface = SDL_GetWindowSurface(window);

				//Fill the surface white
				drawScreen(screenSurface);

				//Update the surface
				SDL_UpdateWindowSurface(window);
				//Wait two seconds
				//SDL_Delay(2000);

				while (1)
				{
					LARGE_INTEGER nStopTime;
					// get new elapsed time
					// if (new elapsed time - start
					QueryPerformanceCounter(&nStopTime);
					nStopTime.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
					nStopTime.QuadPart /= nFrequency.QuadPart;
					if (nStopTime.QuadPart > frameTime.QuadPart) {
						printf("%.2f\n", (float)nStopTime.QuadPart / 1000);
						break;
					}
				}
			}
		}
	}
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
}

void drawScreen(SDL_Surface * screenSurface)
{
	//fill rectangle on screen
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

	//draw triangle
	drawTriangles();
}

void drawTriangles()
{
	

	
}


