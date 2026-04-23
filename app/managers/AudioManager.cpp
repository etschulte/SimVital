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
    m_inAdminMenu(false),
    m_audioPlayer()
    {
    
    timerPtr = new QTimer(this);
    timerPtr->setSingleShot(true);
    connect(timerPtr, &QTimer::timeout, this, &AudioManager::evaluateAudioState);

    m_audioPlayer = new QProcess(this);
    connect(m_audioPlayer, &QProcess::finished, this, &AudioManager::evaluateAudioState);

    connect(ecgPtr, &EcgController::alarmStateChanged, this, &AudioManager::evaluateAudioState);
    connect(spo2Ptr, &SpO2Controller::alarmStateChanged, this, &AudioManager::evaluateAudioState);
    connect(nibpPtr, &NibpController::alarmStateChanged, this, &AudioManager::evaluateAudioState);
    connect(rrPtr, &RrController::alarmStateChanged, this, &AudioManager::evaluateAudioState);
}

AudioManager::~AudioManager() {
    m_audioPlayer->kill();
}

void AudioManager::evaluateAudioState() {
    QStringList qProcessArgs = {"-D", "plughw:CARD=UACDemoV10,0", "/home/evanpi/SimVital/data/audio/TF002.WAV"};

    if (!m_systemActive) {
        return;
    }

    bool isCrashing = ecgPtr->getIsAlarming() || spo2Ptr->getIsAlarming() || nibpPtr->getIsAlarming()
        || rrPtr->getIsAlarming();
    bool isSilenced = timerPtr->isActive();

    if (isCrashing && !isSilenced && m_audioPlayer->state() != QProcess::Running && !m_inAdminMenu) {
        m_audioPlayer->start("aplay", qProcessArgs);
    }

    if (!isCrashing || isSilenced || m_inAdminMenu) {
        m_audioPlayer->kill();
    }
}

void AudioManager::silenceAlarms() {
    timerPtr->start(120000);
    m_audioPlayer->kill();
}

void AudioManager::setAdminMute(bool isMuted) {
    m_inAdminMenu = isMuted;

    if (isMuted) {
        m_audioPlayer->kill();
    } else {
        evaluateAudioState();
    }
}

void AudioManager::reset() {
    timerPtr->stop();
    m_audioPlayer->kill();
}

void AudioManager::setSystemActive(bool active) {
    m_systemActive = active;

    if (!m_systemActive) {
        reset();
    }
}