#pragma once

#include <QObject>

#include "SpO2Generator.hpp"

class SpO2Controller : public QObject {
    Q_OBJECT
    Q_PROPERTY(int spO2Val READ getSpO2Val NOTIFY spO2ValChanged)

private:
    int latestSpO2Val;
    SpO2Generator* generatorPtr;
    
public:
    SpO2Controller(SpO2Generator* generatorPtr, QObject* parent = nullptr);

    int getSpO2Val() const;

public slots:
    void updateSpO2Val(int spO2Val);

signals:
    

};