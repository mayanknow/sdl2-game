// creating a windows in SDL2

// standard c++ library
#include<iostream>

// importing SDL2 header
#include<SDL.h>

// set-pixel function
// uint8_t is unsigned 8-bit integer non-negative values
void SetPixel(SDL_Surface *surface, int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    SDL_LockSurface(surface);
    std::cout << "Left mouse pressed(" << x << ", " << y << ")\n";
    uint8_t *pixelArray = (uint8_t *) surface->pixels;
    // here pitch is the total number of bytes in  a row
    /*      x
        ------------->
        |  1 2 3 4 5
      y |  1 2 X 4 5
        |  1 2 3 4 5
        \/
        There are 5 elements in each row
        so the pitch will be 6
        **
        to reach the 3rd element of 2nd row
        we multiply y with pitch and add the element
        X is the third element
        **
    */

    // BGR format is used here
    pixelArray[y*surface->pitch +x*surface->format->BytesPerPixel+0] = b;
    pixelArray[y*surface->pitch +x*surface->format->BytesPerPixel+1] = g;
    pixelArray[y*surface->pitch +x*surface->format->BytesPerPixel+2] = r;
    SDL_UnlockSurface(surface);
}

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
            // if(event.button.button == SDL_BUTTON_LEFT) {
            //     SetPixel(screen, x, y, 255, 0 ,0);
            // }

            // getting input values from the keyborad snapshort
            // Uint8 is an unsigned integer
            // No negative values are expected so unsigned
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            /*
                **MORTAL KOMBAT COMBO** 
            */
            // Right button + left click => red color
            if(state[SDL_SCANCODE_RIGHT] && event.button.button == SDL_BUTTON_LEFT) {
                SetPixel(screen, x, y, 255, 0 ,0);
                std::cout << "Left arrow key is pressed\n";
            }
            // Left button + left click => green color
            if(state[SDL_SCANCODE_LEFT] && event.button.button == SDL_BUTTON_LEFT) {
                SetPixel(screen, x, y, 0, 255 ,0);
                std::cout << "Right arrow key is pressed\n";
            }
        }
        // updating window ever frame in game loop
        SDL_UpdateWindowSurface(window);
    }

    // destroying created window
    SDL_DestroyWindow(window);

    // SDL exit/quit function
    SDL_Quit();

    return 0;
}