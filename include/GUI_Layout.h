#include <imgui.h>
#include <string>
#include <ctime>
#include "cmath"
#include <cstring>
//Class contains functionality for UI
class GUI{
    //bools for permissions
    bool login = false;
    bool employee = false;
    bool admin = false;
    //Day select for calendar actions
    int month;
    int day = 1;
    int year;
    //Page specifier
    unsigned int page = 0;
public:
    //Constructor
    GUI();
    //primary function
    void RunGUI();
private:
    //Functions for individual pages
    void calendar();
    void Date();
};