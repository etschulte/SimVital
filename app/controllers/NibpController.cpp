#include "NibpController.hpp"

#include <cstdlib>
#include <QDateTime>
#include <QTimer>

NibpController::NibpController(NibpGenerator* generator, QObject* parent) 
    : QObject(parent),
    nibpGeneratorPtr(generator),
    currentNibpReading("--"),
    currentTime("--"),
    upperLimit(160),
    lowerLimit(90),
    isAlarming(false),
    isSilenced(true)
    {

}

void NibpController::startMeasurement() {
    currentNibpReading = "Measuring...";
    emit nibpValChanged();
    
    QTimer::singleShot(3000, this, &NibpController::finishMeasurement);
}

bool NibpController::getIsAlarming() const {
    return isAlarming;
}

void NibpController::loadLimits(const PatientScenario& scenario) {
    upperLimit = scenario.nibpUpperAlarm;
    lowerLimit = scenario.nibpLowerAlarm;
}

void NibpController::updateAlarm(bool alarmStatus) {

    if (isAlarming != alarmStatus) {
        isAlarming = alarmStatus;

        if (isAlarming == true) {
            isSilenced = false;
        }

        emit alarmStateChanged();
    }

}

void NibpController::resetState() {
    isAlarming = false;

    emit alarmStateChanged();
}

void NibpController::finishMeasurement() {
    bool shouldBeAlarming = false;
    std::pair<int, int> valuePair = nibpGeneratorPtr->generateReading();

    shouldBeAlarming = (valuePair.first <= lowerLimit || valuePair.first >= upperLimit);
    updateAlarm(shouldBeAlarming);
    
    QString firstReading = QString::number(valuePair.first);
    QString secondReading = QString::number(valuePair.second);

    currentNibpReading = firstReading + "/" + secondReading;
    currentTime = QDateTime::currentDateTime().toString("hh:mm");

    emit nibpValChanged();
    emit timeValChanged();
}

QString NibpController::getNibpVal() const {
    return currentNibpReading;
}

QString NibpController::getTimeVal() const {
    return currentTime;
}