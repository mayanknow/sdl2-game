#include<string>
#include<SDL.h>

// this hpp file must be includdedin the cpp impelemetataion file
// andg the main file


class TextureRectangle {
    public:
    // constructor
    TextureRectangle(SDL_Renderer* renderer, std::string filepath);
    ~TextureRectangle();
    void SetRectangleProperties(int x, int y, int w, int h);    
    void Update();

    void Render(SDL_Renderer* renderer);
    private:
    SDL_Rect m_rectangle;
    SDL_Texture *m_texture;
};