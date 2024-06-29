cmake_minimum_required(VERSION 3.28)
project(midi2osc)

set(CMAKE_CXX_STANDARD 17)

find_package(RtMidi)
find_package(libconfig++)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

IF(WIN32)
    set(IpSystemTypePath ip/win32)
    set(LIBS ${LIBS} Ws2_32 winmm)
ELSE(WIN32)
    set(IpSystemTypePath ip/posix)
ENDIF(WIN32)

ADD_LIBRARY(oscpack

        ip/IpEndpointName.h
        ip/IpEndpointName.cpp

        ip/NetworkingUtils.h
        ${IpSystemTypePath}/NetworkingUtils.cpp

        ip/UdpSocket.h
        ${IpSystemTypePath}/UdpSocket.cpp

        ip/PacketListener.h
        ip/TimerListener.h

        osc/OscTypes.h
        osc/OscTypes.cpp
        osc/OscHostEndianness.h
        osc/OscException.h
        osc/OscPacketListener.h
        osc/MessageMappingOscPacketListener.h
        osc/OscReceivedElements.h
        osc/OscReceivedElements.cpp
        osc/OscPrintReceivedElements.h
        osc/OscPrintReceivedElements.cpp
        osc/OscOutboundPacketStream.h
        osc/OscOutboundPacketStream.cpp

)

add_executable(midi2osc main.cpp
        MidiMessage.cpp
        Osc.cpp
        OscMessage.cpp
        MessageMapper.cpp
        MessageMapper.h
        Config.cpp
        Config.h
)

target_include_directories(midi2osc PRIVATE /usr/include/rtmidi PRIVATE /usr/include/ )
target_link_libraries(midi2osc rtmidi oscpack config++ ${LIBS})