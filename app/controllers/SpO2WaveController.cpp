#include "SpO2WaveController.hpp"

SpO2WaveController::SpO2WaveController(SpO2WaveGenerator* waveGenerator, QObject* parent) 
    : QObject(parent),
    waveGeneratorPtr(waveGenerator)
    {
    connect(waveGeneratorPtr, &SpO2WaveGenerator::valChanged, this, &SpO2WaveController::updateWaveVal);
}

void SpO2WaveController::updateWaveVal(double waveVal) {
    emit waveValChanged(waveVal);
}