#include "EcgController.hpp"

EcgController::EcgController(MitBihParser* parser, RingBuffer* buffer, QObject* parent) 
    : QObject(parent), 
    parserPtr(parser), 
    bufferPtr(buffer),
    timerPtr(nullptr), 
    recentEcgVal(0) 
    {

    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &EcgController::onTick); // registering timer callback 

}

// nothing to deconstruct
EcgController::~EcgController() {}

// gets ECG value
int EcgController::getEcgVal() const {
    return recentEcgVal;
}

// starts the timer
void EcgController::start() {
    if (!timerPtr->isActive()) {
        timerPtr->start(100);
    }
}

// stops the timer
void EcgController::stop() {
    if (timerPtr->isActive()) {
        timerPtr->stop();
    }
}

// emits when ECG value changes
void EcgController::onTick() {
    int nextVal = 0;

    // check if we can read from the buffer
    if (bufferPtr->read(nextVal)) {
        recentEcgVal = nextVal;
        emit ecgValChanged(recentEcgVal); // tells QML to update 
    }
}