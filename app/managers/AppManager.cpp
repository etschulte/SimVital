#include "AppManager.hpp"

#include <QQmlContext>

AppManager::AppManager() 
    : ecgController(simEngine.getParser(), simEngine.getBuffer(), simEngine.getEcgGen()),
    spO2Controller(simEngine.getSpO2Gen()),
    spO2WaveController(simEngine.getSpO2WaveGen()),
    rrController(simEngine.getRRGen()),
    nibpController(simEngine.getNibpGen()),
    audioManager(&ecgController, &spO2Controller, &nibpController, &rrController),
    sessionManager(&dbManager),
    adminManager(&dbManager)
    {
    QObject::connect(&ecgController, &EcgController::hrValChanged, simEngine.getSpO2WaveGen(), &SpO2WaveGenerator::setHeartRate);
    QObject::connect(&ecgController, &EcgController::hrValChanged, simEngine.getSpO2Gen(), &SpO2Generator::setHeartRate);
    
    QObject::connect(&simEngine, &SimulationEngine::scenarioLoaded, &ecgController, &EcgController::passThresholdsToGen);
    QObject::connect(&simEngine, &SimulationEngine::scenarioLoaded, &ecgController, &EcgController::loadLimits);
    QObject::connect(&simEngine, &SimulationEngine::scenarioLoaded, &ecgController, &EcgController::resetState);

    QObject::connect(&simEngine, &SimulationEngine::scenarioLoaded, &spO2Controller, &SpO2Controller::loadLimits);
    QObject::connect(&simEngine, &SimulationEngine::scenarioLoaded, &spO2Controller, &SpO2Controller::resetState);
    
    QObject::connect(&simEngine, &SimulationEngine::scenarioLoaded, &rrController, &RrController::loadLimits);
    QObject::connect(&simEngine, &SimulationEngine::scenarioLoaded, &rrController, &RrController::resetState);

    QObject::connect(&simEngine, &SimulationEngine::scenarioLoaded, &nibpController, &NibpController::loadLimits);
    QObject::connect(&simEngine, &SimulationEngine::scenarioLoaded, &nibpController, &NibpController::resetState);

    QObject::connect(&sessionManager, &SessionManager::userRoleChanged, [this]() {
        if (sessionManager.getUserRole() != "") {
            simEngine.startSimulation();
            audioManager.setSystemActive(true);
            qDebug() << "Session active: Simulation started";
        } else {
            simEngine.stopSimulation();
            audioManager.setSystemActive(false);
            qDebug() << "Session ended: Simulation stopped";
        }
    });
    QObject::connect(&sessionManager, &SessionManager::userLoggedOut, &nibpController, &NibpController::resetReading);
}

void AppManager::setContext(QQmlApplicationEngine* engine) {
    engine->rootContext()->setContextProperty("ecgController", &ecgController);
    engine->rootContext()->setContextProperty("spo2Controller", &spO2Controller);
    engine->rootContext()->setContextProperty("spo2WaveController", &spO2WaveController);
    engine->rootContext()->setContextProperty("rrController", &rrController);
    engine->rootContext()->setContextProperty("nibpController", &nibpController);
    engine->rootContext()->setContextProperty("simEngine", &simEngine);
    engine->rootContext()->setContextProperty("audioManager", &audioManager);
    engine->rootContext()->setContextProperty("sessionManager", &sessionManager);
    engine->rootContext()->setContextProperty("adminManager", &adminManager);
}