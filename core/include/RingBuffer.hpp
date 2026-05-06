#pragma once

#include <vector>

class RingBuffer {
private:
    std::vector<int> buffer; 
    int capacity; 
    int writePointer; 
    int readPointer; 
    int currentCounter; 

public:
    RingBuffer(int size);
    ~RingBuffer();

    // writes sample data to buffer
    bool write(int sample);

    // reads data from buffer
    bool read(int &sample);

    bool reset();

    // checks if buffer is empty
    bool isEmpty() const;

    // checks if buffer is full
    bool isFull() const;

    // gets capacity value
    int getCapacity();
};