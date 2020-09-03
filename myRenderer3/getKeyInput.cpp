#include <stdio.h>

#include "engine.h"
#include "sdl/SDL.h"
#include "getKeyInput.h"
#include "logger.h"

void getKeyInput()
{
    SDL_Event e;
    //Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
            setIsDone(true);
        }
        //User presses a key
        else if (e.type == SDL_KEYDOWN)
        {
            //Select surfaces based on key press
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                setIsDone(true);
                break;
            default:
                break;
            }
            printf("The key '%c' is pressed\n", e.key.keysym.sym);
        }
    }
}
