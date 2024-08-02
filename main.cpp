#include <stdlib.h>
#include <iostream>
#include <vector>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include "Reservation.h";
using namespace std;

const string server = "tcp://ec2-3-19-221-222.us-east-2.compute.amazonaws.com:3306";
const string username = "remote_user";
const string password = "PassCode.3725";

//All data in databse names BookData
// Tables:
    //books: (columns = int id, string bookName, string author, string genre, string publishData, int pageCount)
    //reservations: (columns = int id, int year, int month, int day, int userID)
    // 
//TESTS⌄⌄⌄⌄⌄⌄⌄⌄⌄⌄⌄⌄⌄⌄

void promptAddBook();
void promptAddReservation();
void printBooks();
void printReservations();

//TESTS^^^^^^^^^^^^^^^^^
//Clear tables
void clearData(string tableName); // tables: books, reservations

void connectToDataBase();
void addBook(string bookName, string author, string genre, string publishDate, int pageCount);
void removeBook(string name);
void displayByAuthor(string authorName);
void createReservation(int year, int month, int day, int time, string name);

vector<Reservation> getReservation(int year, int month, int day);


int main() {


    //clearData("reservations");
    printBooks();
    cout << endl << endl << "Reservations: " << endl;
    printReservations();
    promptAddBook();
    promptAddReservation();

    vector<Reservation> selectReservation = getReservation(2025, 2, 15);
    for (int i = 0; i < selectReservation.size(); i++) {
        selectReservation[i].print();
    }

    return EXIT_SUCCESS;
}

void promptAddBook() {
    int choice;
    cout << "Do you want to add a book?" << endl;
    cout << "Type 1 for YES, any other number for NO" << endl;
    cin >> choice;

    if (choice == 1) {
        string bookName;
        string author;
        string genre;
        string publishDate;
        int pageCount;

        cout << "Book Name: ";
        cin >> bookName;

        cout << "Author Name: ";
        cin >> author;

        cout << "Genre: ";
        cin >> genre;

        cout << "PublishDate: ";
        cin >> publishDate;

        cout << "Page Count: " << endl;
        cin >> pageCount;

        addBook(bookName, author, genre, publishDate, pageCount);
    }
}

void promptAddReservation() {
    int choice;
    cout << "Do you want to create a reservation?" << endl;
    cout << "Type 1 for YES, any other number for NO" << endl;
    cin >> choice;

    if (choice == 1) {
        int year;
        int month;
        int day;
        int time;
        string name;

        cout << "Year (4 digit): ";
        cin >> year;

        cout << "Month (2 digit): ";
        cin >> month;

        cout << "Day (2 digit): ";
        cin >> day;

        cout << "Time (Military time 0-24):";
        cin >> time;
        cout << "Your name: ";
        cin >> name;

        createReservation(year, month, day, time, name);
    }
}


