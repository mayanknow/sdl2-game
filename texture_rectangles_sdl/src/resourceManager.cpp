#include "../include/resourceManager.hpp"
#include<SDL.h>
// #include<iostream>

ResourceManager::ResourceManager()
{

}

ResourceManager::ResourceManager(ResourceManager const&)
{

}

ResourceManager ResourceManager::operator=(ResourceManager const& rhs)
{
    // Mike wrote: TODO
    // Although we do not need this for a singleton
    return *this;
}

// is instiantiate, exactly 1 instace of our class
// this the implementation of singleton in c++
ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager* s_instance = new ResourceManager;
    // here the pointer is retured and got dereferenced
    // as the return type is reference to a class
    return *s_instance;
}

SDL_Surface * ResourceManager::GetSurface(std::string filepath)
{
    // we will look through, or m_surfaces
    // which is a unordered_map and see if
    // a file like this already exists
    // **And if the file does exist, then retrun the
    // associated surface

    // this is the iterator
    auto search = m_surfaces.find(filepath);
    // if the search didn't reach at the end
    // the file has been found then
    if(search != m_surfaces.end()) {
        // std::cout << "image found" << std::endl;
        return m_surfaces[filepath];
    } else {
        // this means the image hasn't been used before
        // so, create a new surface and load that image
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        // std::cout << "image first" << std::endl;
        
        // adding this surface to the m_surfaces list
        m_surfaces.insert(std::make_pair(filepath, surface));
        return m_surfaces[filepath];
    }

    return nullptr;
}