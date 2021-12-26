//
//  JsonHandler.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#include "JsonHandler.hpp"

void JsonHandler::loadJson(const char* src, Json::Value *data)
{
    std::ifstream file(src);
    Json::Reader reader;
    bool success = reader.parse(file, *data);
    

}

