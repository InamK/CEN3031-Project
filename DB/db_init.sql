DROP DATABASE IF EXISTS library_management;
CREATE DATABASE library_management;
USE library_management;

-- DROP TABLE IF EXISTS users;
CREATE TABLE users (
                       id INT AUTO_INCREMENT PRIMARY KEY,
                       username VARCHAR(50) NOT NULL UNIQUE,
                       password VARCHAR(255) NOT NULL,
                       role ENUM('user', 'employee', 'admin') NOT NULL,
                       approved BOOLEAN DEFAULT FALSE
);

-- DROP TABLE IF EXISTS books;
CREATE TABLE books (
                       id INT AUTO_INCREMENT PRIMARY KEY,
                       title VARCHAR(255) NOT NULL,
                       author VARCHAR(255) NOT NULL,
                       isbn VARCHAR(13) NOT NULL UNIQUE,
                       available BOOLEAN DEFAULT TRUE
);

-- DROP TABLE IF EXISTS transactions;
CREATE TABLE transactions (
                              id INT AUTO_INCREMENT PRIMARY KEY,
                              user_id INT NOT NULL,
                              book_id INT NOT NULL,
                              checkout_date DATE NOT NULL,
                              return_date DATE,
                              status ENUM('checked_out', 'returned') NOT NULL DEFAULT 'checked_out',
                              FOREIGN KEY (user_id) REFERENCES users(id),
                              FOREIGN KEY (book_id) REFERENCES books(id)
);

-- DROP TABLE IF EXISTS events;
CREATE TABLE events (
                        id INT AUTO_INCREMENT PRIMARY KEY,
                        title VARCHAR(255) NOT NULL,
                        description TEXT,
                        event_date DATE NOT NULL,
                        create_date DATE NOT NULL,
                        approved BOOLEAN DEFAULT FALSE,
                        created_by INT NOT NULL,
                        FOREIGN KEY (created_by) REFERENCES users(id)
);

-- Add test data
INSERT INTO users (username, password, role, approved) VALUES ('johndoe', 'password123', 'user', TRUE);
INSERT INTO users (username, password, role, approved) VALUES ('janedoe', 'password456', 'employee', TRUE);
INSERT INTO users (username, password, role, approved) VALUES ('bobsmith', 'password789', 'user', TRUE);
INSERT INTO users (username, password, role, approved) VALUES ('alicesmith', 'passwordabc', 'employee', TRUE);
INSERT INTO users (username, password, role, approved) VALUES ('charliebrown', 'passworddef', 'user', FALSE);  -- approved = False user
INSERT INTO users (username, password, role, approved) VALUES ('admin', 'adminpass', 'admin', TRUE); -- admin user

-- books
INSERT INTO books (title, author, isbn, available) VALUES ('The Great Gatsby', 'F. Scott Fitzgerald', '9780743273565', TRUE);
INSERT INTO books (title, author, isbn, available) VALUES ('To Kill a Mockingbird', 'Harper Lee', '9780061120084', FALSE);
INSERT INTO books (title, author, isbn, available) VALUES ('1984', 'George Orwell', '9780451524935', FALSE);
INSERT INTO books (title, author, isbn, available) VALUES ('Pride and Prejudice', 'Jane Austen', '9780141040349', FALSE);
INSERT INTO books (title, author, isbn, available) VALUES ('The Catcher in the Rye', 'J.D. Salinger', '9780316769488', TRUE);

-- transactions
INSERT INTO transactions (user_id, book_id, checkout_date, return_date, status) VALUES (1, 1, '2024-01-15', '2024-01-22', 'returned');
INSERT INTO transactions (user_id, book_id, checkout_date, return_date, status) VALUES (2, 2, '2024-02-05', NULL, 'checked_out'); -- cheacked out, so this book is not available
INSERT INTO transactions (user_id, book_id, checkout_date, return_date, status) VALUES (3, 3, '2024-03-10', NULL, 'checked_out');
INSERT INTO transactions (user_id, book_id, checkout_date, return_date, status) VALUES (1, 4, '2024-03-20', NULL, 'checked_out');
INSERT INTO transactions (user_id, book_id, checkout_date, return_date, status) VALUES (4, 5, '2024-04-01', '2024-04-08', 'returned');

-- events
INSERT INTO events (title, description, event_date, create_date, approved, created_by) VALUES ('Book Club Meeting', 'Discussing the book of the month: 1984 by George Orwell.', '2024-04-15', '2024-03-01', TRUE, 2);
INSERT INTO events (title, description, event_date, create_date, approved, created_by) VALUES ('Author Visit: Harper Lee', 'Join us for a special visit and Q&A session with Harper Lee.', '2024-05-10', '2024-03-15', FALSE, 3);
INSERT INTO events (title, description, event_date, create_date, approved, created_by) VALUES ('Summer Reading Kickoff', 'Kick off the summer reading program with activities and prizes.', '2024-06-01', '2024-04-20', TRUE, 1);
INSERT INTO events (title, description, event_date, create_date, approved, created_by) VALUES ('Children Storytime', 'A fun storytime event for kids aged 3-7.', '2024-06-20', CURRENT_DATE, FALSE, 4);

