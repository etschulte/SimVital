#pragma once

#include <QObject>
#include <QString>

#include "NibpGenerator.hpp"

class NibpController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString readingVal READ getNibpVal NOTIFY nibpValChanged)
    Q_PROPERTY(QString timeVal READ getTimeVal NOTIFY timeValChanged)

private:
    NibpGenerator* nibpGeneratorPtr;
    QString currentNibpReading;
    QString currentTime;

public:
    NibpController(NibpGenerator* generator, QObject* parent = nullptr);

    QString getNibpVal() const;

    QString getTimeVal() const;

public slots:
    void startMeasurement();

private slots:
    void finishMeasurement();

signals:
    void nibpValChanged();

    void timeValChanged();
};