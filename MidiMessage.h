//
// Created by robert on 22/06/24.
//

#ifndef MIDIMESSAGE_H
#define MIDIMESSAGE_H

#include <iostream>
#include <vector>
#include <string>

enum class MidiMessageType { NoteOff=8, NoteOn, PolyphonicAftertouch, ControlChange, ProgramChange, ChannelAftertouch, PitchWheel};

class MidiMessage
{
public:
    MidiMessage():message(std::vector<unsigned char>{}) {}
    MidiMessage(std::vector<unsigned char> message): message(std::move(message)) {}
    void setMessage(std::vector<unsigned char> const & value);
    std::string getTypeName();
    void print();
    char status() const { return message[0]; }
    char channel() const { return (status() & 0xf) + 1; }
    char data1() const { return message[1]; }
    char data2() const { return message[2]; }
    bool isEmpty() const { return message.size() == 0; }
    bool isNoteOff() const { return (status() >> 4 & 0xf) == 0x8; }
    bool isNoteOn() const { return (status() >> 4 & 0xf) == 0x9; }
    bool isPolyphonicAftertouch() const { return (status() >> 4 & 0xf) == 0xA; }
    bool isControlChange() const {  return (status() >> 4 & 0xf) == 0xB; }
    bool isProgramChange() const { return (status() >> 4 & 0xf) == 0xC; }
    bool isChannelAftertouch() const { return (status() >> 4 & 0xf) == 0xD; }
    bool isPitchWheel() const { return (status() >> 4 & 0xf) == 0xE; }
    bool isSystemExclusiveStart() const { return status() == 0xF0; }
    bool isSystemExclusiveEnd() const { return status() == 0xF7; }
    bool isSongPointer() const { return status() == 0xF2; }
    bool isSongSelect() const { return status() == 0xF3; }
    bool isTuneRequest() const { return status() == 0xF6; }
    bool isQuarterFrame() const { return status() == 0xF1; }
    bool isTimingClock() const { return status() == 0xF8; }
    bool isMeasureEnd() const { return status() == 0xF9; }
    bool isStart() const { return status() == 0xFA; }
    bool isContinue() const { return status() == 0xFB; }
    bool isStop() const { return status() == 0xFC; }
    bool isActiveSensing() const { return status() == 0xFE; }
    bool isReset() const { return status() == 0xFF; }
    bool isSystemExclusive() const { return isSystemExclusiveStart() || isSystemExclusiveEnd(); }
    bool isSystemCommon() const { return isSongPointer() || isSongSelect() || isTuneRequest(); }
    bool isMidiTimeCode() const { return isQuarterFrame(); }
    bool isSystemRealtime() const { return isTimingClock() || isMeasureEnd() || isStart() ||
                            isContinue() || isStop() || isActiveSensing() || isReset(); }
private:
    std::vector<unsigned char> message;
};


#endif //MIDIMESSAGE_H
