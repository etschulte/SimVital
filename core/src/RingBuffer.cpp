#include "RingBuffer.hpp"

RingBuffer::RingBuffer(int size){
    capacity = size;
    writePointer = 0;
    readPointer = 0;
    buffer.resize(capacity);
    currentCounter = 0;
}

// nothing to deconstruct
RingBuffer::~RingBuffer(){}

bool RingBuffer::write(int sample) {

    if (isFull()) {
        return false;
    }

    // writes sample data to current writePointer position and moves pointer to next
    buffer[writePointer] = sample;
    writePointer++;

    // resets writePointer position to 0 if it is at the end of the buffer
    if (writePointer >= capacity) {
        writePointer = 0;
    }

    currentCounter++;

    return true;
}

bool RingBuffer::read(int &sample) {

    if (isEmpty()) {
        return false;
    }

    // reads value at current readPointer position and moves pointer to next
    sample = buffer[readPointer];
    readPointer++;

    // resets readPointer position to 0 if it is at the end of the buffer
    if (readPointer >= capacity) {
        readPointer = 0;
    }

    currentCounter--;

    return true;
}

bool RingBuffer::isEmpty() const {

    return currentCounter == 0;
}

bool RingBuffer::isFull() const {

    return currentCounter == capacity;
}

int RingBuffer::getCapacity() {
    return capacity;
}