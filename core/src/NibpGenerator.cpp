#include "../include/NibpGenerator.hpp"

#include <cstdlib>

NibpGenerator::NibpGenerator()
    : systolicVal(120),
    diastolicVal(80) 
    {
}

NibpGenerator::NibpGenerator(int systolicVal, int diastolicVal) 
    : systolicVal(systolicVal),
    diastolicVal(diastolicVal)
    {
}

void NibpGenerator::setSystolicVal(int newSystolic) {
    systolicVal = newSystolic;
}

void NibpGenerator::setDiastolicVal(int newDiastolic) {
    diastolicVal = newDiastolic;
}

std::pair<int, int> NibpGenerator::generateReading() {
    int randNum = rand() % 7;
    int calculatedSystolic = systolicVal;
    int calculatedDiastolic = diastolicVal;
    int increment = randNum - 3;

    calculatedSystolic += increment;
    calculatedDiastolic += increment;

    return std::make_pair(calculatedSystolic, calculatedDiastolic);
}

