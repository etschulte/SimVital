#pragma once

#include <vector>

class RingBuffer {
private:
    std::vector<int> buffer; // fixed size array that holds 12 bit heart arrythmia data
    int capacity; // how much data the buffer holds
    int writePointer; // tracks where the next incoming bit of data will be saved
    int readPointer; // tracks where the next outgoing bit of data will be read from
    int currentCounter; // tracks how many unread samples are currently in the buffer

public:
    RingBuffer(int size);
    ~RingBuffer();

    // writes sample data to buffer
    bool write(int sample);

    // reads data from buffer
    bool read(int &sample);

    // checks if buffer is empty
    bool isEmpty() const;

    // checks if buffer is full
    bool isFull() const;

    // gets capacity value
    int getCapacity();
};