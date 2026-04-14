#pragma once

#include <QtSql>
#include <QObject>
#include <QList>

#include "UserData.hpp"

class DatabaseManager : public QObject {
    Q_OBJECT

private:
    QSqlDatabase dbConnection;

public:
    DatabaseManager(QObject* parent = nullptr);

    void initDatabase();

    UserData verifyUser(const QString& username, const QString& password);

    bool addUser(const QString& firstName, const QString& lastName, const QString& role, const QString& username, const QString& password);

    bool removeUser(const QString& username);

    QList<UserData> getAllUsers();
};