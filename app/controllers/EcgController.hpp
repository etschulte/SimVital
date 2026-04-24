#pragma once

#include <QObject>
#include <QTimer>
#include "MitBihParser.hpp"
#include "RingBuffer.hpp"
#include "PatientScenario.hpp"
#include "EcgGenerator.hpp"


class EcgController : public QObject {
    Q_OBJECT 
    Q_PROPERTY(int ecgVal READ getEcgVal NOTIFY ecgValChanged)
    Q_PROPERTY(int hrVal READ getHRVal NOTIFY hrValChanged)
    Q_PROPERTY(bool isAlarming READ getIsAlarming NOTIFY alarmStateChanged)

private:
    MitBihParser* parserPtr; 
    RingBuffer* bufferPtr; 
    QTimer* timerPtr; 
    EcgGenerator* ecgGenPtr;
    
    int upperLimit;
    int lowerLimit;
    bool isAlarming;
    bool isSilenced;

public:
    

    // Contstructor and destructor 
    EcgController(MitBihParser* parser, RingBuffer* buffer, EcgGenerator* generator, QObject* parent = nullptr);
    ~EcgController();

    // getter class for ECG value
    int getEcgVal() const;

    // getter class for heart rate value
    int getHRVal() const;

    void passThresholdsToGen(const PatientScenario& scenario);

    bool getIsAlarming() const;

signals:
    // Signals that the ECG value has changed
    void ecgValChanged(int ecgVal);

    // Signlas that the heart rate value has changed
    void hrValChanged(int hrVal);

    void alarmStateChanged();

public slots:
    void loadLimits(const PatientScenario& scenario);

    void updateAlarm(bool alarmStatus);

    void resetState();

private slots:
    // Callback for QTimer to grab next number from buffer
    void onTick();
};
