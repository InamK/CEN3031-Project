#include <string>

class Checkout{
public:
    int trans_id;
    int book_id;
    std::string title;
    std::string author;
    Checkout(std::string tid, std::string bid, std::string title, std::string author);
};