#include "../include/PatientScenario.hpp"
#include "../include/SpO2Generator.hpp"

SpO2Generator::SpO2Generator(int targetVal, QObject* parent) 
    : QObject(parent),
    targetVal(targetVal),
    currentVal(targetVal) 
    {

    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &SpO2Generator::createNoise);
    timerPtr->start(1000);

}

void SpO2Generator::createNoise() {

}

