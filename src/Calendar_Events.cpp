#include "Calendar_Events.h"

Event::Event(std::string name, std::string description, int hour, int minute, int month, int day) {
    this->name = name;
    this->description = description;
    this->hour = hour;
    this->minute = minute;
    this->month = month;
    this->day = day;
}


void Events::AddEvent() {}