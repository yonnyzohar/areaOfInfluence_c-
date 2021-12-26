//
//  Man.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#include "Man.hpp"

void Man::update(int offsetX, int offsetY)
{
    destRect.x = x + offsetX;
    destRect.y = y + offsetY;
    destRect.w = 50.0f;
    destRect.h = 100.0f;
}
