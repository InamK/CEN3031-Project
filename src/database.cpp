//
// Created by XZ on 2024/7/14.
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
    if (!mysql_real_connect(conn, "gz-cynosdbmysql-grp-59hnehbp.sql.tencentcdb.com", user.c_str(), password.c_str(), database.c_str(), 25121, NULL, 0)) {
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
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result && mysql_field_count(conn) > 0) {
        std::cerr << "MySQL store result error: " << mysql_error(conn) << std::endl;
    }
    return result;
}