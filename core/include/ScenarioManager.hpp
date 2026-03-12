#pragma once

#include "PatientScenario.hpp"
#include <QString>

class ScenarioManager {

public: 
    PatientScenario loadScenario(const QString& jsonFile) const;

};