//
//  main.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 23/12/2021.
///Library/Frameworks/SDL2.framework/Versions/A/Headers/

#include "MyGame.hpp"
#include <iostream>



MyGame *game = nullptr;

//setting up basis sdl window
//https://www.youtube.com/watch?v=lHAUc6F_B3Y
//https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/mac/index.php
//sdl must be dwonloaded and placed under Library/frameWorks/ and connected to this project under "Build Phases"->"Link binaries with libraries.
//important!!! for this work- under signing&capabilities, "hardened runtime" mut be true, and underneath it,
//Disble Library Validation must be checked. otherwise apple will not let sdl work
int main() {

    
    const int fps = 24;
    const int frameDelay = 1000 / fps;
    Uint32 frameStart;
    int frameTime = 0;
    
    game = new MyGame();
    game->init("yonny", 0, 0, 1136, 640, false);
    while(game->running())
    {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update(frameTime);
        game->render(frameTime);
        
        frameTime = SDL_GetTicks() - frameStart;
        
        //this maintains 60 fps
        if(frameTime < frameDelay)
        {
           SDL_Delay(frameDelay - frameTime);
        }
        
    }
    
    game->clean();

    
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

