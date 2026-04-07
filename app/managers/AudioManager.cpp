#include "AudioManager.hpp"

AudioManager::AudioManager(EcgController* ecg, SpO2Controller* spo2, NibpController* nibp, 
    RrController* rr, QObject* parent)
    : QObject(parent),
    ecgPtr(ecg),
    spo2Ptr(spo2),
    nibpPtr(nibp),
    rrPtr(rr)
    {
    
    timerPtr = new QTimer(this);
    connect(timerPtr, &QTimer::timeout, this, &AudioManager::evaluateAudioState);

    audioPlayerPtr = new QSoundEffect(this);
    audioPlayerPtr->setSource(QUrl::fromLocalFile("../data/audio/TF002.WAV"));
    audioPlayerPtr->setLoopCount(QSoundEffect::Infinite);
    audioPlayerPtr->setVolume(0.5);

    connect(ecgPtr, &EcgController::alarmStateChanged, this, &AudioManager::evaluateAudioState);
    connect(spo2Ptr, &SpO2Controller::alarmStateChanged, this, &AudioManager::evaluateAudioState);
    connect(nibpPtr, &NibpController::alarmStateChanged, this, &AudioManager::evaluateAudioState);
    connect(rrPtr, &RrController::alarmStateChanged, this, &AudioManager::evaluateAudioState);
}

void AudioManager::evaluateAudioState() {
    bool isCrashing = ecgPtr->getIsAlarming() || spo2Ptr->getIsAlarming() || nibpPtr->getIsAlarming()
        || rrPtr->getIsAlarming();
    bool isSilenced = timerPtr->isActive();

    if (isCrashing && !isSilenced) {
        audioPlayerPtr->play();
    } else {
        audioPlayerPtr->stop();
    }
}

void AudioManager::silenceAlarms() {
    timerPtr->start(120000);
    audioPlayerPtr->stop();
}