#pragma once

#include <utility>

class NibpGenerator {
private:
    int systolicVal;
    int diastolicVal;

public:
    NibpGenerator(int systolicVal, int diastolicVal);

    std::pair<int, int> generateReading();
};