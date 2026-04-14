#include "SessionManager.hpp"

SessionManager::SessionManager(DatabaseManager* db, QObject* parent) 
    : QObject(parent),
    dbManagerPtr(db),
    m_currentRole(""),
    m_isLoggedIn(false)
    {
}

void SessionManager::login(const QString& username, const QString& password) {
    QString loginAttempt = dbManagerPtr->verifyUser(username, password);

    if (loginAttempt != "") {
        m_currentRole = loginAttempt;
        m_isLoggedIn = true;

        emit loginSuccess();
        emit userRoleChanged();
    } else {
        emit loginFailed();
    }
}

void SessionManager::logout() {
    m_currentRole = "";
    m_isLoggedIn = false;

    emit userRoleChanged();
}

QString SessionManager::getUserRole() const {
    return m_currentRole;
}