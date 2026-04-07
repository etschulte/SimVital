#include "RrController.hpp"

RrController::RrController(RrGenerator* generator, QObject* parent) 
    : QObject(parent),
    generatorPtr(generator),
    latestRR(0),
    lowerLimit(0),
    upperLimit(0),
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
    latestRR = rrVal;

    emit rrValChanged();
}