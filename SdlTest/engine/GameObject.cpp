//
//  GameObject.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//
#include "GameObject.hpp"

GameObject::GameObject(AtlasObj *o, int _x, int _y, int _w, int _h)
{
    atlas = o;
    x = _x;
    y = _y;

    //Json::Value data = o->data["frames"]["IDLE_E0000"]["frame"];
    
    
    
}

void GameObject::setAnimFrame(std::string _name) {
    
    std::string id = std::to_string(identifier);
    
    if (_name.compare(prevState) != 0)
    {
       // std::cout << id << " " << _name << " is not equal to " << prevState << std::endl;
        frameCounter = 0;
    } else {
       // std::cout << id << " " << _name << " is equal to " << prevState << std::endl;
        frameCounter++;
    }
    std::string key =_name + Utilities::getZeros(frameCounter);
    if(atlas->frames.find(  key ) != atlas->frames.end()){
        
        //std::cout << id << " found " << key << std::endl;
        
        Frame &frame = atlas->frames[key];
        srcRect.x = frame.x;
        srcRect.y = frame.y;
        srcRect.w = frame.w;
        srcRect.h = frame.h;
    }
    else
    {
        frameCounter = 0;
        key =_name + Utilities::getZeros(frameCounter);
        
        //std::cout << id << " found " << key << std::endl;
        
        Frame &frame = atlas->frames[key];
        srcRect.x = frame.x;
        srcRect.y = frame.y;
        srcRect.w = frame.w;
        srcRect.h = frame.h;
    }


    prevState = _name;

}

void GameObject::update()
{
    destRect.x = x ;
    destRect.y = y ;
    destRect.w = 50.0f;
    destRect.h = 100.0f;
}
void GameObject::render(int dt)
{
    SDL_RenderCopy(Game::renderer, atlas->texture, &srcRect, &destRect);
}
void GameObject::destroy()
{
    
}

GameObject::~GameObject()
{
    
}
