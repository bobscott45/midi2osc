//
// Created by robert on 22/06/24.
//

#ifndef OSC_H
#define OSC_H
#include "OscMessage.h"

#include "ip/UdpSocket.h"
#include "osc/OscOutboundPacketStream.h"

const int OutputBufferSize = 1024;


class Osc
{
public:

    Osc(const char *address, const int port);
    void sendMessage(OscMessage const &message);

private:
    UdpTransmitSocket  transmitSocket;
    char buffer[OutputBufferSize];
    osc::OutboundPacketStream packetStream;
};

#endif //OSC_H
