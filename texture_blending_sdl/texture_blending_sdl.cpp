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
    // SDL_WINDOW_SHOWN is ignored by SDL_CreateWindow
    window = SDL_CreateWindow("C++ SDL2 Window", 0, 0, 640, 480, SDL_WINDOW_SHOWN);

    // creating an SDL_Renderer pointer
    SDL_Renderer *renderer = nullptr;

    // initializing SDL_Renderer
    // here "-1" will make choose sdl rendering driver automatically
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // create a surface and load a BMP
    SDL_Surface *surface = SDL_LoadBMP("./images/kong.bmp");

    // adding color key before making the surface a texture
    // takes surface as a parameter
    // SDL_MapRGB function uses surface format pointer and returns selected pixel
    //  255, 0, 255 in RGBA is Magenta which is the color key
    // The retured pixels will be the transparent pixels
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));


    // create a texture from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Free surface after the operation
    SDL_FreeSurface(surface);

    // create a reactangle
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 50;
    rectangle.w = 200;
    rectangle.h = 200;

    // create a second reactangle
    SDL_Rect rectangle2;
    rectangle2.x = 50;
    rectangle2.y = 50;
    rectangle2.w = 200;
    rectangle2.h = 200;


    // infinite loop for application
    bool gameIsRunning = true;
    while(gameIsRunning)
    {
        SDL_Event event;
        // (1) handle inputs
        // event loop start
        while(SDL_PollEvent(&event))
        {
            // handle each specific event
            // SQL_QUIT is close button
            if(event.type == SDL_QUIT) {
                gameIsRunning = false;
            }

            // adding SDL_MouseMotionEvent
            if(event.type == SDL_MOUSEMOTION)
            {
                rectangle2.x = event.motion.x;
                rectangle2.y = event.motion.y;
            }

            if(event.type == SDL_KEYDOWN) {
                // event.key.keysm.sym
                // keysym is a key symbol union which has a sym value
                // SDLK_0 is teh 0 key on the keyboard
                if(event.key.keysym.sym == SDLK_DOWN) {
                    // creating a blendmode
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);
                }
            }

            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    // creating a blendmode
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);
                }
            }
        }
        // (2) handle updates
        
        // set renderer bg color first
        // else it will be changed to line draw color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);            // black color
        // (3) clear and draw the screen
        SDL_RenderClear(renderer);

        // Set the render draw color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);      // white color
        // do our drawing here
        SDL_RenderDrawLine(renderer, 5, 5, 200, 220);

        // Draw texture using SDL_RenderCopy
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);

        // Draw another texture using SDL_RenderCopy
        SDL_RenderCopy(renderer, texture, NULL, &rectangle2);


        // finally render what have been drawn
        SDL_RenderPresent(renderer);
    }

    // destroying texture after being used
    SDL_DestroyTexture(texture);

    // destroying created window
    SDL_DestroyWindow(window);

    // SDL exit/quit function
    SDL_Quit();

    return 0;
}