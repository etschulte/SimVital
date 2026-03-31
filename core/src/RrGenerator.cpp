#include "../include/RrGenerator.hpp"

#include <QRandomGenerator>

RrGenerator::RrGenerator(QObject* parent)
    : QObject(parent),
    targetVal(16),
    currentVal(16) 
    {

    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &RrGenerator::createNoise);
    timerPtr->start(1000);
}

RrGenerator::RrGenerator(int targetVal, QObject* parent)
    : QObject(parent),
    targetVal(targetVal),
    currentVal(targetVal)
    {
    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &RrGenerator::createNoise);
    timerPtr->start(1000);
}

RrGenerator::~RrGenerator() {}

void RrGenerator::setTargetVal(int newTargetVal) {
    targetVal = newTargetVal;
}

void RrGenerator::createNoise() {
    int randNum = QRandomGenerator::global()->bounded(1, 17);

    if (randNum >= 0 && randNum < 2) {
        currentVal++;
    }
    else if (randNum >= 3 && randNum < 5) {
        currentVal--;
    }

    if (currentVal > (targetVal + 2)) {
        currentVal--;
    }
    
    if (currentVal < (targetVal - 2)) {
        currentVal++;
    }

    if (currentVal < 0) {
        currentVal = 0;
    }

    emit rrValChanged(currentVal);
}