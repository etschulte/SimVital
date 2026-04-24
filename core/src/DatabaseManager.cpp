#include "DatabaseManager.hpp"

#include <QDebug>
#include <QCryptographicHash>

DatabaseManager::DatabaseManager(QObject* parent) 
    : QObject(parent)
    {
    if (QSqlDatabase::contains()) {
        dbConnection = QSqlDatabase::database();
    } else {
        dbConnection = QSqlDatabase::addDatabase("QSQLITE");
        dbConnection.setDatabaseName("simvital.db");
        initDatabase();
    }
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

    initQuery.exec(queryText);

    QSqlQuery checkQuery;
    checkQuery.exec("SELECT COUNT(*) FROM users;");
    checkQuery.next();
    int userCount = checkQuery.value(0).toInt();

    if (userCount == 0) {
        qDebug() << "Database is empty. Seeding default Admin and Instructor accounts...";

        QByteArray passwordStr = "admin123";
        QByteArray hashedData = QCryptographicHash::hash(passwordStr, QCryptographicHash::Sha256);
        QString hashedPassword = QString(hashedData.toHex()); 

        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO users (firstName, lastName, role, username, passwordHash) "
                            "VALUES (:first, :last, :role, :user, :hash)");
        
        insertQuery.bindValue(":first", "Master");
        insertQuery.bindValue(":last", "Admin");
        insertQuery.bindValue(":role", "Admin");
        insertQuery.bindValue(":user", "admin");
        insertQuery.bindValue(":hash", hashedPassword);

        if (!insertQuery.exec()) {
            qDebug() << "Failed to seed default admin!";
        } else {
            qDebug() << "Default admin created successfully.";
        }

        QByteArray instPasswordStr = "instructor123";
        QByteArray instHashedData = QCryptographicHash::hash(instPasswordStr, QCryptographicHash::Sha256);
        QString instHashedPassword = QString(instHashedData.toHex()); 

        QSqlQuery instInsertQuery;
        instInsertQuery.prepare("INSERT INTO users (firstName, lastName, role, username, passwordHash) "
                            "VALUES (:first, :last, :role, :user, :hash)");
        
        instInsertQuery.bindValue(":first", "Clinical");
        instInsertQuery.bindValue(":last", "Instructor");
        instInsertQuery.bindValue(":role", "Instructor");
        instInsertQuery.bindValue(":user", "instructor");
        instInsertQuery.bindValue(":hash", instHashedPassword);

        if (!instInsertQuery.exec()) {
            qDebug() << "Failed to seed default instructor!";
        } else {
            qDebug() << "Default instructor created successfully.";
        }
    }
}

UserData DatabaseManager::verifyUser(const QString& username, const QString& password) {
    UserData userData;
    QByteArray passwordStr = password.toUtf8();
    QByteArray hashedData = QCryptographicHash::hash(passwordStr, QCryptographicHash::Sha256);
    QString hashedInput = QString(hashedData.toHex());

    QSqlQuery query;
    query.prepare("SELECT passwordHash, role, firstName, lastName FROM users WHERE username = :user");
    query.bindValue(":user", username);

    if (query.exec()) {
        if (query.next()) {
            QString storedHash = query.value(0).toString();
            userData.role = query.value(1).toString(); 
            userData.firstName = query.value(2).toString();
            userData.lastName = query.value(3).toString();      

            if (hashedInput == storedHash) {
                qDebug() << "Login successful. Role:" << userData.role;
                return userData;
            } else {
                qDebug() << "Login failed: Invalid password.";
            }
        } else {
             qDebug() << "Login failed: Username not found.";
        }
    } else {
        qDebug() << "Database error during login:" << query.lastError().text();
    }

    return userData;
}

bool DatabaseManager::addUser(const QString& firstName, const QString& lastName, const QString& role, const QString& username, const QString& password) {
    
    QByteArray passwordStr = password.toUtf8();
    QByteArray hashedData = QCryptographicHash::hash(passwordStr, QCryptographicHash::Sha256);
    QString hashedPassword = QString(hashedData.toHex()); 

    QSqlQuery query;
    query.prepare("INSERT INTO users (firstName, lastName, role, username, passwordHash) "
                  "VALUES (:first, :last, :role, :user, :hash)");
                  
    query.bindValue(":first", firstName);
    query.bindValue(":last", lastName);
    query.bindValue(":role", role);
    query.bindValue(":user", username);
    query.bindValue(":hash", hashedPassword); 

    if (!query.exec()) {
        qDebug() << "Error adding user:" << query.lastError().text();
        return false; 
    }
    
    qDebug() << "User" << username << "added successfully.";
    return true;
}

bool DatabaseManager::removeUser(const QString& username) {
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE username = :user");
    query.bindValue(":user", username);

    if (!query.exec()) {
        qDebug() << "Error removing user:" << query.lastError().text();
        return false; 
    }
    
    qDebug() << "User" << username << "removed successfully.";
    return true;
}

QList<UserData> DatabaseManager::getAllUsers() {
    QList<UserData> userList;
    
    QSqlQuery query("SELECT firstName, lastName, role, username FROM users");

    while (query.next()) {
        UserData user;
        user.firstName = query.value(0).toString();
        user.lastName = query.value(1).toString();
        user.role = query.value(2).toString();
        user.username = query.value(3).toString(); 
        
        userList.append(user);
    }
    
    return userList;
}