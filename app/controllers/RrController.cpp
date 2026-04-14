#include "RrController.hpp"
#include <QDebug>

RrController::RrController(RrGenerator* generator, QObject* parent) 
    : QObject(parent),
    generatorPtr(generator),
    latestRR(0),
    upperLimit(25),
    lowerLimit(10),
    isAlarming(false),
    isSilenced(true)
    {
    connect(generatorPtr, &RrGenerator::rrValChanged, this, &RrController::updateRRVal);
}

int RrController::getRRVal() const {
    return latestRR;
}

bool RrController::getIsAlarming() const {
    return isAlarming;
}

void RrController::loadLimits(const PatientScenario& scenario) {
    upperLimit = scenario.rrUpperAlarm;
    lowerLimit = scenario.rrLowerAlarm;
}

void RrController::resetState() {
    isAlarming = false;

    emit alarmStateChanged();
}

void RrController::updateAlarm(bool alarmStatus) {

    if (isAlarming != alarmStatus) {
        isAlarming = alarmStatus;

        if (isAlarming == true) {
            isSilenced = false;
        }

        emit alarmStateChanged();
    }
}

void RrController::updateRRVal(int rrVal) {
    bool shouldBeAlarming = false;
    latestRR = rrVal;

    shouldBeAlarming = (latestRR <= lowerLimit || latestRR >= upperLimit);
    updateAlarm(shouldBeAlarming);

    emit rrValChanged();
}