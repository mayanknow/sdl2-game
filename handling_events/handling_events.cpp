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
            // SQL_QUIT is close button
            if(event.type == SDL_QUIT) {
                gameIsRunning = false;
            }
            // SDL_ALLCAPITAL is a variable
            // SDL_IfItLooksLikeThis is a function
            if(event.type == SDL_MOUSEMOTION) {
                std::cout << "mouse has been moved\n";
            }

            // SDL_KEYDOWN checks for any event emitted related to keys
            if(event.type == SDL_KEYDOWN) {
                // event.key.keysm.sym
                // keysym is a key symbol union which has a sym value
                // SDLK_0 is teh 0 key on the keyboard
                if(event.key.keysym.sym == SDLK_0) {
                    std::cout << "0 was pressed\n";
                } else {
                    std::cout << "0 was not pressed\n";
                }
            }

            // getting input values from the keyborad snapshort
            // Uint8 is an unsigned integer
            // No negative values are expected so unsigned
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_RIGHT]) {
                std::cout << "Right arrow key is pressed\n";
            }
        }
    }

    // destroying created window
    SDL_DestroyWindow(window);

    // SDL exit/quit function
    SDL_Quit();

    return 0;
}