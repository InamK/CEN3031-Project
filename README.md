# CEN3031-Project

## 1. How to run
1. You should copy the `mysql-connector-c-6.1.11-winx64\lib\libmysql.dll` and `mysql-connector-c-6.1.11-winx64\lib\libmysql.lib` in **cmake-build-debug** Folder.
2. You must have Directx 11 installed to run the GUI


## 2. DATABASE design

Now we update the mysql using tencent cloud service.

MySQL
>IP: gz-cynosdbmysql-grp-59hnehbp.sql.tencentcdb.com  
User: cen3031  
Password: cen3031_pass  
Port: 25121  
Database: library_management  
version: 5.7  
SSL: NO SSL  


### Tables

#### 1. `users` Table

| Field    | Type                             | Null | Key  | Default | Extra          |
|----------|----------------------------------|------|------|---------|----------------|
| id       | INT                              | NO   | PRI  | NULL    | AUTO_INCREMENT |
| username | VARCHAR(50)                      | NO   | UNI  | NULL    |                |
| password | VARCHAR(255)                     | NO   |      | NULL    |                |
| role     | ENUM('user', 'employee', 'admin')| NO   |      | NULL    |                |
| approved | BOOLEAN                          | YES  |      | FALSE   |                |

#### 2. `books` Table

| Field    | Type         | Null | Key  | Default | Extra          |
|----------|--------------|------|------|---------|----------------|
| id       | INT          | NO   | PRI  | NULL    | AUTO_INCREMENT |
| title    | VARCHAR(255) | NO   |      | NULL    |                |
| author   | VARCHAR(255) | NO   |      | NULL    |                |
| isbn     | VARCHAR(13)  | NO   | UNI  | NULL    |                |
| available| BOOLEAN      | YES  |      | TRUE    |                |

#### 3. `transactions` Table

| Field         | Type                              | Null | Key  | Default         | Extra          |
|---------------|-----------------------------------|------|------|-----------------|----------------|
| id            | INT                               | NO   | PRI  | NULL            | AUTO_INCREMENT |
| user_id       | INT                               | NO   | MUL  | NULL            |                |
| book_id       | INT                               | NO   | MUL  | NULL            |                |
| checkout_date | DATE                              | NO   |      | CURRENT_DATE()  |                |
| return_date   | DATE                              | YES  |      | NULL            |                |
| status        | ENUM('checked_out', 'returned')   | NO   |      | 'checked_out'   |                |
| FOREIGN KEY   | user_id REFERENCES users(id)      |      |      |                 |                |
| FOREIGN KEY   | book_id REFERENCES books(id)      |      |      |                 |                |

#### 4. `events` Table

| Field       | Type         | Null | Key  | Default | Extra          |
|-------------|--------------|------|------|---------|----------------|
| id          | INT          | NO   | PRI  | NULL    | AUTO_INCREMENT |
| title       | VARCHAR(255) | NO   |      | NULL    |                |
| description | TEXT         | YES  |      | NULL    |                |
| event_date  | DATE         | NO   |      | NULL    |                |
| create_date | DATE         | NO   |      | NULL    |                |
| approved    | BOOLEAN      | YES  |      | FALSE   |                |
| created_by  | INT          | NO   | MUL  | NULL    |                |
| FOREIGN KEY | created_by REFERENCES users(id) | | | |                |

## 3. Implemented Interface Methods

### `UserManager` Class

- **createAccount(username, password, role)**: Creates a new user account with the specified username, password, and role.

- **login(const std::string& username, const std::string& password, std::string& role)**: Authenticates the user based on the provided username and password, and assigns the user's role to the provided reference variable `role` if successful.

- **validateUser(username, password)**: Validates if the provided username and password are correct and the user is approved.

- **getUserRole(username)**: Retrieves the role of the user based on the provided username.

- **changeUserRole(const std::string& username, const std::string& newRole)**: Changes the role of an existing user.

- **getAllUsers()**: Returns a list of all users as a vector of pairs containing user IDs and usernames.

- **getUserId(const std::string& username)**: Retrieves the user ID based on the provided username.

- **approveUser(const std::string& username)**: Approves a user, allowing them to log in.

### `BookManager` Class

- **getAllBooks()**: Returns a list of all books in the library as a vector of vectors of strings. Each inner vector represents a book with its attributes like ID, title, author, ISBN, and availability.

- **addBook(title, author, isbn)**: Adds a new book to the library with the given title, author, and ISBN.

- **removeBook(bookId)**: Removes a book from the library based on its ID.

- **checkoutBook(userId, bookId)**: Records the checkout of a book by a user.

- **returnBook(transactionId)**: Records the return of a previously checked out book.

- **searchBooks(keyword)**: Searches for books in the library based on a keyword, returning a list of matching books.

- **getCheckedOutBooksByUser(int userId)**: Returns a list of books currently checked out by the specified user.

### `EventManager` Class

- **getAllEvents()**: Returns a list of all events in the library's event calendar as a vector of vectors of strings. This method is intended for use by admin and employee users.

- **getEventsByUser(int userId)**: Returns a list of events created by a specific user (typically a regular user) as a vector of vectors of strings. This method is intended for users to view their own events.

- **addEvent(title, description, eventDate, createdBy)**: Adds a new event to the library's event calendar.

- **approveEvent(int eventId)**: Approves an event, changing its status to approved.

- **getEventsForMonth(int year, int month)**: Returns a list of events scheduled for the specified month and year. Outputs a vector of strings with event details including ID, title, date, description, and approval status.

- **editEvent(eventId, title, description, eventDate)**: Edits an existing event's details.

- **deleteEvent(eventId)**: Deletes an event from the calendar.


## Some commands





