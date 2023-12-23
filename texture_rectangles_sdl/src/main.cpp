// creating a windows in SDL2

// standard c++ library
#include<iostream>
#include<string>
#include<memory>

// importing SDL2 header
#include<SDL.h>

#include "../include/texture_rectangle.hpp"


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

    std::vector<std::shared_ptr<TextureRectangle>> rects;
    for(int i = 0; i < 10; i++) {
        std::shared_ptr<TextureRectangle> rect = std::make_shared<TextureRectangle>(renderer, "../images/image.bmp");
        rects.push_back(rect);
    }

    int row = 0;
    int col = 1;
    for(int i = 0; i < 10; i++) {
        rects[i]->SetRectangleProperties(20*col, 30*row, 200, 200);
        if(i%3 == 0) {
            row++;
            col = 0;
        }
        col++;
    }


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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);            // black color
        // (3) clear and draw the screen
        SDL_RenderClear(renderer);

        // Set the render draw color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);      // white color
        
        // do our drawing here
        for(auto& rect: rects){
            rect->Render(renderer);
        }

        // finally render what have been drawn
        SDL_RenderPresent(renderer);
    }

    // destroying created window
    SDL_DestroyWindow(window);

    // SDL exit/quit function
    SDL_Quit();

    return 0;
}