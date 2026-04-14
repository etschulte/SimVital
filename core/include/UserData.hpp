#pragma once

#include <QString>
#include <QMetaType>

struct UserData
{
    QString firstName;
    QString lastName;
    QString role;
};

Q_DECLARE_METATYPE(UserData);