#pragma once

#include <QObject>

#include "DatabaseManager.hpp"
#include "../models/UserModel.hpp"

class AdminManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(UserModel* userModel READ getUserModel CONSTANT)

private:
    DatabaseManager* dbPtr;
    UserModel m_userModel;

    void refreshUserList();

public:
    AdminManager(DatabaseManager* db, QObject* parent = nullptr);

    Q_INVOKABLE bool registerUser(QString firstName, QString lastName, QString role, QString username, QString password);

    Q_INVOKABLE bool removeUser(QString username);

    UserModel* getUserModel();
};