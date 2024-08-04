#include "Book.h"
//
// Created by Joey Perry on 8/3/2024.
//
Book::Book(std::string idStr, std::string title, std::string author, std::string isbn, std::string avalibleString) {
    id = std::stoi(idStr);
    this->title = title;
    this->author = author;
    if(avalibleString == "1"){
        avalible = true;
    } else {
        avalible = false;
    }
    genre = id % 10;
    if(genre == 0){
        genre++;
    }
    if(id % 2 == 0){
        type = 1;
    } else {
        type = 2;
    }
}