#pragma once

#include <QObject>
#include <QTimer>

class RrGenerator : public QObject {
    Q_OBJECT

private: 
    int targetVal;
    int currentVal;
    QTimer* timerPtr;

public:
    RrGenerator(int targetVal, QObject* parent = nullptr);

signals:
    void rrValChanged(int newVal);

private slots:
    void createNoise();
};