//
// Created by XZ on 2024/8/2.
//
#include "event_manager.h"
#include <iostream>

EventManager::EventManager(Database& db) : db(db) {}

bool EventManager::addEvent(const std::string& title, const std::string& description, int createdBy) {
    std::string query = "INSERT INTO events (title, description, event_date, created_by) VALUES ('" + title + "', '" + description + "', CURDATE(), " + std::to_string(createdBy) + ");";
    return db.executeQuery(query);
}

bool EventManager::editEvent(int eventId, const std::string& title, const std::string& description) {
    std::string query = "UPDATE events SET title='" + title + "', description='" + description + "' WHERE id=" + std::to_string(eventId) + ";";
    return db.executeQuery(query);
}

bool EventManager::deleteEvent(int eventId) {
    std::string query = "DELETE FROM events WHERE id=" + std::to_string(eventId) + ";";
    return db.executeQuery(query);
}

// This function is for admin, employee, they can see all the events
std::vector<std::vector<std::string>> EventManager::getAllEvents() {
    std::vector<std::vector<std::string>> events;
    MYSQL_RES* res = db.fetchQuery("SELECT * FROM events;");
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            std::vector<std::string> event;
            for (int i = 0; i < mysql_num_fields(res); ++i) {
                event.push_back(row[i] ? row[i] : "NULL");
            }
            events.push_back(event);
        }
        mysql_free_result(res);
    } else {
        std::cerr << "Failed to query events table" << std::endl;
    }
    return events;
}

// This function is for user, user just can see their own events
std::vector<std::vector<std::string>> EventManager::getEventsByUser(int userId) {
    std::vector<std::vector<std::string>> events;
    MYSQL_RES* res = db.fetchQuery("SELECT * FROM events WHERE created_by=" + std::to_string(userId) + ";");
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            std::vector<std::string> event;
            for (int i = 0; i < mysql_num_fields(res); ++i) {
                event.push_back(row[i] ? row[i] : "NULL");
            }
            events.push_back(event);
        }
        mysql_free_result(res);
    } else {
        std::cerr << "Failed to query events table" << std::endl;
    }
    return events;
}
