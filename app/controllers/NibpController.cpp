#include "NibpController.hpp"

#include <cstdlib>
#include <QDateTime>
#include <QTimer>

NibpController::NibpController(NibpGenerator* generator, QObject* parent) 
    : QObject(parent),
    nibpGeneratorPtr(generator),
    currentNibpReading("--"),
    currentTime("--"),
    upperLimit(0),
    lowerLimit(0),
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

void NibpController::finishMeasurement() {
    std::pair<int, int> valuePair = nibpGeneratorPtr->generateReading();
    
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