#include <string>
//
// Created by Joey Perry on 8/3/2024.
//
class Book{
public:
    int id;
    std::string title;
    std::string author;
    bool avalible;
    int type;
    int genre;
    Book(std::string idStr, std::string title, std::string author, std::string isbn, std::string avalibleString);
};