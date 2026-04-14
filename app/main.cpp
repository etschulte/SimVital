#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <thread>
#include <chrono>
#include <QDebug>
#include <QObject>
#include <QQmlContext>

#include "../core/include/MitBihParser.hpp"
#include "../core/include/RingBuffer.hpp"
#include "controllers/EcgController.hpp"
#include "../core/include/ScenarioManager.hpp"
#include "../core/include/PatientScenario.hpp"
#include "controllers/SpO2Controller.hpp"
#include "../core/include/SpO2Generator.hpp"
#include "controllers/SpO2WaveController.hpp"
#include "../core/include/SpO2WaveGenerator.hpp"
#include "controllers/RrController.hpp"
#include "../core/include/RrGenerator.hpp"
#include "controllers/NibpController.hpp"
#include "../core/include/NibpGenerator.hpp"
#include "../core/include/SimulationEngine.hpp"
#include "managers/AudioManager.hpp"
#include "../core/include/DatabaseManager.hpp"
#include "managers/SessionManager.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    SimulationEngine engineCore;

    DatabaseManager dbManager;
    dbManager.initDatabase();

    EcgController ecgController(engineCore.getParser(), engineCore.getBuffer());
    SpO2Controller spo2Controller(engineCore.getSpO2Gen());
    SpO2WaveController spo2WaveController(engineCore.getSpO2WaveGen());
    RrController rrController(engineCore.getRRGen());
    NibpController nipbController(engineCore.getNibpGen());

    AudioManager audioManager(&ecgController, &spo2Controller, &nipbController, &rrController);
    SessionManager sessionManager(&dbManager);

    engine.rootContext()->setContextProperty("ecgController", &ecgController);
    engine.rootContext()->setContextProperty("spo2Controller", &spo2Controller);
    engine.rootContext()->setContextProperty("spo2WaveController", &spo2WaveController);
    engine.rootContext()->setContextProperty("rrController", &rrController);
    engine.rootContext()->setContextProperty("nibpController", &nipbController);
    engine.rootContext()->setContextProperty("simEngine", &engineCore);
    engine.rootContext()->setContextProperty("audioManager", &audioManager);
    engine.rootContext()->setContextProperty("sessionManager", &sessionManager);
    
    QObject::connect(&ecgController, &EcgController::hrValChanged, engineCore.getSpO2WaveGen(), &SpO2WaveGenerator::setHeartRate);
    QObject::connect(&ecgController, &EcgController::hrValChanged, engineCore.getSpO2Gen(), &SpO2Generator::setHeartRate);
    QObject::connect(&engineCore, &SimulationEngine::scenarioLoaded, &ecgController, &EcgController::setThresholds);
    QObject::connect(&engineCore, &SimulationEngine::scenarioLoaded, &ecgController, &EcgController::loadLimits);
    QObject::connect(&engineCore, &SimulationEngine::scenarioLoaded, &spo2Controller, &SpO2Controller::loadLimits);
    QObject::connect(&engineCore, &SimulationEngine::scenarioLoaded, &rrController, &RrController::loadLimits);
    QObject::connect(&engineCore, &SimulationEngine::scenarioLoaded, &nipbController, &NibpController::loadLimits);

    const QUrl url(QStringLiteral("qrc:/qt/qml/SimVital/main.qml")); // telling the QML engine to load the main qml file
    engine.load(url);

    int exitCode = app.exec();

    return exitCode;
}