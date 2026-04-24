#pragma once

#include <QQmlApplicationEngine>

#include "controllers/EcgController.hpp"
#include "controllers/NibpController.hpp"
#include "controllers/RrController.hpp"
#include "controllers/SpO2Controller.hpp"
#include "controllers/SpO2WaveController.hpp"
#include "managers/AdminManager.hpp"
#include "managers/AudioManager.hpp"
#include "managers/SessionManager.hpp"
#include "../core/include/SimulationEngine.hpp"
#include "../core/include/MitBihParser.hpp"
#include "../core/include/RingBuffer.hpp"
#include "../core/include/ScenarioManager.hpp"
#include "../core/include/SpO2Generator.hpp"
#include "../core/include/SpO2WaveGenerator.hpp"
#include "../core/include/RrGenerator.hpp"
#include "../core/include/NibpGenerator.hpp"
#include "../core/include/DatabaseManager.hpp"


class AppManager {

private:
    SimulationEngine simEngine;
    DatabaseManager dbManager;
    EcgController ecgController;
    SpO2Controller spO2Controller;
    SpO2WaveController spO2WaveController;
    RrController rrController;
    NibpController nibpController;
    AudioManager audioManager;
    SessionManager sessionManager;
    AdminManager adminManager;
    
public:
    AppManager();

    void setContext(QQmlApplicationEngine* engine);
};