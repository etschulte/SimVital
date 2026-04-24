#pragma once

class EcgGenerator {

private:
    int m_recentEcgVal; 
    int ecgThreshold; 
    int slopeThreshold;
    bool wasAboveThreshold; 
    int samplesSinceLastBeat; 
    int refractoryCounter; 
    int m_currentBpm; 
    bool seenFirstPeak; 

public:
    const int sampleRate = 360; 
    const int refractoryPeriod = 90;

    EcgGenerator();

    void calculateEcgValues(int bufferData);

    int getCurrentBpm() const;

    int getRecentEcgVal() const;

    void setThresholds(int newEcgThreshold, int newSlopeThreshold);

};