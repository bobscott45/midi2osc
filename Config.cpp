//
// Created by robert on 26/06/24.
//

#include "Config.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <libconfig.h++>

#include "MessageMapper.h"

Config::Config(std::string const &filename)
{
    try
    {
        config.readFile(filename);
    } catch ( const libconfig::FileIOException &ex)
    {
        std::cerr << "Error reading " << filename  <<  std::endl;
        throw ex;
    }
    catch ( libconfig::ParseException &ex)
    {
        std::cerr << "Error parsing " << filename << " at line " << ex.getLine() << ":" << ex.getError() << std::endl;
        throw ex;
    }
}

void Config::populateMapper(MessageMapper &mapper)
{
    populateMidiMap(mapper);
    populateOscMap(mapper);

}

void Config::populateMidiMap(MessageMapper &mapper) const
{
    libconfig::Setting &midi   = config.lookup("mapper.midi");

    int  channel, controllerFrom, controllerTo, trackFrom;
    std::string action;
    int const length = midi.getLength();
    for(unsigned int index = 0; index < length ; index++)
    {
        midi[index].lookupValue("channel", channel);
        midi[index].lookupValue("controllerFrom", controllerFrom);
        midi[index].lookupValue("controllerTo", controllerTo);
        midi[index].lookupValue("trackFrom", trackFrom);
        midi[index].lookupValue("action", action);
        mapper.addMidiMapItems(channel, controllerFrom, controllerTo, trackFrom, action);
    }
}

void Config::populateOscMap(MessageMapper &mapper) const
{
    libconfig::Setting &oscConfig = config.lookup("mapper.osc");
    int const length = oscConfig.getLength();
    std::string action, address, type;
    for(unsigned int index = 0; index < length; index++)
    {
        oscConfig[index].lookupValue("action", action);
        oscConfig[index].lookupValue("address", address);
        oscConfig[index].lookupValue("type", type);
        mapper.addOscMapItem(action, address, type);
    }
}




