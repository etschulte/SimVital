#include "NibpController.hpp"

#include <cstdlib>
#include <QDateTime>
#include <QTimer>

NibpController::NibpController(NibpGenerator* generator, QObject* parent) 
    : QObject(parent),
    nibpGeneratorPtr(generator),
    currentNibpReading("--"),
    currentTime("--")
    {

}

void NibpController::startMeasurement() {
    currentNibpReading = "Measuring...";
    emit nibpValChanged();
    
    QTimer::singleShot(3000, this, &NibpController::finishMeasurement);
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