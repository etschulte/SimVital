#include "EcgGenerator.hpp"

EcgGenerator::EcgGenerator() 
    : m_recentEcgVal(0),
    ecgThreshold(1100),
    slopeThreshold(50),
    wasAboveThreshold(false),
    samplesSinceLastBeat(0),
    refractoryCounter(0),
    m_currentBpm(0) ,
    seenFirstPeak(false)
    {

}

int EcgGenerator::getCurrentBpm() const {
    return m_currentBpm;
}

int EcgGenerator::getRecentEcgVal() const {
    return m_recentEcgVal;
}

void EcgGenerator::setThresholds(int newEcgThreshold, int newSlopeThreshold) {
    ecgThreshold = newEcgThreshold;
    slopeThreshold = newSlopeThreshold;
    wasAboveThreshold = false;
    seenFirstPeak = false;
    samplesSinceLastBeat = 0;
}

void EcgGenerator::calculateEcgValues(int bufferData) {
    int slope = bufferData - m_recentEcgVal;

    m_recentEcgVal = bufferData;

    samplesSinceLastBeat++;

    if (refractoryCounter > 0) {
        refractoryCounter--;
    }

    if (samplesSinceLastBeat > (sampleRate * 2.5)) {
        if (m_currentBpm != 0) {
            m_currentBpm = 0;
        }
    }

    if (refractoryCounter == 0 && m_recentEcgVal > ecgThreshold && slope > slopeThreshold && wasAboveThreshold == false) {

        if (seenFirstPeak == false) {
                seenFirstPeak = true;
            } else {
                m_currentBpm = (60 * sampleRate) / samplesSinceLastBeat;
            }
            samplesSinceLastBeat = 0;
            refractoryCounter = refractoryPeriod;
    }   

    wasAboveThreshold = (m_recentEcgVal > ecgThreshold);
    
}

