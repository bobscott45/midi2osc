#include <iostream>
#include <unistd.h>

#include "RtMidi.h"
#include <libconfig.h++>

#include "Config.h"
#include "MidiMessage.h"
#include "Osc.h"
#include "osc/OscOutboundPacketStream.h"


#include "MessageMapper.h"

const int SLEEP = 25;
const char * ADDRESS = "192.168.1.135";
const int PORT = 8000;

void openMidiPorts();
void closeMidiPorts();
void listMidiSources(RtMidi *midi);
MidiMessage & getMidiMessage(MidiMessage &message);
void handleMidiError(RtMidiError &error);

RtMidiIn  *midiIn = nullptr;
RtMidiOut *midiOut = nullptr;

int main()
{
    try {
        openMidiPorts();
    } catch (RtMidiError &error) {
        handleMidiError(error);
        closeMidiPorts();
        exit( EXIT_FAILURE);
    }

    std::cout << "Input" << std::endl;
    std::cout << "-----" << std::endl;
    listMidiSources(midiIn);
    std::cout << std::endl;
    std::cout << "Output" << std::endl;
    std::cout << "------"  << std::endl;
    listMidiSources(midiOut);
    midiIn->openPort(3, "ReMOTE SL:ReMOTE SL MIDI 3 24:2");
    Osc osc(ADDRESS, PORT);
    std::vector<unsigned char> message;
    MessageMapper mapper;
    Config config("midi2osc.config");

    config.populateMapper(mapper);


    while(true)
    {
        MidiMessage midiMessage{};
        getMidiMessage(midiMessage);
        if( midiMessage.isEmpty())
        {
            usleep(SLEEP);
            continue;
        }
        midiMessage.print();
        if(midiMessage.isControlChange())
        {
            // midiMessage.print();
            OscMessage oscMessage{};
            mapper.makeOscMessage(midiMessage, oscMessage);
            if(oscMessage.type == OscDataType::Invalid) continue;
            osc.sendMessage(oscMessage);
        }
        usleep(SLEEP);
    }
    closeMidiPorts();
    return EXIT_SUCCESS;
}

void openMidiPorts()
{
    midiIn = new RtMidiIn();
    midiOut = new RtMidiOut();
}

void closeMidiPorts()
{
    delete midiIn;
    delete midiOut;
}

void listMidiSources(RtMidi *midi)
{
    unsigned int port_count = midi->getPortCount();
    std::cout << std::endl << "There are " << port_count << " MIDI sources available." << std::endl;

    for(unsigned int i = 0; i < port_count; i++)
    {
        try
        {
            std::cout << i << ": " << midiIn->getPortName(i) << std::endl;
        }
        catch ( RtMidiError &error)
        {
           handleMidiError(error);
        }
    }
}

MidiMessage & getMidiMessage(MidiMessage &message)
{
    std::vector<unsigned char> rawMessage;
    midiIn->ignoreTypes(false, false, false );
    midiIn->getMessage( &rawMessage );
    message.setMessage(rawMessage);
    return message;
}

void handleMidiError(RtMidiError &error)
{
    error.printMessage();
}


