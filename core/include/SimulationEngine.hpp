#pragma once

#include <QObject>
#include <thread>
#include "MitBihParser.hpp"
#include "RingBuffer.hpp"
#include "NibpGenerator.hpp"
#include "RrGenerator.hpp"
#include "SpO2Generator.hpp"
#include "SpO2WaveGenerator.hpp"
#include "ScenarioManager.hpp"
#include "PatientScenario.hpp"

class SimulationEngine : public QObject {
    Q_OBJECT

private:
    MitBihParser parser;
    RingBuffer buffer;
    NibpGenerator nibpGen;
    RrGenerator rrGen;
    SpO2Generator spo2Gen;
    SpO2WaveGenerator spo2WaveGen;
    ScenarioManager manager;
    std::thread thread;
    std::atomic<bool> flag;

public:
    SimulationEngine();

    void fillBuffer();

    Q_INVOKABLE void switchScenario(QString scenarioFile);

    MitBihParser* getParser();

    RingBuffer* getBuffer();

    NibpGenerator* getNibpGen();

    RrGenerator* getRRGen();

    SpO2Generator* getSpO2Gen();

    SpO2WaveGenerator* getSpO2WaveGen();

    ScenarioManager* getScenarioManager();
};