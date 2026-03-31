#pragma once

#include <utility>

class NibpGenerator {
private:
    int systolicVal;
    int diastolicVal;

public:

    NibpGenerator();

    NibpGenerator(int systolicVal, int diastolicVal);

    void setSystolicVal(int newSystolic);

    void setDiastolicVal(int newDiastolic);

    std::pair<int, int> generateReading();
};