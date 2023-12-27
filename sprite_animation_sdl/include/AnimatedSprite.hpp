#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include<string>
#include<SDL.h>

class AnimatedSprite {
public:
    // constructor
    AnimatedSprite(SDL_Renderer *renderer, std::string filepath);
    // destructor
    ~AnimatedSprite();

    // Draw function
    void Draw(int x, int y, int w, int h);

    // Select and play a specific frame
    void PlayFrame(int x, int y, int w, int h, int frame);

    // update every frame
    void Update();

    // Render
    void Render(SDL_Renderer *renderer);

private:
    SDL_Rect m_src;     // source: where we are selectig from
    SDL_Rect m_dst;     // destination: where we are rendering
    SDL_Texture* m_texture;

};







#endif