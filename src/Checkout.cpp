#include "Checkout.h"

Checkout::Checkout(std::string tid, std::string bid, std::string title, std::string author){
    this->title = title;
    this->author = author;
    trans_id = std::stoi(tid);
    book_id = std::stoi(bid);
}