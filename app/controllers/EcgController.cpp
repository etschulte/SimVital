#include "EcgController.hpp"
#include <QDebug>

EcgController::EcgController(MitBihParser* parser, RingBuffer* buffer, QObject* parent) 
    : QObject(parent), 
    parserPtr(parser), 
    bufferPtr(buffer),
    timerPtr(nullptr), 
    recentEcgVal(0),
    threshold(1100),
    slopeThreshold(50),
    wasAboveThreshold(false),
    samplesSinceLastBeat(0),
    refractoryCounter(0),
    m_currentBpm(0) ,
    seenFirstPeak(false),
    upperLimit(120),
    lowerLimit(50),
    isAlarming(false),
    isSilenced(true)
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

void EcgController::setThresholds(const PatientScenario& scenario) {
    threshold = scenario.ecgThreshold;
    slopeThreshold = scenario.ecgSlopeThreshold;
    wasAboveThreshold = false;
    seenFirstPeak = false;
    samplesSinceLastBeat = 0;
}

bool EcgController::getIsAlarming() const {
    return isAlarming;
}

void EcgController::loadLimits(const PatientScenario& scenario) {
    upperLimit = scenario.HRUpperAlarm;
    lowerLimit = scenario.HRLowerAlarm;
}

void EcgController::updateAlarm(bool alarmStatus) {

    if (isAlarming != alarmStatus) {
        isAlarming = alarmStatus;

        if (isAlarming == true) {
            isSilenced = false;
        }

        emit alarmStateChanged();
    }

}

void EcgController::resetState() {
    isAlarming = false;

    emit alarmStateChanged();
}

void EcgController::onTick() {
    int nextVal = 0;
    bool shouldBeAlarming = false;

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

                shouldBeAlarming = (m_currentBpm <= lowerLimit || m_currentBpm >= upperLimit);
                updateAlarm(shouldBeAlarming);
            }
        }

        if (refractoryCounter == 0 && recentEcgVal > threshold && slope > slopeThreshold && wasAboveThreshold == false) {
            
            if (seenFirstPeak == false) {
                seenFirstPeak = true;
            } else {
                m_currentBpm = (60 * sampleRate) / samplesSinceLastBeat;
                emit hrValChanged(m_currentBpm);

                shouldBeAlarming = (m_currentBpm <= lowerLimit || m_currentBpm >= upperLimit);
                updateAlarm(shouldBeAlarming);
            }

            samplesSinceLastBeat = 0;
            refractoryCounter = refractoryPeriod;
        }   

        wasAboveThreshold = (recentEcgVal > threshold);
    }
    
}