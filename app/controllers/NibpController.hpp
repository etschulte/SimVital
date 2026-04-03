#pragma once

#include <QObject>
#include <QString>

#include "NibpGenerator.hpp"
#include "PatientScenario.hpp"

class NibpController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString readingVal READ getNibpVal NOTIFY nibpValChanged)
    Q_PROPERTY(QString timeVal READ getTimeVal NOTIFY timeValChanged)
    Q_PROPERTY(bool isAlarming READ getIsAlarming NOTIFY alarmStateChanged)

private:
    NibpGenerator* nibpGeneratorPtr;
    QString currentNibpReading;
    QString currentTime;
    int lowerLimit;
    int upperLimit;
    bool isAlarming;
    bool isSilenced;

public:
    NibpController(NibpGenerator* generator, QObject* parent = nullptr);

    QString getNibpVal() const;

    QString getTimeVal() const;

    bool getIsAlarming() const;

public slots:
    void startMeasurement();

    void updateAlarm(bool alarmStatus);

    void loadLimits(const PatientScenario& scenario);

private slots:
    void finishMeasurement();

signals:
    void nibpValChanged();

    void timeValChanged();

    void alarmStateChanged();
};