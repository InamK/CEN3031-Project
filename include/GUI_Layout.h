#include <imgui.h>
#include <string>
#include <vector>
#include <ctime>
#include "cmath"
#include <cstring>
#include <unordered_map>
#include "database.h"
#include "user_manager.h"
#include "event_manager.h"
#include "book_manager.h"
#include "Book.h"
#include "Calendar_Events.h"
#include "Checkout.h"
#include <iostream>

//Class contains functionality for UI
class GUI{
    std::string id = "debug_user";
    //bools for permissions
    bool login = false;
    bool employee = false;
    bool admin = false;
    //Day select for calendar actions
    int month;
    int day = 1;
    int year;
    //Page specifier
    unsigned int page = 2; //This is login screen
    std::string user; //Username kept track of.
    //Backend connectors
    UserManager users;
    BookManager books;
    EventManager events;

public:
    //Constructor
    GUI(UserManager& users, EventManager& events, BookManager& books);
    //primary function
    void RunGUI();
private:
    //Functions for individual pages
    void calendar();
    void Date();
    void Home();
    void Books();
    void Events();
    void Event_Create();
    void CreateResource();
    void Members();
    void Confirmations();
};