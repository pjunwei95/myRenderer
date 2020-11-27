#include "include/sdl/SDL.h"
#include "getKeyInput.h"
#include "profileManager.h"


void getKeyInput()
{
    SDL_Event e;
    //Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
            //setIsDone(true);
            Engine::Instance().SetIsDone(true);
        }
        //User presses a key
        else if (e.type == SDL_KEYDOWN)
        {
            //Select surfaces based on key press
            logfile("The key '%c' is pressed\n", e.key.keysym.sym);
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                //setIsDone(true);
                Engine::Instance().SetIsDone(true);
                break;
            case SDLK_p:
                logfile("Dumping profile logs:\n");
                ProfileManager::Instance().PrintBufferProfile();
                ProfileInfo::Instance().DumpProfileInfo();
                break;

            default:
                break;
            }
        }
    }
}
