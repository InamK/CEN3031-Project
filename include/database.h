//
// Created by XZ on 2024/7/14.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>
#include <string>

class Database {
public:
    Database(const std::string& user, const std::string& password, const std::string& database);
    ~Database();

    bool connect();
    bool executeQuery(const std::string& query);
    MYSQL_RES* fetchQuery(const std::string& query);

private:
    MYSQL* conn;
    std::string user;
    std::string password;
    std::string database;
};

#endif // DATABASE_H

