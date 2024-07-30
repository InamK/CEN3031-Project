#include <string>
#include <unordered_map>

class Event{
    std::string name;
    std::string description;
    int hour, minute, day, month;
    bool approved = false;
    Event(std::string name, std::string description, int hour, int minute, int month, int day);
};

class Events{
    std::unordered_map<int, Event> event_list;
public:
    void AddEvent();
    void CheckDay();
};