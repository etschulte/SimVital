#pragma once

#include <QObject>
#include <QTimer>

class SpO2WaveGenerator : public QObject {
    Q_OBJECT

private:
    QTimer* timerPtr;
    double timeStep;
    int currentHr;

public:
    SpO2WaveGenerator(QObject* parent = nullptr);

signals:
    void valChanged(double newVal);

private slots:
    void calcNextStep();

public slots:
    void setHeartRate(int hr);
};