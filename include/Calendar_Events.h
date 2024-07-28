#include <string>
#include <unordered_map>

class Event{
    std::string name;
    std::string description;
    int hour, minute;
    bool approved;
};

class Events{
    std::unordered_map<int, Event> event_list;
public:
    void AddEvent();
    void CheckDay();
};