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
    Q_PROPERTY(QString currentScenario READ currentScenario NOTIFY currentScenarioChanged)

private:
    ScenarioManager manager;
    MitBihParser parser;
    RingBuffer buffer;
    NibpGenerator nibpGen;
    RrGenerator rrGen;
    SpO2Generator spo2Gen;
    SpO2WaveGenerator spo2WaveGen;
    QString m_currentScenario;
    std::thread thread;
    std::atomic<bool> flag;

public:
    explicit SimulationEngine(QObject* parent = nullptr);
    virtual ~SimulationEngine();

    QString currentScenario() const { return m_currentScenario; }

    void fillBuffer();

    Q_INVOKABLE void switchScenario(QString scenarioFile);

    Q_INVOKABLE void startSimulation();

    Q_INVOKABLE void stopSimulation();

    MitBihParser* getParser();

    RingBuffer* getBuffer();

    NibpGenerator* getNibpGen();

    RrGenerator* getRRGen();

    SpO2Generator* getSpO2Gen();

    SpO2WaveGenerator* getSpO2WaveGen();

    ScenarioManager* getScenarioManager();

signals:
    void currentScenarioChanged();

    void scenarioLoaded(const PatientScenario &scenario);
};