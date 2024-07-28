//
// Created by star on 2024/7/14.
//

#include "user_manager.h"
#include <iostream>

UserManager::UserManager(Database& db) : db(db) {}

bool UserManager::createAccount(const std::string& username, const std::string& password, const std::string& role) {
    std::string query = "INSERT INTO users (username, password, role) VALUES ('" + username + "', '" + password + "', '" + role + "');";
    return db.executeQuery(query);
}

bool UserManager::login(const std::string& username, const std::string& password, std::string& role) {
    std::string query = "SELECT role FROM users WHERE username='" + username + "' AND password='" + password + "' AND approved=1;";
    MYSQL_RES* res = db.fetchQuery(query);

    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            role = row[0];
            mysql_free_result(res);
            return true;
        }
        mysql_free_result(res);
    }
    return false;
}