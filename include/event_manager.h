//
// Created by XZ on 2024/8/2.
//

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "database.h"
#include <string>
#include <vector>

class EventManager {
public:
    EventManager(Database& db);

    bool addEvent(const std::string& title, const std::string& description, int createdBy);
    bool editEvent(int eventId, const std::string& title, const std::string& description);
    bool deleteEvent(int eventId);

    std::vector<std::vector<std::string>> getAllEvents();

    std::vector<std::vector<std::string>> getEventsByUser(int userId);

private:
    Database& db;
};

#endif //EVENT_MANAGER_H
