//
// Created by XZ on 2024/7/14.
//
#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "database.h"
#include <string>
#include <vector>

class UserManager {
public:
    UserManager(Database& db);

    bool createAccount(const std::string& username, const std::string& password, const std::string& role);
    bool login(const std::string& username, const std::string& password, std::string& role);
    bool validateUser(const std::string& username, const std::string& password);

    std::string getUserRole(const std::string& username);

    bool changeUserRole(const std::string& username, const std::string& newRole);
    std::vector<std::pair<int, std::string>> getAllUsers();
    int getUserId(const std::string& username);
    bool approveUser(const std::string& username);
private:
    Database& db;
};

#endif //USER_MANAGER_H
