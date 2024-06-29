//
// Created by robert on 22/06/24.
//

#include "MidiMessage.h"
#include <iostream>
#include <string>

void MidiMessage::setMessage(std::vector<unsigned char> const & value)
{
    message = std::vector<unsigned char>(value);
}

void MidiMessage::print()
{
    std::cout << getTypeName() << " "
        << std::to_string(channel()) << ":"
        << std::to_string(data1()) << ":"
        << std::to_string(data2())
        << std::endl;
}
std::string MidiMessage::getTypeName()
{
    std::string typeName;
    switch (status() >> 4 & 0xf)
    {
    case 0x8:
        return std::string("NoteOff");
    case 0x9:
        return std::string("NoteOn");
    case 0xA:
        return std::string("PolyphonicAftertouch");
    case 0xB:
        return std::string("ControlChange");
    case 0xC:
        return std::string("ProgramChange");
    case 0xD:
        return std::string("ChannelAftertouch");
    case 0xE:
        return std::string("PitchWheel");
    }

    if(isSystemExclusive()) return std::string("SystemExclusive");
    if(isSystemCommon()) return std::string("SystemCommon");
    if(isMidiTimeCode()) return std::string("MidiTimeCode");
    if(isSystemRealtime()) return std::string("SystemRealtime");
    return "Invalid";
}

