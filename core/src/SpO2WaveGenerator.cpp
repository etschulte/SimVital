#include "../include/SpO2WaveGenerator.hpp"

#include <cmath>

SpO2WaveGenerator::SpO2WaveGenerator(QObject* parent) 
    : QObject(parent), 
    timeStep(0.0),
    currentHr(60) 
    {
    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &SpO2WaveGenerator::calcNextStep);
    timerPtr->start(16);
}

SpO2WaveGenerator::~SpO2WaveGenerator() {}

void SpO2WaveGenerator::calcNextStep() {
    double wave = 0.0;

    if (currentHr > 0) {
        double increment = 6.28 * (currentHr / 60.0) * 0.016;
        timeStep += increment;
        wave = std::sin(timeStep);
    }
    
    emit valChanged(wave);
}

void SpO2WaveGenerator::setHeartRate(int hr) {
    currentHr = hr;
}