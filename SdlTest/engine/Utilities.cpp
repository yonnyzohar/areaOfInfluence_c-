//
//  Utilities.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 25/12/2021.
//

#include "Utilities.hpp"
#define PI 3.14159265359


float Utilities::correctAngle(float _angleDeg) {
    while (_angleDeg < 0) {
        _angleDeg += 360;
    }
    
    while (_angleDeg > 360) {
        _angleDeg -= 360;
    }
    
    return _angleDeg;
}

float Utilities::radToDegrees(float rads) {
    return rads * 180 / PI;
}

float Utilities::degreesToRad(float degs) {
    return degs * PI / 180;
}


float Utilities::getAngle(float fromX, float fromY, float toX, float toY) {
    float angle = atan2(toY - fromY, toX - fromX);
    return angle;
}

float Utilities::getDistance(float p1X, float p1Y, float p2X, float p2Y) {
    
    float dX = p1X - p2X;
    float dY = p1Y - p2Y;
    float dist = sqrt(dX * dX + dY * dY);
    return dist;
}


std::string Utilities::getDirection(float p1X, float p1Y, float p2X, float p2Y)
{
    
    
    std::string firstDir = "";
    std::string secondDir = "";
    
    //////////////////////
    int degrees = atan2(p1Y - p2Y, p1X - p2X) / PI * 180;
    
    while (degrees >= 360) {
        degrees -= 360;
    }
    while (degrees < 0) {
        degrees += 360;
    }
    
    
    degrees = ceil(degrees);
    
    if (degrees >= 66 && degrees < 112) {
        firstDir = "N";
    }
    if (degrees >= 22 && degrees < 66) {
        firstDir = "N";
        secondDir = "W";
    }
    
    if (degrees >= 0 && degrees < 22) {
        secondDir = "W";
    }
    
    if (degrees >= 337 && degrees <= 359) {
        secondDir = "W";
    }
    if (degrees >= 292 && degrees < 337) {
        firstDir = "S";
        secondDir = "W";
    }
    if (degrees >= 247 && degrees < 292) {
        firstDir = "S";
    }
    if (degrees >= 202 && degrees < 247) {
        firstDir = "S";
        secondDir = "E";
    }
    if (degrees >= 157 && degrees < 202) {
        secondDir = "E";
    }
    
    if (degrees >= 112 && degrees < 157) {
        firstDir = "N";
        secondDir = "E";
    }
    
    
    return firstDir + "" + secondDir;
}


std::string Utilities::getZeros(int num)
{
    std::string num_str =std::to_string(num);
    int len = num_str.length();
    std::string str = "";
    for (int i = 0; i < 4 - len; i++) {
        str += "0";
    }

    str += num_str;
    return str;
}
