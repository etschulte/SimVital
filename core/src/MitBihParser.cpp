#include "MitBihParser.hpp"

//Constructor setting default values for variables
MitBihParser::MitBihParser() : secondSamplePending(false), pendingSampleVal(0) {}

//Nothing to cleanup so deconstructor can be empty
MitBihParser::~MitBihParser(){}

bool MitBihParser::loadFile(const std::string &filePath) {

    //close file if one is already open
    if (fileStream.is_open()) {
        fileStream.close();
    }

    //reset variables
    secondSamplePending = false;
    pendingSampleVal = 0;

    //open file
    fileStream.open(filePath, std::ios::binary);

    return fileStream.is_open();
}

bool MitBihParser::getNextVal(int &value) {
    
    //if we have a leftover sample, use that
    if (secondSamplePending) {
        value = pendingSampleVal;
        secondSamplePending = false;
        return true;
    }

    //create array of 3 8 bit unsigned integers
    uint8_t block[3];

    //cast to char
    fileStream.read(reinterpret_cast<char*>(block), 3);

    //check to make sure we got 3 bytes
    if (fileStream.gcount() < 3) {
        return false;
    }

    int sample1 = block[0] + ((block[1] & 0x0F) << 8); // uses all of byte 0 and bottom 4 bits of byte 1
    int sample2 = block[2] + ((block[1] & 0x0F) << 4); // uses all of byte 2 and top 4 bits of byte 1


    //Used to center around 2048 for graphing; not sure if I need yet
    // if (sample1 > 2048) {
    //     sample1 -= 4096;
    // }
    // if (sample2 > 2048) {
    //     sample2 -= 4096;
    // }

    value = sample1;
    pendingSampleVal = sample2;
    secondSamplePending = true;

    return true;
}


