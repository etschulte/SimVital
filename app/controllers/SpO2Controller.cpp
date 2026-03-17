#include "SpO2Controller.hpp"

SpO2Controller::SpO2Controller(SpO2Generator* generator, QObject* parent) 
    : QObject(parent),
    generatorPtr(generator),
    latestSpO2Val(0) 
    {
    connect(generatorPtr, &SpO2Generator::spO2ValChanged, this, &SpO2Controller::updateSpO2Val);
}


int SpO2Controller::getSpO2Val() const {
    return latestSpO2Val;
}

void SpO2Controller::updateSpO2Val(int spO2Val) {
    latestSpO2Val = spO2Val;
    
    emit spO2ValChanged();
}



