#include <string>
#include <vector>

class Event{
    std::string name;
    std::string description;
    int hour, minute, day, month;
    bool approved = false;
    std::vector<std::string> RSVP_List;
    Event(std::string name, std::string description, int hour, int minute, int month, int day);
};
