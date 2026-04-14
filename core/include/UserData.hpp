#pragma once

#include <QString>
#include <QMetaType>

struct UserData
{
    QString firstName;
    QString lastName;
    QString role;
    QString username;
    QString passwordHash;
};

Q_DECLARE_METATYPE(UserData);