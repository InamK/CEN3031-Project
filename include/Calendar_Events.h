#include <string>
#include <vector>
#include <iostream>

class Event{
public:
    int id;
    std::string name;
    std::string description;
    int day, month, year;
    bool approved;
    Event(std::string id, std::string name, std::string description, std::string date, std::string state);
};
