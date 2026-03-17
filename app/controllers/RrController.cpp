#include "RrController.hpp"

RrController::RrController(RrGenerator* generator, QObject* parent) 
    : QObject(parent),
    generatorPtr(generator),
    latestRR(0)
    {
    connect(generatorPtr, &RrGenerator::rrValChanged, this, &RrController::updateRRVal);
}

int RrController::getRRVal() const {
    return latestRR;
}

void RrController::updateRRVal(int rrVal) {
    latestRR = rrVal;

    emit rrValChanged();
}