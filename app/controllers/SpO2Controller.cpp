#include "SpO2Controller.hpp"

SpO2Controller::SpO2Controller(SpO2Generator* generator, QObject* parent) 
    : QObject(parent),
    generatorPtr(generator),
    latestSpO2Val(0),
    lowerLimit(90),
    isAlarming(false),
    isSilenced(true)
    {
    connect(generatorPtr, &SpO2Generator::spO2ValChanged, this, &SpO2Controller::updateSpO2Val);
}

int SpO2Controller::getSpO2Val() const {
    return latestSpO2Val;
}

bool SpO2Controller::getIsAlarming() const {
    return isAlarming;
}

void SpO2Controller::loadLimits(const PatientScenario& scenario) {
    lowerLimit = scenario.spo2LowerAlarm;
}

void SpO2Controller::resetState() {
    isAlarming = false;

    emit alarmStateChanged();
}

void SpO2Controller::updateAlarm(bool alarmStatus) {

    if (isAlarming != alarmStatus) {
        isAlarming = alarmStatus;

        if (isAlarming == true) {
            isSilenced = false;
        }

        emit alarmStateChanged();
    }

}

void SpO2Controller::updateSpO2Val(int spO2Val) {
    latestSpO2Val = spO2Val;

    bool shouldBeAlarming = (latestSpO2Val <= lowerLimit);

    updateAlarm(shouldBeAlarming);

    emit spO2ValChanged();
}