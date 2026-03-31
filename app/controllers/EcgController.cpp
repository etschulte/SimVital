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


EcgController::~EcgController() {}

int EcgController::getEcgVal() const {
    return recentEcgVal;
}

int EcgController::getHRVal() const {
    return m_currentBpm;
}

void EcgController::onTick() {
    int nextVal = 0;

    if (bufferPtr->read(nextVal)) {
        int slope = nextVal - recentEcgVal;

        recentEcgVal = nextVal;
        emit ecgValChanged(recentEcgVal);

        samplesSinceLastBeat++;

        if (refractoryCounter > 0) {
            refractoryCounter--;
        }

        if (samplesSinceLastBeat > (sampleRate * 2.5)) {
            if (m_currentBpm != 0) {
                m_currentBpm = 0;
                emit hrValChanged(m_currentBpm);
            }
        }

        int slopeThreshold = 50;

        if (refractoryCounter == 0 && recentEcgVal > threshold && slope > slopeThreshold && wasAboveThreshold == false) {
            
            if (seenFirstPeak == false) {
                seenFirstPeak = true;
            } else {
                m_currentBpm = (60 * sampleRate) / samplesSinceLastBeat;
                emit hrValChanged(m_currentBpm);
            }

            samplesSinceLastBeat = 0;
            refractoryCounter = refractoryPeriod;
        }

        wasAboveThreshold = (recentEcgVal > threshold);
    }
}