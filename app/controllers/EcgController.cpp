#include "EcgController.hpp"
#include <QDebug>

EcgController::EcgController(MitBihParser* parser, RingBuffer* buffer, QObject* parent) 
    : QObject(parent), 
    parserPtr(parser), 
    bufferPtr(buffer),
    timerPtr(nullptr), 
    recentEcgVal(0),
    threshold(1100),
    wasAboveThreshold(false),
    samplesSinceLastBeat(0),
    refractoryCounter(0),
    m_currentBpm(0) ,
    seenFirstPeak(false)
    {

    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &EcgController::onTick); // registering timer callback 
    timerPtr->start(1000 / sampleRate);

}


// nothing to deconstruct
EcgController::~EcgController() {}

// gets ECG value
int EcgController::getEcgVal() const {
    return recentEcgVal;
}

// gets HR value
int EcgController::getHRVal() const {
    return m_currentBpm;
}

// emits when ECG value changes
void EcgController::onTick() {
    int nextVal = 0;

    // check if we can read from the buffer
    if (bufferPtr->read(nextVal)) {
        recentEcgVal = nextVal;
        emit ecgValChanged(recentEcgVal); // tells QML to update

        samplesSinceLastBeat++; // advances the clock

        // if the cooldown timer is active, decrement it 
        if (refractoryCounter > 0) {
            refractoryCounter--;
        }

        // if cooldown timer is awake, current ECG value is above threshold, and previous ECG was below, then emit bpm and reset clock and cooldown
        if (refractoryCounter == 0 && recentEcgVal > threshold && wasAboveThreshold == false) {

            // skips first peak
            if (seenFirstPeak == false) {
                seenFirstPeak = true;
            } else {
                m_currentBpm = (60 * sampleRate) / samplesSinceLastBeat;
                emit hrValChanged(m_currentBpm);
            }
            
            // reset clock and cooldown timer
            samplesSinceLastBeat = 0;
            refractoryCounter = refractoryPeriod;
        }

        // sets that the previous value was above the threshold
        wasAboveThreshold = (recentEcgVal > threshold);
    }
}