// creating a windows in SDL2

// standard c++ library
#include<iostream>

// importing SDL2 header
#include<SDL.h>

// importing sdl2_image
#include<SDL_image.h>

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

    // intializing flags to check if the images are ready to get imported
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);

    // initailize SDL2_image
    if((initStatus & flags) != flags) {
        std::cout  << "SDL2_image format not available" << std::endl;
    }

    // create an image surface
    SDL_Surface *image;
    image = IMG_Load("./images/image.png");

    // error check if image is not loaded
    if(!image) {
        std::cout << "Image not loaded..." << std::endl;
    }

    // create a texture
    SDL_Texture *ourPng = SDL_CreateTextureFromSurface(renderer, image);

    // create a reactangle
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 50;
    rectangle.w = 200;
    rectangle.h = 50;


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
        }
        // (2) handle updates
        
        // set renderer bg color first
        // else it will be changed to line draw color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);            // black color
        // (3) clear and draw the screen
        SDL_RenderClear(renderer);

        // Set the render draw color
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);      // white color
        // do our drawing here
        // SDL_RenderDrawLine(renderer, 5, 5, 200, 220);
        // SDL_RenderDrawRect(renderer, &rectangle);

        // Draw texture using SDL_RenderCopy
        // SDL_RenderCopy(renderer, textureText, NULL, &rectangle);

        SDL_RenderCopy(renderer, ourPng, NULL, NULL);

        // finally render what have been drawn
        SDL_RenderPresent(renderer);
    }

    // destroying texture after being used
    // SDL_DestroyTexture(textureText);

    // destroying created window
    SDL_DestroyWindow(window);

    // remember to close font subsystem 
    // TTF_CloseFont(outFont);

    // free our png image surface
    SDL_FreeSurface(image);

    // destroy our texture
    SDL_DestroyTexture(ourPng);


    // quitting SDL2_image
    IMG_Quit();

    // SDL exit/quit function
    SDL_Quit();

    return 0;
}