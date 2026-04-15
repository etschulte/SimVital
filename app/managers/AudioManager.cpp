#include "AudioManager.hpp"

#include <QDebug>

AudioManager::AudioManager(EcgController* ecg, SpO2Controller* spo2, NibpController* nibp, 
    RrController* rr, QObject* parent)
    : QObject(parent),
    ecgPtr(ecg),
    spo2Ptr(spo2),
    nibpPtr(nibp),
    rrPtr(rr),
    m_systemActive(false),
    m_inAdminMenu(false)
    {
    
    timerPtr = new QTimer(this);
    timerPtr->setSingleShot(true);
    connect(timerPtr, &QTimer::timeout, this, &AudioManager::evaluateAudioState);

    audioPlayerPtr = new QSoundEffect(this);
    audioPlayerPtr->setSource(QUrl("qrc:/sounds/alarm.wav"));
    audioPlayerPtr->setLoopCount(QSoundEffect::Infinite);
    audioPlayerPtr->setVolume(0.3);

    connect(ecgPtr, &EcgController::alarmStateChanged, this, &AudioManager::evaluateAudioState);
    connect(spo2Ptr, &SpO2Controller::alarmStateChanged, this, &AudioManager::evaluateAudioState);
    connect(nibpPtr, &NibpController::alarmStateChanged, this, &AudioManager::evaluateAudioState);
    connect(rrPtr, &RrController::alarmStateChanged, this, &AudioManager::evaluateAudioState);
}

void AudioManager::evaluateAudioState() {
    if (!m_systemActive) {
        return;
    }

    bool isCrashing = ecgPtr->getIsAlarming() || spo2Ptr->getIsAlarming() || nibpPtr->getIsAlarming()
        || rrPtr->getIsAlarming();
    bool isSilenced = timerPtr->isActive();

    if (isCrashing && !isSilenced && !audioPlayerPtr->isPlaying() && !m_inAdminMenu) {
        audioPlayerPtr->play();
    } else {
        audioPlayerPtr->stop();
    }
}

void AudioManager::silenceAlarms() {
    timerPtr->start(120000);
    audioPlayerPtr->stop();
}

void AudioManager::setAdminMute(bool isMuted) {
    m_inAdminMenu = isMuted;

    if (isMuted) {
        audioPlayerPtr->stop();
    } else {
        evaluateAudioState();
    }
}

void AudioManager::reset() {
    timerPtr->stop();
    audioPlayerPtr->stop();
}

void AudioManager::setSystemActive(bool active) {
    m_systemActive = active;

    if (!m_systemActive) {
        reset();
    }
}