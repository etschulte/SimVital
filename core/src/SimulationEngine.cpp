#include "SimulationEngine.hpp"

SimulationEngine::SimulationEngine(QObject* parent) 
    : QObject(parent), 
    parser(),
    buffer(1024),
    nibpGen(),
    rrGen(),
    spo2Gen(),
    spo2WaveGen(),
    manager(),
    thread(),
    flag(false)
{
    switchScenario("data/jsonFiles/normal.json");
}

SimulationEngine::~SimulationEngine() {
    flag = true;
    if (thread.joinable()) {
        thread.join();
    }
}

void SimulationEngine::fillBuffer() {
    while(!flag) {
        int val;

        if (!parser.getNextVal(val)) break;

        int dummyVal;
        if (!parser.getNextVal(dummyVal)) break;

        while (!buffer.write(val)) {

            if (flag) return;

            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
}

void SimulationEngine::switchScenario(QString scenarioFile) {
    if (thread.joinable()) {
        flag = true;
        thread.join();
    }

    PatientScenario scenario = manager.loadScenario(scenarioFile);

    m_currentScenario = scenario.name;
    emit currentScenarioChanged();
    emit scenarioLoaded(scenario.ecgThreshold, scenario.ecgSlopeThreshold);

    parser.loadFile(scenario.ecgFile, scenario.startingIndex);
    spo2Gen.setTargetVal(scenario.spo2);
    rrGen.setTargetVal(scenario.respiratoryRate);
    nibpGen.setSystolicVal(scenario.nibpSystolic);
    nibpGen.setDiastolicVal(scenario.nibpDiastolic);

    buffer.reset();

    flag = false;
    thread = std::thread(&SimulationEngine::fillBuffer, this);
}

MitBihParser* SimulationEngine::getParser() {
    return &parser;
}

RingBuffer* SimulationEngine::getBuffer() {
    return &buffer;
}

NibpGenerator* SimulationEngine::getNibpGen() {
    return &nibpGen;
}

RrGenerator* SimulationEngine::getRRGen() {
    return &rrGen;
}

SpO2Generator* SimulationEngine::getSpO2Gen() {
    return &spo2Gen;
}

SpO2WaveGenerator* SimulationEngine::getSpO2WaveGen() {
    return &spo2WaveGen;
}

ScenarioManager* SimulationEngine::getScenarioManager() {
    return &manager;
}

#include "moc_SimulationEngine.cpp"

