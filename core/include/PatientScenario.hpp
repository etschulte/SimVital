#pragma once

#include <QString>

struct PatientScenario
{
    QString name;
    QString ecgFile;
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
};