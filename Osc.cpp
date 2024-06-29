//
// Created by robert on 22/06/24.
//

#include <iostream>

#include "Osc.h"
#include "OscMessage.h"
#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"
#include "osc/OscOutboundPacketStream.h"

Osc::Osc(const char *address, const int port) : transmitSocket(UdpTransmitSocket(IpEndpointName(address, port))), buffer{}, packetStream(osc::OutboundPacketStream(buffer, OutputBufferSize)) {}

void Osc::sendMessage(OscMessage const &message) {
    // std::cout << message.address << " " << message.value.floatValue << std::endl;
    packetStream <<
        osc::BeginBundleImmediate
        << osc::BeginMessage(message.address.c_str());
    switch(message.type)
    {
    case OscDataType::Nomalized:
        packetStream << message.value.floatValue;
        break;
    case OscDataType::Toggle:
        if(message.value.charValue == 0)
        {
            packetStream.Clear();
            return;
        }
        packetStream << 1;
        break;
    }
    packetStream << osc::EndMessage
        << osc::EndBundle;
    transmitSocket.Send(packetStream.Data(), packetStream.Size());
    packetStream.Clear();
}