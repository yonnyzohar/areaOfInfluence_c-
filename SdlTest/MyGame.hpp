//
//  MyGame.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef MyGame_hpp
#define MyGame_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "Game.hpp"
#include "Man.hpp"
#include "Utilities.hpp"
#include "Keybaord.hpp"



class MyGame : public Game
{
public:
    //using Game::Game;
    MyGame();
    ~MyGame();
    void update(int dt) override;
    void draw(int dt) override;
    void onloaded() override;
    void moveHero();
    void parseJsonToMap(Json::Value &data, std::map<std::string,Frame> &frames);
    
    
    int mapW = 1000;
    int mapH = 1000;
    int numParticles = 300;
    float heroInfluence = 100.0f;
    int blockSize;  
    float runSpeed = 6.0f;
    float manRad = 15.0f;
    std::string dir = "S";
    std::string prevState;
    int numRows;
    int numCols;
    std::map<std::string, std::vector<Man*>> gridMap;
    std::vector<Man*> deltaArr;
    Man* hero;
    bool ready = false;
    void moveParticles(Man* o, bool fromHero);
      
private:
    void begin();
    
};

#endif /* MyGame_hpp */
