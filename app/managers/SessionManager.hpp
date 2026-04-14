#pragma once

#include <QObject>
#include <QString>

#include "DatabaseManager.hpp"

class SessionManager : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString currentUserRole READ getUserRole NOTIFY userRoleChanged)
    Q_PROPERTY(QString currentUserName READ getUserName NOTIFY currentUserNameChanged)

private:
    QString m_currentRole;
    QString m_currentUserName;
    bool m_isLoggedIn;
    DatabaseManager* dbManagerPtr;

public:
    SessionManager(DatabaseManager* db, QObject* parent = nullptr);

    Q_INVOKABLE void login(const QString& username, const QString& password);
    
    Q_INVOKABLE void logout();

    QString getUserRole() const;

    QString getUserName() const;

signals:
    void userRoleChanged();

    void currentUserNameChanged();

    void loginFailed();

    void loginSuccess();
};