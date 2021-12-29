//
//  Man.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#include "Man.hpp"

void Man::update(int offsetX, int offsetY)
{
    destRect.x = (int)(x + offsetX);
    destRect.y = (int)(y + offsetY);
    destRect.w = (int)destW;
    destRect.h = (int)destH;
}
