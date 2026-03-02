#pragma once

#include <QObject>
#include <QTimer>
#include "MitBihParser.hpp"
#include "RingBuffer.hpp"


class EcgController : public QObject {
private:
    Q_OBJECT // QObject Macro
    Q_PROPERTY(int ecgVal READ getEcgVal NOTIFY ecgValChanged) // QProperty Macro
    MitBihParser* parserPtr; // Pointer to the MitBihParser so that we can use that object when created in main
    RingBuffer* bufferPtr; // Pointer to RingBuffer so we can use that object when created in main
    QTimer* timerPtr; // Pointer to QTimer to act as a pacemaker for pulling data
    int recentEcgVal; // Most recent ECG value

public:
    // Contstructor and destructor 
    EcgController(MitBihParser* parserPtr, RingBuffer* bufferPtr, QObject* parent = nullptr);
    ~EcgController();

    // getter class for ECG value
    int getEcgVal() const;

    // functions that allow us to use buttons in UI to start and stop timer
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

signals:
    // Signals that the ECG value has changed
    void ecgValChanged(int recentEcgVal);

private slots:
    // Callback for QTimer to grab next number from buffer
    void onTick();
};
