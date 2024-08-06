#include "Calendar_Events.h"

Event::Event(std::string id, std::string name, std::string description, std::string date, std::string state) {
    this->id = std::stoi(id);
    this->name = name;
    this->description = description;
    if(state == "0"){
        approved = false;
    } else {
        approved = true;
    }
    std::string temp = date.substr(0,4);
    year = std::stoi(temp);
    temp = date.substr(5, 2);
    month = std::stoi(temp);
    temp = date.substr(8, 2);
    day = std::stoi(temp);
}
