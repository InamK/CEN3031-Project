//
// Created by XZ on 2024/8/2.
//

#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H

#include "database.h"
#include <string>
#include <vector>

class BookManager {
public:
    BookManager(Database& db);

    bool addBook(const std::string& title, const std::string& author, const std::string& isbn);
    bool removeBook(int bookId);
    bool checkoutBook(int userId, int bookId);
    bool returnBook(int transactionId, int bookId);
    std::vector<std::vector<std::string>> searchBooks(const std::string& keyword);
    std::vector<std::vector<std::string>> getAllBooks();
    std::vector<std::vector<std::string>> getCheckedOutBooksByUser(int userId);

private:
    Database& db;
};

#endif //BOOK_MANAGER_H
