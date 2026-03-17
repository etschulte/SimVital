#include "../include/SpO2WaveGenerator.hpp"

#include <cmath>

SpO2WaveGenerator::SpO2WaveGenerator(QObject* parent) 
    : QObject(parent), 
    timeStep(0.0) 
    {
    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &SpO2WaveGenerator::calcNextStep);
    timerPtr->start(16);
}

void SpO2WaveGenerator::calcNextStep() {
    timeStep += 0.01;

    double wave = std::sin(timeStep);
    emit valChanged(wave);
}