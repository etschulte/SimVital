#pragma once

#include <QString>
#include <QMetaType>

struct PatientScenario
{
    QString name;
    QString ecgFile;
    int startingIndex;
    int spo2;
    int spo2UpperAlarm;
    int spo2LowerAlarm;
    int respiratoryRate;
    int rrUpperAlarm;
    int rrLowerAlarm;
    int nibpSystolic;
    int nibpDiastolic;
    int nibpUpperAlarm;
    int nibpLowerAlarm;
    int HRUpperAlarm;
    int HRLowerAlarm;
    int ecgThreshold;
    int ecgSlopeThreshold;
};

Q_DECLARE_METATYPE(PatientScenario);