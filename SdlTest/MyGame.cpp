//
//  MyGame.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#include "MyGame.hpp"
#include "JsonHandler.hpp"


MyGame::MyGame()
{
    
}

//load in json and save it as out own data structure, much faster
void MyGame::parseJsonToMap(Json::Value &data, std::map<std::string,Frame> &frames)
{
    Json::Value f = (data)["frames"];
    for( Json::Value::const_iterator itr = f.begin() ; itr != f.end() ; itr++ )
    {
        std::string key = itr.key().asString();
        Frame frame;
        Json::Value frameObj = f[key];
        Json::Value list = frameObj["frame"];
        frame.x = list["x"].asInt();
        frame.y = list["y"].asInt();
        frame.w = list["w"].asInt();
        frame.h = list["h"].asInt();
        
        
        frame.destW = frame.w;
        frame.destH = frame.h;
        
        frames.emplace(key, frame);
               
    }

    
    
}



void MyGame::onloaded()
{
    mapW = 5000;
    mapH = 5000;
    numParticles = 8000;
    heroInfluence = 200.0f;
    runSpeed = 4.0f;
    manRad = 15.0f;

    blockSize = stageWidth / 10;
    numRows = mapH / blockSize;
    numCols = mapW / blockSize;
    
    //save json and texture in map for later retrival
    if(m.find( "man" ) == m.end())
    {
        AtlasObj *o = new AtlasObj();
        const char* jsonPath = "/Users/yonnizohar/Desktop/c++ projects/SdlTest/SdlTest/assets/man/data.json";
        JsonHandler::loadJson(jsonPath, &o->data);
        
        parseJsonToMap(o->data,o->frames);
        
        const char* imgPath = "/Users/yonnizohar/Desktop/c++ projects/SdlTest/SdlTest/assets/man/asset.png";
        
        o->texture = TextureManager::getTexture(imgPath);
        m.emplace("man", o);
        begin();
    }
    
    //std::cout << "this is my json " <<  << std::endl;
}
/**/
//the sorting funciton for later
struct
{
    inline bool operator() (const Man* struct1, const Man* struct2)
    {
        return (struct1->y < struct2->y);
    }
} sortFnctn;


//create gameobjects, store them in row/col map->vectors
void MyGame::begin() {
    /* */
    int i = 0;
    for ( i = 0; i < numParticles; i++) {
        
        bool found = false;
        int rndX = rand() % mapW;
        int rndY = rand() % mapH;
        
        
        while (found == false) {
            int row = rndX / blockSize;
            int col = rndY / blockSize;
            std::string key = std::to_string(row) + "_" + std::to_string(col);
            //if key does not exist
            if(gridMap.find(  key ) != gridMap.end()){
                
                std::vector<Man*> &arr = gridMap[key];
                
                for (int j = 0; j < arr.size(); j++) {
                    Man *o = arr[j];
                    int minDist = manRad * 2;
                    if (Utilities::getDistance(rndX, rndY, o->x, o->y) < minDist)
                    {
                        rndX = rndX = rand() % mapW;
                        rndY = rndY = rand() % mapH;
                        found = false;
                        j = 0;
                    }
                }
                found = true;
                
                
            }
            else
            {
                found = true;
            }

        }
        
        
        Man *circle = new Man(m["man"], rndX,rndY, 50, 50);
        
        circle->x = rndX;
        circle->y = rndY;
        circle->size = manRad;
        circle->moved = false;
        circle->identifier = rand() % 1000000;
        
        circle->row = rndY / blockSize;
        circle->col = rndX / blockSize;
        std::string key = std::to_string(circle->row) + "_" + std::to_string(circle->col);
        if(gridMap.find(  key ) == gridMap.end()){
            std::vector<Man*> v;
            gridMap.emplace(key, std::move(v) );
        }
        
        //std::cout << "other guy at " << rndX << " " << rndY << std::endl;

        gridMap[key].push_back(circle);
    }

    //std::sort(arr.begin(), arr.end(), sortFnctn);
    
    //create hero, apart from others
    hero = new Man(m["man"], mapW / 2,mapH / 2, 50, 50);
    std::cout << "hero at " << mapW / 2 << " " << mapH / 2 << std::endl;
    hero->x = mapW / 2;
    hero->y = mapH / 2;
    hero->size = heroInfluence;
    hero->identifier = rand() % 1000000;
    

    ready = true;
}

void MyGame::moveHero() {

    std::string state = "IDLE_";
    dir = "";
    hero->walking = false;
    
    if (Keybaord::W) {
        hero->y -= runSpeed;
        hero->walking = true;
        state = "WALK_";
        dir += "N";
    }
    
    if (Keybaord::S) {
        hero->y += runSpeed;
        hero->walking = true;
        state = "WALK_";
        dir += "S";
    }
    
    if (Keybaord::A) {
        hero->x -= runSpeed;
        hero->walking = true;
        state = "WALK_";
        dir += "W";
    }
    
    if (Keybaord::D) {
        hero->x += runSpeed;
        hero->walking = true;
        state = "WALK_";
        dir += "E";
    }
    
    if (dir == "") {
        dir = "S";
    }
    

    hero->row = hero->y / blockSize;
    hero->col = hero->x / blockSize;
    

    hero->setAnimFrame(state + dir );

}




