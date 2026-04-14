#pragma once

#include <QObject>
#include <QString>

#include "DatabaseManager.hpp"

class SessionManager : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString currentUserRole READ getUserRole NOTIFY userRoleChanged)

private:
    QString m_currentRole;
    bool m_isLoggedIn;
    DatabaseManager* dbManagerPtr;

public:
    SessionManager(DatabaseManager* db, QObject* parent = nullptr);

    Q_INVOKABLE void login(const QString& username, const QString& password);
    
    Q_INVOKABLE void logout();

    QString getUserRole() const;

signals:
    void userRoleChanged();
};