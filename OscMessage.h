//
// Created by robert on 25/06/24.
//

#ifndef OSCMESSAGE_H
#define OSCMESSAGE_H

#include <string>

enum class OscDataType
{
    Nomalized, Toggle, Invalid
};

union Value
{
    Value(unsigned char const v):charValue(v){}
    Value(float const v):floatValue(v){}
    Value(int const v):intValue(v){}
    unsigned char charValue;
    unsigned int intValue;
    float floatValue;
};


class OscMessage {
public:
    std::string address;
    OscDataType type;
    Value value;
    OscMessage(): address(""), type(OscDataType{}), value(0){}
    OscMessage(const std::string address, const OscDataType type): address(address), type(type), value(0) {}
    OscMessage(const std::string address, const OscDataType type, int value): address(address), type(type), value(0) {}
    OscMessage(const std::string address, const OscDataType type, float value): address(address), type(type), value(value) {}
};



#endif //OSCMESSAGE_H
