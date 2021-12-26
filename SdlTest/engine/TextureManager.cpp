//
//  TextureManager.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#include "TextureManager.hpp"


SDL_Texture* TextureManager::getTexture(const char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

    SDL_FreeSurface(surface);
    return texture;

}
