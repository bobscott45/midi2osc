//
// Created by robert on 26/06/24.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <libconfig.h++>

#include "MessageMapper.h"
#include "MidiMessage.h"

class MessageMapper;

class Config {
public:
    Config(std::string const &filename);
    void populateMapper(MessageMapper &mapper);

private:
    libconfig::Config config;
    void populateMidiMap(MessageMapper &mapper) const;
    void populateOscMap(MessageMapper &mapper) const;
};



#endif //CONFIG_H
