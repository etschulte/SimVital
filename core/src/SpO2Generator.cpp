#include "../include/PatientScenario.hpp"
#include "../include/SpO2Generator.hpp"

#include <QRandomGenerator>

SpO2Generator::SpO2Generator(QObject* parent) 
    : QObject(parent),
    targetVal(98),
    currentVal(98),
    currentHr(60)
    {

    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &SpO2Generator::createNoise);
    timerPtr->start(1000);
}

SpO2Generator::SpO2Generator(int targetVal, QObject* parent) 
    : QObject(parent),
    targetVal(targetVal),
    currentVal(targetVal),
    currentHr(60)
    {

    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &SpO2Generator::createNoise);
    timerPtr->start(1000);
}

SpO2Generator::~SpO2Generator() {}

void SpO2Generator::setTargetVal(int newTargetVal) {
    targetVal = newTargetVal;
}

void SpO2Generator::setHeartRate(int hr) {
    currentHr = hr;
}

void SpO2Generator::createNoise() {
    int randNum = QRandomGenerator::global()->bounded(1, 101);

    if (randNum >= 80 && randNum < 90) {
        currentVal++;
    }
    else if (randNum >= 90 && randNum < 100) {
        currentVal--;
    }

    if (currentVal > (targetVal + 2)) {
        currentVal--;
    }
    
    if (currentVal < (targetVal - 2)) {
        currentVal++;
    }

    if (currentVal > 100) {
        currentVal = 100;
    }

    if (currentHr <= 0) {
        emit spO2ValChanged(-1);
    } else {
        emit spO2ValChanged(currentVal);
    }
}

