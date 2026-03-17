#pragma once

#include "SpO2WaveGenerator.hpp"

#include <QObject>

class SpO2WaveController : public QObject {
    Q_OBJECT

private:
    SpO2WaveGenerator* waveGeneratorPtr;

public:
    SpO2WaveController(SpO2WaveGenerator* waveGenerator, QObject* parent = nullptr);

public slots:
    void updateWaveVal(double waveVal);

signals:
    void waveValChanged(double val);
};