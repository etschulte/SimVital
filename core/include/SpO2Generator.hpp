#pragma once

#include <QObject>
#include <QTimer>

class SpO2Generator : public QObject {
    Q_OBJECT

private: 
    int targetVal;
    int currentVal;
    int currentHr;
    QTimer* timerPtr;

public:
    SpO2Generator(QObject* parent = nullptr);
    SpO2Generator(int targetVal, QObject* parent = nullptr);
    ~SpO2Generator();

    void setTargetVal(int newTargetVal);

    void setHeartRate(int hr);

signals:
    void spO2ValChanged(int newVal);

private slots:
    void createNoise();

};