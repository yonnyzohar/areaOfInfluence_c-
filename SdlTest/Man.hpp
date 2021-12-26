//
//  Man.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef Man_hpp
#define Man_hpp

#include <stdio.h>

#include "GameObject.hpp"


class Man : public GameObject
{
    
public:
    using GameObject::GameObject;
    void update(int offsetX, int offsetY) ;
    
    int size;
    int row;
    int col;
    std::vector<Man*> movers;
    bool inRange;
    bool moved;
    bool walking;
    
    /*
    bool operator==( Man* rhs){
              if ((this->identifier==rhs->identifier))
                  return true;
              return false;
          }
    */
};

#endif /* Man_hpp */
