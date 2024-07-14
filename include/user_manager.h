//
// Created by star on 2024/7/14.
//

#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "database.h"
#include <string>

class UserManager {
public:
    UserManager(Database& db);

    bool createAccount(const std::string& username, const std::string& password, const std::string& role);
    bool login(const std::string& username, const std::string& password, std::string& role);

private:
    Database& db;
};

#endif //USER_MANAGER_H
