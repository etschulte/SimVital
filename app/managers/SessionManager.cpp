#include "SessionManager.hpp"

SessionManager::SessionManager(DatabaseManager* db, QObject* parent) 
    : QObject(parent),
    dbManagerPtr(db),
    m_currentRole(""),
    m_currentUserName(""),
    m_isLoggedIn(false)
    {
}

void SessionManager::login(const QString& username, const QString& password) {
    UserData userData = dbManagerPtr->verifyUser(username, password); 

    if (userData.role != "") {
        m_currentRole = userData.role;
        m_currentUserName = userData.firstName + " " + userData.lastName;
        m_isLoggedIn = true;

        emit loginSuccess();
        emit userRoleChanged();
        emit currentUserNameChanged();
    } else {
        emit loginFailed();
    }
}

void SessionManager::logout() {
    m_currentRole = "";
    m_currentUserName = "";
    m_isLoggedIn = false;

    emit userRoleChanged();
    emit userLoggedOut();
}

QString SessionManager::getUserRole() const {
    return m_currentRole;
}

QString SessionManager::getUserName() const {
    return m_currentUserName;
}