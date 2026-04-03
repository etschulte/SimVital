#pragma once

#include <QObject>

#include "RrGenerator.hpp"
#include "PatientScenario.hpp"

class RrController : public QObject {
    Q_OBJECT
    Q_PROPERTY(int rrVal READ getRRVal NOTIFY rrValChanged)
    Q_PROPERTY(bool isAlarming READ getIsAlarming NOTIFY alarmSateChanged)

private:
    int latestRR;
    RrGenerator* generatorPtr;
    int lowerLimit;
    int upperLimit;
    bool isAlarming;
    bool isSilenced;

public:
    RrController(RrGenerator* generator, QObject* parent = nullptr);

    int getRRVal() const;

    bool getIsAlarming() const;

public slots:
    void updateRRVal(int rrVal);

    void updateAlarm(bool alarmStatus);

    void loadLimits(const PatientScenario& scenario);

signals:
    void rrValChanged();

    void alarmSateChanged();
};