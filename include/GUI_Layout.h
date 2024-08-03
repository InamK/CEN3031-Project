#include <imgui.h>
#include <string>
#include <ctime>
#include "cmath"
#include <cstring>
#include "database.h"
#include "user_manager.h"
#include "event_manager.h"
#include "book_manager.h"
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
    unsigned int page = 2; //This is login screen
    std::string user; //Username kept track of.
    //Backend connectors
    Database db;
    UserManager users;
    BookManager books;
    EventManager events;

public:
    //Constructor
    GUI(Database& db, UserManager& users, EventManager& events, BookManager& books);
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