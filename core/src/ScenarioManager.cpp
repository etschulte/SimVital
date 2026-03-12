#include "../include/ScenarioManager.hpp"
#include "../include/PatientScenario.hpp"

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QDebug>


PatientScenario ScenarioManager::loadScenario(const QString& jsonFile) const {
    PatientScenario scenario;
    QFile file(jsonFile);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open scenario file: " << jsonFile;
        return scenario;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    QJsonObject jsonObj = jsonDoc.object();

    scenario.name = jsonObj["name"].toString();
    scenario.ecgFile = jsonObj["ecgFile"].toString();
    scenario.spo2 = jsonObj["Spo2"].toInt();
    scenario.spo2UpperAlarm = jsonObj["Spo2UpperAlarm"].toInt();
    scenario.spo2LowerAlarm = jsonObj["Spo2LowerAlarm"].toInt();
    scenario.respiratoryRate = jsonObj["RespiratoryRate"].toInt();
    scenario.rrUpperAlarm = jsonObj["RRUpperAlarm"].toInt();
    scenario.rrLowerAlarm = jsonObj["RRLowerAlarm"].toInt();
    scenario.nibpSystolic = jsonObj["NIBPSystolic"].toInt();
    scenario.nibpDiastolic = jsonObj["NIBPDiastolic"].toInt();
    scenario.nibpUpperAlarm = jsonObj["NIBPUpperAlarm"].toInt();
    scenario.nibpLowerAlarm = jsonObj["NIBPLowerAlarm"].toInt();

    return scenario;
}