void MyGame::update(int dt)
{
    /**/
    if(!ready)
    {
        return;
    }
    
   

    int i = 0;
    
    //the delta array is populated when a game object is moved. we check here if he was moved to a different tile
    for (i = 0; i < deltaArr.size(); i++) {
        Man *o = deltaArr[i];
        
        int prevRow =o->row;
        int prevCol = o->col;
        
        
        int row = o->y / blockSize;
        int col = o->x / blockSize;
        o->movers.clear();
        o->inRange = false;
        o->moved = false;
        
        
        if(prevRow != row || prevCol != col)
        {
            //remove guy from prev map
            std::string key = std::to_string(prevRow) + "_" + std::to_string(prevCol);
            if(gridMap.find(  key ) != gridMap.end()){
                std::vector<Man*> &a = gridMap[key];
                auto it = std::find(a.begin(), a.end(), o);
                 
                    // If element was found
                    if (it != a.end())
                    {
                     
                        // calculating the index
                        // of K
                        int index = it - a.begin();
                        
                       // Man* temp =gridMap[key][index];
                        a.erase(a.begin()+index);
                    }
            }
            
            
            o->row = row;
            o->col = col;
            
            //we might end up in a brand new tile
            key = std::to_string(row) + "_" + std::to_string(col);
            //if key does not exist
            if(gridMap.find(  key ) == gridMap.end()){
                std::vector<Man*> v;
                gridMap.emplace(key, std::move(v) );
            }
            
            std::vector<Man*>::iterator it;
            std::vector<Man*> &a = gridMap[key];
              it = std::find (a.begin(), a.end(), o);
              if (it == a.end())
              {
                  a.push_back(o);
              }

        }
        
        
    }
    deltaArr.clear();
    
    moveHero();
    moveParticles(hero, true);

}


void MyGame::draw(int dt)
{
    if(!ready)
    {
        return;
    }
    

    float heroPosX = -hero->x + (stageWidth / 2);
    float heroPosY = -hero->y + (stageHeight / 2);
    
    int i = 0;
    
    
    /**/
    int row;
    int col;
    int spread = stageWidth / blockSize / 2;
    for (row = hero->row - spread; row <= hero->row + spread+1; row++) {
        for (col = hero->col - spread; col <= hero->col + spread; col++) {
            std::string key = std::to_string(row) + "_" + std::to_string(col);
            
            if(gridMap.find(  key ) != gridMap.end()){
                std::vector<Man*> &a = gridMap[key];
                for (int j = 0; j < a.size(); j++) {
                    Man *o = a[j];
                    
                    std::string state = "IDLE_";
                    if (o->moved) {
                        if (hero->walking) {
                            state = "WALK_";
                        }
                    }
                    std::string dir = Utilities::getDirection(o->x, o->y, hero->x, hero->y);
                    
                    o->setAnimFrame(state + dir);
                    o->update(heroPosX, heroPosY);
                    o->render(dt);
                        
                }
            }
            
        }
    }
     
    hero->update(heroPosX, heroPosY);
    hero->render(dt);

}


//go over objects near the player. move them back if they are in radiuos.
//recursively have them do the same.
//place moved objects in deltaArray
void MyGame::moveParticles(Man *o, bool fromHero) {
    
    int row;
    int col;
    int start = -1;
    int end = 2;
    
    
    int spread = stageWidth / blockSize / 2;
    if (fromHero) {
        start = -spread;
        end = spread;
    }
    
    for (row = start; row < end; row++) {
        for (col = start; col < end; col++) {
            
            
            std::string key = std::to_string(o->row + row) + "_" + std::to_string(o->col + col);
            
            if(gridMap.find(  key ) != gridMap.end()){
                std::vector<Man*> &a = gridMap[key];
                std::sort(a.begin(), a.end(), sortFnctn);
                for (int j = 0; j < a.size(); j++) {
                    
                    Man* c = a[j];
                    
                    if (c->x == o->x && c->y == o->y) {
                        continue;
                    }
                    
                    std::vector<Man*>::iterator it;

                      it = std::find (o->movers.begin(), o->movers.end(), c);
                      if (it != o->movers.end())
                      {
                          continue;
                      }
                    
                    
                    
                    if(std::find(c->movers.begin(), c->movers.end(), o) != c->movers.end()) {
                        continue;
                    }
                    /**/

                    float dist = Utilities::getDistance(c->x, c->y, o->x, o->y);

                    float minDist = c->size + o->size;
                    
                    
                    float h = c->y - o->y;
                    float w = c->x - o->x;
                    float dirX = w / dist;
                    float dirY = h / dist;

                    if (dist < minDist) {
                        
                        c->inRange = true;
                        
                        //float per = 1 - (dist / minDist);
                        float vecX =ceil(dirX * minDist) ;
                        float vecY =ceil(dirY * minDist );
                        //c->x +=vecX;
                        //c->y +=vecY;
                        c->x = o->x +vecX;
                        c->y = o->y + vecY;
                        c->moved = true;
                        deltaArr.push_back(c);
                        
                        //std::cout << vecX << " " << vecY << " " << runSpeed << std::endl;

                        c->movers.push_back(o);
                        moveParticles(c, false);
                    }
                }
            }
        }
    }
     
    /* */
}
/**/
