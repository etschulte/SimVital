#include "DatabaseManager.hpp"

#include <QDebug>

DatabaseManager::DatabaseManager() {
    dbConnection = QSqlDatabase::addDatabase("QSQLITE");
    dbConnection.setDatabaseName("simvital.db");
}

void DatabaseManager::initDatabase() {
    if (!dbConnection.open()) {
        qDebug() << "Connection to database failed";
    }

    QSqlQuery initQuery;
    QString queryText = "CREATE TABLE IF NOT EXISTS users ("
        "userID integer primary key autoincrement,"
        "firstName TEXT,"
        "lastName TEXT,"
        "role TEXT,"
        "username TEXT unique,"
        "passwordHash TEXT"
        ");";
}