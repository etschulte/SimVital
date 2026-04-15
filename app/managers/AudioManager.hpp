#pragma once

#include <QTimer>
#include <QObject>
#include <QSoundEffect>

#include "controllers/EcgController.hpp"
#include "controllers/SpO2Controller.hpp"
#include "controllers/NibpController.hpp"
#include "controllers/RrController.hpp"

class AudioManager : public QObject {
    Q_OBJECT

private:
    EcgController* ecgPtr;
    SpO2Controller* spo2Ptr;
    NibpController* nibpPtr;
    RrController* rrPtr;
    QTimer* timerPtr;
    QSoundEffect* audioPlayerPtr;
    bool m_systemActive;
    bool m_inAdminMenu;

public:
    AudioManager(EcgController* ecg, SpO2Controller* spo2, NibpController* nibp, RrController* rr, QObject* parent = nullptr);

    Q_INVOKABLE void silenceAlarms();

    Q_INVOKABLE void setAdminMute(bool isMuted);

    void reset();

    void setSystemActive(bool active);

public slots:
    void evaluateAudioState();
};

