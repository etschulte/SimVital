#pragma once

#include <QObject>
#include <QTimer>
#include "MitBihParser.hpp"
#include "RingBuffer.hpp"


class EcgController : public QObject {
    Q_OBJECT // QObject Macro
    Q_PROPERTY(int ecgVal READ getEcgVal NOTIFY ecgValChanged) // QProperty Macro
    Q_PROPERTY(int hrVal READ getHRVal NOTIFY hrValChanged)

private:
    MitBihParser* parserPtr; // Pointer to the MitBihParser so that we can use that object when created in main
    RingBuffer* bufferPtr; // Pointer to RingBuffer so we can use that object when created in main
    QTimer* timerPtr; // Pointer to QTimer to act as a pacemaker for pulling data
    int recentEcgVal; // Most recent ECG value

    int threshold; // threshold data must cross
    int slopeThreshold;
    bool wasAboveThreshold; // checks if current value is above threshold
    int samplesSinceLastBeat; // increments for each data point
    int refractoryCounter; // cooldown timer
    int m_currentBpm; // stores calculated current BPM
    bool seenFirstPeak; // tracks if we have seen the first peak yet

public:
    const int sampleRate = 360; // amount of data points that equal 1 second
    const int refractoryPeriod = 90;  // amount of samples we want to ignore the data for

    // Contstructor and destructor 
    EcgController(MitBihParser* parser, RingBuffer* buffer, QObject* parent = nullptr);
    ~EcgController();

    // getter class for ECG value
    int getEcgVal() const;

    // getter class for heart rate value
    int getHRVal() const;

    void setThresholds(int threshold, int slopeThreshold);

signals:
    // Signals that the ECG value has changed
    void ecgValChanged(int ecgVal);

    // Signlas that the heart rate value has changed
    void hrValChanged(int hrVal);

private slots:
    // Callback for QTimer to grab next number from buffer
    void onTick();
};
