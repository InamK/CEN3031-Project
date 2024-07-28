//
// Created by star on 2024/7/14.
//

// database.cpp
#include "database.h"
#include <iostream>

Database::Database(const std::string& user, const std::string& password, const std::string& database)
    : user(user), password(password), database(database) {
    conn = mysql_init(NULL);
}

Database::~Database() {
    if (conn) {
        mysql_close(conn);
    }
}

bool Database::connect() {
    if (!mysql_real_connect(conn, "localhost", user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0)) {
        std::cerr << "MySQL connection error: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

bool Database::executeQuery(const std::string& query) {
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

MYSQL_RES* Database::fetchQuery(const std::string& query) {
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
        return nullptr;
    }
    return mysql_store_result(conn);
}

