#include "EcgController.hpp"
#include <QDebug>

EcgController::EcgController(MitBihParser* parser, RingBuffer* buffer, EcgGenerator* generator, QObject* parent) 
    : QObject(parent), 
    parserPtr(parser), 
    bufferPtr(buffer),
    ecgGenPtr(generator),
    timerPtr(nullptr),    
    upperLimit(120),
    lowerLimit(50),
    isAlarming(false),
    isSilenced(true)
    {

    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &EcgController::onTick); 
    timerPtr->start(1000 / ecgGenPtr->sampleRate);

}

EcgController::~EcgController() {}

int EcgController::getEcgVal() const {
    return ecgGenPtr->getRecentEcgVal();
}

int EcgController::getHRVal() const {
    return ecgGenPtr->getCurrentBpm();
}

void EcgController::passThresholdsToGen(const PatientScenario& scenario) {
    if (ecgGenPtr) {
        ecgGenPtr->setThresholds(scenario.ecgThreshold, scenario.ecgSlopeThreshold);
    }
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
    int m_recentEcgVal = getEcgVal();
    int m_currentBpm = getHRVal();

    if (bufferPtr->read(nextVal)) {
        
        m_recentEcgVal = nextVal;
        emit ecgValChanged(m_recentEcgVal);

        if (ecgGenPtr) {
            ecgGenPtr->calculateEcgValues(nextVal);
            
            int newBpm = ecgGenPtr->getCurrentBpm();

            if (newBpm != m_currentBpm) {
                m_currentBpm = newBpm;
                emit hrValChanged(m_currentBpm);
            }
        }

        bool shouldBeAlarming = (m_currentBpm <= lowerLimit || m_currentBpm >= upperLimit);
        updateAlarm(shouldBeAlarming);
    }
}