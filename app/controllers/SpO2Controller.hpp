#pragma once

#include <QObject>

#include "SpO2Generator.hpp"
#include "PatientScenario.hpp"

class SpO2Controller : public QObject {
    Q_OBJECT
    Q_PROPERTY(int spO2Val READ getSpO2Val NOTIFY spO2ValChanged)
    Q_PROPERTY(bool isAlarming READ getIsAlarming NOTIFY alarmStateChanged)

private:
    int latestSpO2Val;
    SpO2Generator* generatorPtr;
    int lowerLimit;
    bool isAlarming;
    bool isSilenced;
    
public:
    SpO2Controller(SpO2Generator* generator, QObject* parent = nullptr);

    int getSpO2Val() const;

    bool getIsAlarming() const;

public slots:
    void updateSpO2Val(int spO2Val);

    void updateAlarm(bool alarmStatus);

    void loadLimits(const PatientScenario& scenario);

signals:
    void spO2ValChanged();

    void alarmStateChanged();
};