void printBooks() {
    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        // Create a connection
        driver = get_driver_instance();
        con = driver->connect(server, username, password);

        // This statement connects to our database named "BookData"
        //The BookData database contains everything, it contains a table for the books, a table for users. emplyeess and admins and a table for reservations
        con->setSchema("BookData");

        // Create a statement
        stmt = con->createStatement();

        // Thus querry selects all the data from the table called "books" located inside the BookData database
        res = stmt->executeQuery("SELECT id, bookName, author, genre, publishDate, pageCount FROM books");

        // Print the column headers
        std::cout << "ID\tBook Name\t\tAuthor\t\tGenre\t\tPublish Date\tPage Count" << std::endl;
        std::cout << "---------------------------------------------------------------------------------" << std::endl;

        // Process and print the data in the table until we reach the end of the table
        while (res->next()) {
            int id = res->getInt("id");
            std::string bookName = res->getString("bookName");
            std::string author = res->getString("author");
            std::string genre = res->getString("genre");
            std::string publishDate = res->getString("publishDate");
            int pageCount = res->getInt("pageCount");

            // Print the data
            std::cout << id << "\t" << bookName << "\t\t" << author << "\t\t" << genre << "\t\t" << publishDate << "\t" << pageCount << std::endl;
        }


        // Clean up
        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        std::cerr << "# ERR: SQLException in " << __FILE__;
        std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "# ERR: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

void printReservations() {
    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        // Create a connection to our databse
        driver = get_driver_instance();
        con = driver->connect(server, username, password);

        // Connect to our databse
        con->setSchema("BookData");

        // Create a statement
        stmt = con->createStatement();

        // This querry selects the entire table named "reservations"
        res = stmt->executeQuery("SELECT id, year, month, day, time, name FROM reservations");

        // Print the column headers
        std::cout << "ID\tYear\t\tMonth\t\tDay\t\tTime\t\tName" << std::endl;
        std::cout << "---------------------------------------------------------------------" << std::endl;

        // Process and print the data in the table until we reach the end of the table
        while (res->next()) {
            int id = res->getInt("id");
            int year = res->getInt("year");
            int month = res->getInt("month");
            int day = res->getInt("day");
            int time = res->getInt("time");
            string name = res->getString("name");

            // Print the data
            std::cout << id << "\t" << year << "\t\t" << month << "\t\t" << day << "\t\t" << time << "\t\t" << name << std::endl;
        }


        // Clean up
        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        std::cerr << "# ERR: SQLException in " << __FILE__;
        std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "# ERR: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}


void clearData(string tableName) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;

    // Create a connection
    driver = get_driver_instance();
    con = driver->connect(server, username, password);

    // Connect to the MySQL database
    con->setSchema("BookData");

    // Create a statement object
    stmt = con->createStatement();

    // Execute the DELETE query
    stmt->execute("DELETE FROM " + tableName);

    // Clean up
    delete stmt;
    delete con;
}



void connectToDataBase() {

}


//this method is used to add book to the "books" table. Only used for testing now but we can limit this function to only admins and employees in the future
void addBook(string bookName, string author, string genre, string publishDate, int pageCount) {
    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::PreparedStatement* pstmt;

        // Create a connection
        driver = get_driver_instance();
        con = driver->connect(server, username, password);

        // Connect to the MySQL database
        con->setSchema("BookData");

        // Create a prepared statement
        pstmt = con->prepareStatement("INSERT INTO books (bookName, author, genre, publishDate, pageCount) VALUES (?, ?, ?, ?, ?)");

        // Set the values
        pstmt->setString(1, bookName);
        pstmt->setString(2, author);
        pstmt->setString(3, genre);
        pstmt->setString(4, publishDate);
        pstmt->setInt(5, pageCount);

        // Execute the prepared statement
        pstmt->executeUpdate();

        // Clean up
        delete pstmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        std::cerr << "# ERR: SQLException in " << __FILE__;
        std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "# ERR: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}
void removeBook(string name) {

}

void displayByAuthor(string authorName) {

}


//create a reservations for the given user for the given date
void createReservation(int year, int month, int day, int time, string name) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    // Create a connection
    driver = get_driver_instance();
    con = driver->connect(server, username, password);

    // Connects to our database
    con->setSchema("BookData");

    // Create a prepared statement
    pstmt = con->prepareStatement("INSERT INTO reservations (year, month, day, time, name) VALUES (?, ?, ?, ?,?)");

    // Setting the values to the ones given in the parameters
    pstmt->setInt(1, year);
    pstmt->setInt(2, month);
    pstmt->setInt(3, day);
    pstmt->setInt(4, time);
    pstmt->setString(5, name);

    // Execute the prepared statement
    pstmt->executeUpdate();

    // Clean up
    delete pstmt;
     delete con;

}

vector<Reservation> getReservation(int year, int month, int day) {
 
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        // Create a connection to our databse
        driver = get_driver_instance();
        con = driver->connect(server, username, password);

        // Connect to our databse
        con->setSchema("BookData");

        // Create a statement
        stmt = con->createStatement();

        // This querry selects the entire table named "reservations"
        string statement;
        if (day != 0) {
            res = stmt->executeQuery("SELECT * FROM reservations WHERE year = " + to_string(year) + " AND month = " + 
                to_string(month) + " AND day = " + to_string(day));
        }
        else {
            res = stmt->executeQuery("SELECT * FROM reservations WHERE year = " + to_string(year) + " AND month = " +
                to_string(month));
        }


        // Print the column headers
        std::cout << "ID\tYear\t\tMonth\t\tDay\t\tTime\t\tName" << std::endl;
        std::cout << "---------------------------------------------------------------------" << std::endl;

        // Process and print the data in the table until we reach the end of the table
        vector <Reservation> selectedReservations;
        while (res->next()) {
            int id = res->getInt("id");
            int year = res->getInt("year");
            int month = res->getInt("month");
            int day = res->getInt("day");
            int time = res->getInt("time");
            string name = res->getString("name");

            // Print the data
            selectedReservations.push_back(Reservation(year, month, day, time, name));
        }

        // Clean up
        delete res;
        delete stmt;
        delete con;
        return selectedReservations;
}