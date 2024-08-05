//
// Created by XZ on 2024/8/2.
//
#include "event_manager.h"
#include <iostream>

EventManager::EventManager(Database& db) : db(db) {}

bool EventManager::addEvent(const std::string& title, const std::string& description, const std::string& eventDate, int createdBy) {
    std::string query = "INSERT INTO events (title, description, event_date, create_date, approved, created_by) VALUES ('"
                        + title + "', '" + description + "', '" + eventDate + "', CURDATE(), FALSE, " + std::to_string(createdBy) + ")";
    return db.executeQuery(query);
}

bool EventManager::editEvent(int eventId, const std::string& title, const std::string& description, const std::string& eventDate) {
    std::string query = "UPDATE events SET title='" + title + "', description='" + description + "', event_date='" + eventDate + "' WHERE id=" + std::to_string(eventId) + ";";
    return db.executeQuery(query);
}

bool EventManager::approveEvent(int eventId) {
    std::string query = "UPDATE events SET approved = TRUE WHERE id = " + std::to_string(eventId);
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


std::vector<std::vector<std::string>> EventManager::getEventsForMonth(int year, int month) {
    std::vector<std::vector<std::string>> events;
    std::string query = "SELECT id, title, event_date, description, approved FROM events "
                        "WHERE YEAR(event_date) = " + std::to_string(year) + " AND MONTH(event_date) = " + std::to_string(month);
    MYSQL_RES* res = db.fetchQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != NULL) {
            std::vector<std::string> event;
            for (int i = 0; i < mysql_num_fields(res); ++i) {
                event.push_back(row[i] ? row[i] : "NULL");
            }
            events.push_back(event);
        }
        mysql_free_result(res);
    } else {
        std::cerr << "Failed to query events table for the specified month and year" << std::endl;
    }
    return events;
}