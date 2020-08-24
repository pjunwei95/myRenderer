#define SDL_MAIN_HANDLED
//#pragma comment (lib, "opengl32.lib")
#include <windows.h>
#include <stdio.h>

#include "sdl/SDL.h"
#include "sdl/SDL_video.h"
#include "main.h"
#include "checkArgs.h"

int main(int argc, char *argsv[])
{
    checkArgs(argc, argsv);
    printf("Press ESC to exit the application\n");
	runFrameController();
	return 0;
}

void runFrameController()
{
	//SDL Properties
    //The window we'll be rendering to
	SDL_Window* window = NULL;
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

    // Windows properties
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
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

                getKeyInput();

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
						//printf("%.2f\n", (float)nStopTime.QuadPart / 1000);
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

void getKeyInput()
{
    SDL_Event e;
    //Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
            isDone = true;
        }
        //User presses a key
        else if (e.type == SDL_KEYDOWN)
        {
            //Select surfaces based on key press
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                isDone = true;
                break;
            default:
                break;
            }
            printf("The key '%c' is pressed\n", e.key.keysym.sym);
        }
    }
}

void drawScreen(SDL_Surface * screenSurface)
{
	//fill rectangle on screen
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));

}

