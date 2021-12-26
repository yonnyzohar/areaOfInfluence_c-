//
//  Utilities.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 25/12/2021.
//

#ifndef Utilities_hpp
#define Utilities_hpp

#include <stdio.h>
#include <string>
#include <math.h> 

class Utilities{
public:
    static float correctAngle(float _angleDeg);
    static float radToDegrees(float rads);
    static float degreesToRad(float degs);
    static float getAngle(float fromX, float fromY, float toX, float toY);
    static float getDistance(float p1X, float p1Y, float p2X, float p2Y);
    static std::string getDirection(float p1X, float p1Y, float p2X, float p2Y);
    static std::string getZeros(int num);
};







#endif /* Utilities_hpp */
