#include "../include/RingBuffer.hpp"

RingBuffer::RingBuffer(int size){
    capacity = size;
    writePointer = 0;
    readPointer = 0;
    buffer.resize(capacity);
    currentCounter = 0;
}

RingBuffer::~RingBuffer() {}

bool RingBuffer::write(int sample) {

    if (isFull()) {
        return false;
    }

    buffer[writePointer] = sample;
    writePointer++;

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

    sample = buffer[readPointer];
    readPointer++;

    if (readPointer >= capacity) {
        readPointer = 0;
    }

    currentCounter--;

    return true;
}

bool RingBuffer::reset() {
    writePointer = 0;
    readPointer = 0;
    currentCounter = 0;

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