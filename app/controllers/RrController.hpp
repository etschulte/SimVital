#pragma once

#include <QObject>

#include "RrGenerator.hpp"

class RrController : public QObject {
    Q_OBJECT
    Q_PROPERTY(int rrVal READ getRRVal NOTIFY rrValChanged)

private:
    int latestRR;
    RrGenerator* generatorPtr;

public:
    RrController(RrGenerator* generator, QObject* parent = nullptr);

    int getRRVal() const;

public slots:
    void updateRRVal(int rrVal);

signals:
    void rrValChanged();
};