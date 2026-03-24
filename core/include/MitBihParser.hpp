#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include <QString>

class MitBihParser {
private:
    std::ifstream fileStream; //file handler
    bool secondSamplePending; //flag value for leftover values
    int pendingSampleVal; //storage for leftover value

public:
    MitBihParser();
    ~MitBihParser();

    bool loadFile(const QString &filePath);

    bool getNextVal(int& value);

};
