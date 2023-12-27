#include<string>

#include<SDL.h>

#include "../include/AnimatedSprite.hpp"
#include "../include/ResourceManager.hpp"

// constructor
AnimatedSprite::AnimatedSprite(SDL_Renderer * renderer, std::string filepath)
{
    SDL_Surface *retrievedSurface = ResourceManager::GetInstance().GetSurface(filepath);
    m_texture = SDL_CreateTextureFromSurface(renderer, retrievedSurface);
}

// destructor
AnimatedSprite::~AnimatedSprite()
{
    SDL_DestroyTexture(m_texture);
}

void AnimatedSprite::Draw(int x, int y, int w, int h)
{
    // create a rectangle
    m_dst.x = x;
    m_dst.y = y;
    m_dst.w = w;
    m_dst.h = h;
}

void AnimatedSprite::PlayFrame(int x, int y, int w, int h, int frame)
{
    // basically x+(w*frame)
    m_src.x = x+w*frame;
    m_src.y = y;
    m_src.w = w;
    m_src.h = h;
}

void AnimatedSprite::Update()
{

}

void AnimatedSprite::Render(SDL_Renderer *renderer)
{
    // &m_src and &m_dst is used because address has to be passed
    // these are value variables
    SDL_RenderCopy(renderer, m_texture, &m_src, &m_dst);
}