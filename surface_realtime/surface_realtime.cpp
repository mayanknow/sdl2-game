// creating a windows in SDL2

// standard c++ library
#include<iostream>

// importing SDL2 header
#include<SDL.h>

int main(int argc, char* argv[])
{
    // creating a window data type
    SDL_Window *window=nullptr;

    // creating the window surface pointer
    SDL_Surface *screen;

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

    // grabbing the window surface
    screen = SDL_GetWindowSurface(window);

    // // image surface pointer
    // SDL_Surface *image;
    // // loading image to the surface
    // image = SDL_LoadBMP("./images/image.bmp");

    // // copying surface to destination surface
    // SDL_BlitSurface(image, NULL, screen, NULL);
    
    // // freeing the memory because it is c/c++ :)
    // SDL_FreeSurface(image);

    // infinite loop for application
    bool gameIsRunning = true;
    while(gameIsRunning)
    {
        SDL_Event event;
        int x, y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x, &y);


        // event loop start
        while(SDL_PollEvent(&event))
        {
            // handle each specific event
            // SQL_QUIT is close button
            if(event.type == SDL_QUIT) {
                gameIsRunning = false;
            }
            if(event.button.button == SDL_BUTTON_LEFT) {
                SDL_LockSurface(screen);
                std::cout << "Left mouse pressed(" << x << ", " << y << ")\n";
                SDL_memset(screen->pixels, 255, screen->h * screen->pitch);
                SDL_UnlockSurface(screen);
                SDL_UpdateWindowSurface(window);
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