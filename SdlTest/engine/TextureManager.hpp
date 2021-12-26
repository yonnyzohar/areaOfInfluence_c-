//
//  TextureManager.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Game.hpp"
#include <stdio.h>

class TextureManager{
public:
    static SDL_Texture* getTexture(const char* path);
    
};


#endif /* TextureManager_hpp */
