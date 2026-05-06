#include "../include/MitBihParser.hpp"

MitBihParser::MitBihParser() : secondSamplePending(false), pendingSampleVal(0) {}

MitBihParser::~MitBihParser(){}

bool MitBihParser::loadFile(const QString &filePath, int startIndex) {

    if (fileStream.is_open()) {
        fileStream.close();
    }

    secondSamplePending = false;
    pendingSampleVal = 0;

    fileStream.open(filePath.toStdString(), std::ios::binary);

    if (fileStream.is_open() && startIndex > 0) {
        int byteOffset = (startIndex / 2) * 3;

        fileStream.seekg(byteOffset, std::ios::beg);
    }

    return fileStream.is_open();
}

bool MitBihParser::getNextVal(int &value) {
    
    if (secondSamplePending) {
        value = pendingSampleVal;
        secondSamplePending = false;
        return true;
    }

    uint8_t block[3];

    fileStream.read(reinterpret_cast<char*>(block), 3);

    if (fileStream.gcount() < 3) {
        return false;
    }

    int sample1 = block[0] + ((block[1] & 0x0F) << 8); 
    int sample2 = block[2] + ((block[1] & 0x0F) << 4); 

    value = sample1;
    pendingSampleVal = sample2;
    secondSamplePending = true;

    return true;
}