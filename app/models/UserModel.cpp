#include "UserModel.hpp"

UserModel::UserModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int UserModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_users.count();
}

QVariant UserModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_users.count()) {
        return QVariant();
    }

    const UserData &user = m_users[index.row()];

    switch (role) {
        case FirstNameRole: return user.firstName;
        case LastNameRole:  return user.lastName;
        case RoleRole:      return user.role;
        case UsernameRole:  return user.username;
        default:            return QVariant();
    }
}

QHash<int, QByteArray> UserModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FirstNameRole] = "firstName";
    roles[LastNameRole]  = "lastName";
    roles[RoleRole]      = "role";
    roles[UsernameRole]  = "username";
    return roles;
}

void UserModel::setUsers(const QList<UserData> &users) {
    beginResetModel(); 

    m_users = users;
    
    endResetModel();   
}