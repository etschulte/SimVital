#pragma once

#include <QObject>
#include <QTimer>

class SpO2Generator : public QObject {
    Q_OBJECT

private: 
    int targetVal;
    int currentVal;
    QTimer* timerPtr;

public:
    SpO2Generator(int targetVal, QObject* parent = nullptr);

    

signals:
    void spO2ValChanged(int newVal);

private slots:
    void createNoise();

};