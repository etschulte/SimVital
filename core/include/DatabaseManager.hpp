#pragma once

#include <QtSql>
#include <QObject>

#include "UserData.hpp"


class DatabaseManager : public QObject {
    Q_OBJECT

private:
    QSqlDatabase dbConnection;

public:
    DatabaseManager(QObject* parent = nullptr);

    void initDatabase();

    UserData verifyUser(const QString& username, const QString& password);
};