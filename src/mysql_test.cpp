//
// Created by XZ on 2024/7/14.
//
#include<bits/stdc++.h>
#include <mysql.h>

#include "database.h"
#include "user_manager.h"
#include "book_manager.h"
#include "event_manager.h"

using namespace std;


int main(void){

    Database db("root", "cen3031", "library_management");

    if (!db.connect()) {
        cerr << "Failed to connect to database" << endl;
        return EXIT_FAILURE;
    }

    UserManager userManager(db);

    cout << "======================================================================" << endl;
    cout << "Testing UserManager..." << endl;
    cout << "======================================================================" << endl;
    // Test: check validateUser
    if (!userManager.validateUser("admin", "adminpass")) {
        cerr << "Invalid username or password" << endl;
        return EXIT_FAILURE;
    } else {
        cout << "Valid username and password" << endl;
    }


    BookManager bookManager(db);

    cout << "======================================================================" << endl;
    cout << "Testing BookManager..." << endl;
    cout << "======================================================================" << endl;
    // Test: Get all books
    std::vector<std::vector<std::string>> books = bookManager.getAllBooks();
    if (!books.empty()) {
        std::cout << "Books in database:" << std::endl;
        for (const auto& book : books) {
            std::cout << "ID: " << book[0] << " Title: " << book[1] << " Author: " << book[2]
                      << " ISBN: " << book[3] << " Available: " << book[4] << std::endl;
        }
    } else {
        std::cerr << "No books found or query failed." << std::endl;
    }

    std::string keyword = "1984";
    std::vector<std::vector<std::string>> results = bookManager.searchBooks(keyword);

    if (!results.empty()) {
        std::cout << "Books matching '" << keyword << "':" << std::endl;
        for (const auto& book : results) {
            std::cout << "ID: " << book[0] << " Title: " << book[1] << " Author: " << book[2]
                      << " ISBN: " << book[3] << " Available: " << book[4] << std::endl;
        }
    } else {
        std::cout << "No books found matching the keyword '" << keyword << "'." << std::endl;
    }



    EventManager event_manager(db);

    cout << "======================================================================" << endl;
    cout << "Testing EventManager..." << endl;
    cout << "======================================================================" << endl;
    // Test: Get all events
    std::vector<std::vector<std::string>> events = event_manager.getAllEvents();
    if (!events.empty()) {
        std::cout << "Events in database:" << std::endl;
        for (const auto& event : events) {
            std::cout << "ID: " << event[0] << " Title: " << event[1] << " Description: " << event[2]
                      << " Created By: " << event[3] << std::endl;
        }
    } else {
        std::cerr << "No events found or query failed." << std::endl;
    }

    // Test: Get events by user
    std::vector<std::vector<std::string>> user_events = event_manager.getEventsByUser(1);
    if (!user_events.empty()) {
        std::cout << "Events created by user 1:" << std::endl;
        for (const auto& event : user_events) {
            std::cout << "ID: " << event[0] << " Title: " << event[1] << " Description: " << event[2]
                      << " Created By: " << event[3] << std::endl;
        }
    } else {
        std::cout << "No events found created by user 1." << std::endl;
    }

    return EXIT_SUCCESS;
}
