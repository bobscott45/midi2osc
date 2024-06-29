//
// Created by robert on 26/06/24.
//

#ifndef MESAGEMAPPER_H
#define MESAGEMAPPER_H
#include <map>

#include "OscMessage.h"

class MidiMessage;

enum class Action
{
    TrackVolume, TrackRecArm, TrackMute, TrackSolo, TrackPan, Invalid
};



class MessageMapper {
public:
    std::map<const std::tuple<int, int>, std::tuple<int, std::string>> midiMap;
    std::map<const Action, std::tuple<std::string, OscDataType>> oscMap;
    void addOscMapItem(std::string const &action, std::string const &address, std::string &type);
    void addMidiMapItems(int channel, int controllerFrom, int controllerTo, int trackFrom, std::string const &action);
    OscMessage & makeOscMessage(MidiMessage const &midiMessage, OscMessage &oscMessage);
private:
    static Action string2action(std::string str);
    static OscDataType string2oscdatatype(std::string str);
    static bool replace(std::string& str, const std::string& from, const std::string& to);
};



#endif //MESAGEMAPPER_H
