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
    explicit RrGenerator(QObject* parent = nullptr);
    virtual ~RrGenerator();

    RrGenerator(int targetVal, QObject* parent = nullptr);

    void setTargetVal(int newTargetVal);

signals:
    void rrValChanged(int newVal);

private slots:
    void createNoise();
};