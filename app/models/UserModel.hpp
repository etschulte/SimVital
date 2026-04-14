#pragma once

#include <QAbstractListModel>
#include <QList>
#include "../core/include/DatabaseManager.hpp" 

class UserModel : public QAbstractListModel {
    Q_OBJECT

private:
    QList<UserData> m_users;

public:
    enum UserRoles {
        FirstNameRole = Qt::UserRole + 1,
        LastNameRole,
        RoleRole,
        UsernameRole
    };

    explicit UserModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setUsers(const QList<UserData> &users);
};