#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include <QString>

class MitBihParser {
private:
    std::ifstream fileStream; 
    bool secondSamplePending; 
    int pendingSampleVal; 

public:
    MitBihParser();
    ~MitBihParser();

    bool loadFile(const QString &filePath, int startIndex);

    bool getNextVal(int& value);

};
