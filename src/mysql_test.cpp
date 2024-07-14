//
// Created by star on 2024/7/14.
//
#include<bits/stdc++.h>
#include <mysql.h>

#include "database.h"
#include "user_manager.h"
using namespace std;

int main(void){

    Database db("root", "cen3031", "library_management");

    if (!db.connect()) {
        cerr << "Failed to connect to database" << endl;
        return EXIT_FAILURE;
    }

    UserManager userManager(db);

    // EXAMPLE QUERY: ALL USERS
    MYSQL_RES* res = db.fetchQuery("SELECT * FROM users");
    if (!res) {
        cerr << "SELECT error" << endl;
        return EXIT_FAILURE;
    }

    MYSQL_ROW row;
    cout << "Users in database:" << endl;
    while ((row = mysql_fetch_row(res)) != NULL) {
        cout << "ID: " << row[0] << " Username: " << row[1] << " Role: " << row[3] << " Approved: " << row[4] << endl;
    }

    mysql_free_result(res);

    return EXIT_SUCCESS;
}
