#include "../include/NibpGenerator.hpp"

#include <cstdlib>

NibpGenerator::NibpGenerator(int systolicVal, int diastolicVal) 
    : systolicVal(systolicVal),
    diastolicVal(diastolicVal)
    {

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