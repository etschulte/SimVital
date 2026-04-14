#include "AdminManager.hpp"

AdminManager::AdminManager(DatabaseManager* db, QObject* parent) 
    : QObject(parent),
    dbPtr(db)
    {
        refreshUserList();
}

void AdminManager::refreshUserList() {
    QList<UserData> users = dbPtr->getAllUsers();

    m_userModel.setUsers(users);
}

bool AdminManager::registerUser(QString firstName, QString lastName, QString role, QString username, QString password) {
    bool tryAddUser = dbPtr->addUser(firstName, lastName, role, username, password);

    if (!tryAddUser) {
        return tryAddUser;
    } else {
        refreshUserList();
    }
    return tryAddUser;
}

bool AdminManager::removeUser(QString username) {
    bool tryRemoveUser = dbPtr->removeUser(username);

    if (!tryRemoveUser) {
        return tryRemoveUser;
    } else {
        refreshUserList();
    }
    return tryRemoveUser;
}

UserModel* AdminManager::getUserModel() {
    return &m_userModel;
}