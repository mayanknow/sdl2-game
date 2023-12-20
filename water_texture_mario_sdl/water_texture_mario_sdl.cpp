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
    window = SDL_CreateWindow("C++ SDL2 Window", 20, 20, 640, 480, SDL_WINDOW_SHOWN);

    // creating an SDL_Renderer pointer
    SDL_Renderer *renderer = nullptr;

    // initializing SDL_Renderer
    // here "-1" will make choose sdl rendering driver automatically
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // create a surface and load a BMP
    SDL_Surface *surface = SDL_LoadBMP("images/pool2.bmp");

    // adding color key before making the surface a texture
    // takes surface as a parameter
    // SDL_MapRGB function uses surface format pointer and returns selected pixel
    //  255, 0, 255 in RGBA is Magenta which is the color key
    // The retured pixels will be the transparent pixels
    // SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));


    // two textures names texture and texture2
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surface);

    // Free surface after the operation
    SDL_FreeSurface(surface);

    // create four rectangles reactangle
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 640;
    rectangle.h = 480;

    SDL_Rect rectangle2;
    rectangle2.x = -639;
    rectangle2.y = 0;
    rectangle2.w = 640;
    rectangle2.h = 480;

    SDL_Rect rectangle3;
    rectangle3.x = 0;
    rectangle3.y = 0;
    rectangle3.w = 640;
    rectangle3.h = 480;

    SDL_Rect rectangle4;
    rectangle4.x = 0;
    rectangle4.y = -480;
    rectangle4.w = 640;
    rectangle4.h = 480;


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

        int w, h;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        // delay which is a little hack mike did
        SDL_Delay(20);



        // handling reactangle events
        rectangle.x++;
        if(rectangle.x > 639) {
            rectangle.x = -639;
        }

        rectangle2.x++;
        if(rectangle2.x > 639) {
            rectangle2.x = -639;
        }

        rectangle3.y++;
        if(rectangle3.y > 479) {
            rectangle3.y = -480;
        }

        rectangle4.y++;
        if(rectangle4.y > 479) {
            rectangle4.y = -480;
        }

        // Order matters
        // Scrolling left and right
        SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_NONE);
        SDL_RenderCopy(renderer,texture,NULL,&rectangle);
        SDL_RenderCopy(renderer,texture,NULL,&rectangle2);
        // Scrolling up and down
        SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_MOD);
        SDL_RenderCopy(renderer,texture2,NULL,&rectangle3);
        SDL_RenderCopy(renderer,texture2,NULL,&rectangle4);


        // finally render what have been drawn
        SDL_RenderPresent(renderer);
    }

    // destroying texture after being used
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);

    // destroying created window
    SDL_DestroyWindow(window);

    // SDL exit/quit function
    SDL_Quit();

    return 0;
}