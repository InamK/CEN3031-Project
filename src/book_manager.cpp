//
// Created by XZ on 2024/8/2.
//

#include "book_manager.h"
#include <iostream>
#include <vector>

BookManager::BookManager(Database& db) : db(db) {}

bool BookManager::addBook(const std::string& title, const std::string& author, const std::string& isbn) {
    std::string query = "INSERT INTO books (title, author, isbn) VALUES ('" + title + "', '" + author + "', '" + isbn + "');";
    return db.executeQuery(query);
}

bool BookManager::removeBook(int bookId) {
    std::string query = "DELETE FROM books WHERE id=" + std::to_string(bookId) + ";";
    return db.executeQuery(query);
}

bool BookManager::checkoutBook(int userId, int bookId) {
    std::string query0 = "UPDATE books SET available = 0 WHERE id = '" + std::to_string(bookId) + "';";
    db.executeQuery(query0);
    std::string query = "INSERT INTO transactions (user_id, book_id, checkout_date) VALUES (" + std::to_string(userId) + ", " + std::to_string(bookId) + ", CURDATE());";
    return db.executeQuery(query);
}

bool BookManager::returnBook(int transactionId, int bookId) {
    std::string query0 = "UPDATE books SET available = 1 WHERE id = '" + std::to_string(bookId) + "';";
    db.executeQuery(query0);
    std::string query = "UPDATE transactions SET return_date=CURDATE(), status='returned' WHERE id=" + std::to_string(transactionId) + ";";
    return db.executeQuery(query);
}

std::vector<std::vector<std::string>> BookManager::searchBooks(const std::string& keyword) {
    std::vector<std::vector<std::string>> books;
    std::string query = "SELECT * FROM books WHERE title LIKE '%" + keyword + "%' OR author LIKE '%" + keyword + "%';";
    MYSQL_RES* res = db.fetchQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            std::vector<std::string> book;
            for (int i = 0; i < mysql_num_fields(res); ++i) {
                book.push_back(row[i] ? row[i] : "NULL");
            }
            books.push_back(book);
        }
        mysql_free_result(res);
    }
    return books;
}

std::vector<std::vector<std::string>> BookManager::getAllBooks() {
    std::vector<std::vector<std::string>> books;
    MYSQL_RES* res = db.fetchQuery("SELECT * FROM books");
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != NULL) {
            std::vector<std::string> book;
            for (int i = 0; i < mysql_num_fields(res); ++i) {
                book.push_back(row[i] ? row[i] : "NULL");
            }
            books.push_back(book);
        }
        mysql_free_result(res);
    } else {
        std::cerr << "Failed to query books table" << std::endl;
    }
    return books;
}

std::vector<std::vector<std::string>> BookManager::getCheckedOutBooksByUser(int userId) {
    std::vector<std::vector<std::string>> books;

    // Query to join transactions with books to get book details
    std::string query = "SELECT transactions.id, books.id, books.title, books.author, books.isbn "
                        "FROM transactions "
                        "JOIN books ON transactions.book_id = books.id "
                        "WHERE transactions.user_id = " + std::to_string(userId) + " AND transactions.status = 'checked_out'";

    MYSQL_RES* res = db.fetchQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != NULL) {
            std::vector<std::string> book;
            for (int i = 0; i < mysql_num_fields(res); ++i) {
                book.push_back(row[i] ? row[i] : "NULL");
            }
            books.push_back(book);
        }
        mysql_free_result(res);
    } else {
        std::cerr << "Failed to query transactions and books tables" << std::endl;
    }
    return books;
}
