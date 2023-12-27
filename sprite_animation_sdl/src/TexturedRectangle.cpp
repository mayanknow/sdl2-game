#include<iostream>
#include<string>
// importing SDL2 header
#include<SDL.h>
#include "../include/TexturedRectangle.hpp"
#include "../include/ResourceManager.hpp"

// constructor
TextureRectangle::TextureRectangle(SDL_Renderer* renderer, std::string filepath) {
    
    SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface("../assets/images/image.bmp");
    // create a texture from surface
    m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);


}

TextureRectangle::~TextureRectangle() {
    // destroying texture after being used
    SDL_DestroyTexture(m_texture);
}

void TextureRectangle::SetRectangleProperties(int x, int y, int w, int h) {
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
}
    
void TextureRectangle::Update() {

}

void TextureRectangle::Render(SDL_Renderer* renderer)
{
    // Draw texture using SDL_RenderCopy
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}