#pragma once

#include "globals.hpp"
#include <boost/thread/mutex.hpp>

class CallbackAsyncSerial;
  
struct Packet
{
    // Packet Length including CBALL Header
    const static int LENGTH = 25;

    // Message Count
    uint8_t msg_count;  

    // Last message received
    uint8_t msg_received;

    uint8_t status;
    uint8_t di1;
    uint8_t di2;
    uint8_t mci;
    uint8_t di3;
    uint8_t di4;
    uint8_t ai1;
    uint8_t ai2;
    uint8_t ai3;
    uint8_t ai4;
    uint8_t ai5;
    uint8_t ai6;
    uint8_t ai7;
    uint8_t ai8;  
};

class Interface
{

public:
    Interface();
    ~Interface();
    void init();
    void close();
    void start();
    void stop();
    bool started();
    Packet get_packet();


private:
    // Mutex Declaration
    boost::mutex mtx;

    // Serial Port Handler
    CallbackAsyncSerial* serial;

    // Circular Array Buffer
    const static int BUFFER_SIZE = 1024;
    uint8_t buffer[BUFFER_SIZE];
    int32_t head;

    // Packet storage
    Packet packet;
    enum
    {
        PACKET_NOT_FOUND = -1,
        CHECKSUM_ERROR   = -2,
    };
    
    // Previous Message Index
    int16_t prev_msg;

    // Is Serial interface open and operational
    bool is_started;

    void received(const char *data, unsigned int len);
    int find_packet();
    bool is_checksum_ok(int offset);

    uint8_t c_get(int i);
    int c_add(int a, int b);
    int c_sub(int a, int b);
};