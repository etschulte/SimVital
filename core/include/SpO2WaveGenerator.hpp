#pragma once

#include <QObject>
#include <QTimer>

class SpO2WaveGenerator : public QObject {
    Q_OBJECT

private:
    QTimer* timerPtr;
    double timeStep;

public:
    SpO2WaveGenerator(QObject* parent = nullptr);

signals:
    void valChanged(double newVal);

private slots:
    void calcNextStep();
};