// creating a windows in SDL2

// standard c++ library
#include<iostream>

// importing SDL2 header
#include<SDL.h>

int main(int argc, char* argv[])
{
    // creating a window data type
    SDL_Window *window=nullptr;

    // error checking for sdl
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized\n";
        SDL_GetError();
    } else {
        std::cout << "Video system is ready to go\n";
    }

    // creating a windows using SDL_CreateWindow function
    window = SDL_CreateWindow("C++ SDL2 Window",
    0,
    0,
    640,
    480,
    SDL_WINDOW_SHOWN);      // SDL_WINDOW_SHOWN is ignored by SDL_CreateWindow

    // infinite loop for application
    bool gameIsRunning = true;
    while(gameIsRunning)
    {
        SDL_Event event;
        // event loop start
        while(SDL_PollEvent(&event))
        {
            // handle each specific event
            if(event.type == SDL_QUIT) {
                gameIsRunning = false;
            }
        }
    }

    // destroying created window
    SDL_DestroyWindow(window);

    // SDL exit/quit function
    SDL_Quit();

    return 0;
}