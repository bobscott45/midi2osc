//
// Created by robert on 26/06/24.
//



#include "MessageMapper.h"

#include <iostream>
#include <algorithm>
#include "MidiMessage.h"
#include "OscMessage.h"

OscMessage & MessageMapper::makeOscMessage(MidiMessage const &midiMessage, OscMessage &oscMessage)
{
    // map<int,Bar>::iterator it = m.find('2');
    // Bar b3;
    // if(it != m.end())
    // {
    //     //element found;
    //     b3 = it->second;
    // }
    auto it =  midiMap.find(std::make_tuple(midiMessage.channel(), midiMessage.data1()));
    if(it == midiMap.end()) return  oscMessage;
    auto spec = it->second;
    // std::tuple<int, std::string> spec = midiMap[std::make_tuple(midiMessage.channel(), midiMessage.data1())];
    const int track = std::get<0>(spec);
    const Action action = string2action(std::get<1>(spec));
    auto oscTemplate = oscMap[action];
    std::string addressTemplate = std::get<0>(oscTemplate);
    const std::string templateString = "{track}";
    replace(addressTemplate, templateString, std::to_string(track));
    oscMessage.address = addressTemplate;
    oscMessage.type = std::get<1>(oscTemplate);
    switch (oscMessage.type)
    {
        case OscDataType::Nomalized:
            {
                const float value = midiMessage.data2() / 127.0;
                oscMessage.value = Value(value);
                break;
            }
        case OscDataType::Toggle:
            {
                const unsigned char value = midiMessage.data2();
                oscMessage.value = Value(value);
                break;
            }
    case OscDataType::Binary:
            {
                const unsigned char value = midiMessage.data2();
                oscMessage.value = Value(value);
                break;
            }
        default:
            throw "Invalid OSC message type";
    }
    return oscMessage;
}

void MessageMapper::addMidiMapItem(int channel, int controller, int track, std::string const &action)
{
    midiMap[std::make_tuple(channel, controller)] = std::make_tuple(track, action);
}

void MessageMapper::addMidiMapItems(int channel, int controllerFrom, int controllerTo, int trackFrom, std::string const &action)
{
    for(unsigned int controller = controllerFrom, track = trackFrom; controller <= controllerTo; controller++, track++)
    {
        addMidiMapItem(channel, controller, track, action);
        // midiMap[std::make_tuple(channel, controller)] = std::make_tuple(track, action);
        // std::cout << channel << "," << controller << "," << track << "," << action << std::endl;
    }
}

void MessageMapper::addOscMapItem(std::string const &action, std::string const &address, std::string &type)
{
    oscMap[string2action(action)] = std::make_tuple(address, string2oscdatatype(type));
    // std::cout << action << "," << address << "," << type << std::endl;
}

Action MessageMapper::string2action(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    if(str == "trackvolume") return Action::TrackVolume;
    if(str == "trackmute") return Action::TrackMute;
    if(str == "trackpan") return Action::TrackPan;
    if(str == "tracksolo") return Action::TrackSolo;
    if(str == "trackrecarm") return Action::TrackRecArm;
    if(str == "rewind") return Action::Rewind;
    if(str == "forward") return Action::Forward;
    if(str == "record") return Action::Record;
    if(str == "stop") return Action::Stop;
    if(str == "play") return Action::Play;
    if(str == "pause") return Action::Pause;
    return Action::Invalid;
}

OscDataType MessageMapper::string2oscdatatype(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    if(str == "normalized") return OscDataType::Nomalized;
    if(str == "toggle") return OscDataType::Toggle;
    if(str == "binary") return OscDataType::Binary;
    return OscDataType::Invalid;
}

bool MessageMapper::replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}


