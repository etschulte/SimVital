#pragma once

#include <QtSql>
#include <QObject>


class DatabaseManager : public QObject {
    Q_OBJECT

private:
    QSqlDatabase dbConnection;

public:
    DatabaseManager();

    void initDatabase();
};