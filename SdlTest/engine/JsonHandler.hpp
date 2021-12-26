//
//  JsonHandler.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef JsonHandler_hpp
#define JsonHandler_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "json.h"
#include "reader.h"
#include "value.h"



class JsonHandler{
public:
    static void loadJson(const char* src, Json::Value *data);

};

#endif /* JsonHandler_hpp */
