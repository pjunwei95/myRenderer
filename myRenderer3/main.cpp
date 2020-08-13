
#define SDL_MAIN_HANDLED
#include "sdl/SDL.h"
#include <windows.h>
#include <stdio.h>

//#pragma comment (lib, "opengl32.lib")
#define FPS 30

BOOL isDone = FALSE;




void runMessageLoop();

void test();

int main()
{
	
	runMessageLoop();

	return 0;
}

void test() {
	//printf("OpenGL version = %s\n", (char*)glGetString(GL_VERSION));

}

void runMessageLoop()
{
	LARGE_INTEGER nFrequency;
	QueryPerformanceFrequency(&nFrequency);
	while (!isDone)
	{
		// get start
		LARGE_INTEGER nStartTime;

		// get elapsed time
		// 1s = 1 000 000 micro s = 30 frames
		// 1/30 = 1 frame
		// x < 1/30
		LARGE_INTEGER  frameTime;
		frameTime.QuadPart = 1000000 / FPS;

		QueryPerformanceCounter(&nStartTime);



		while (1)
		{
			LARGE_INTEGER nStopTime;
			// get new elapsed time
			// if (new elapsed time - start
			QueryPerformanceCounter(&nStopTime);
			nStopTime.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
			nStopTime.QuadPart /= nFrequency.QuadPart;
			if (nStopTime.QuadPart > frameTime.QuadPart) {
				break;
			}
		}
		//printf("%f\n", (float) nElapsed.QuadPart / 1000);
	}
}

