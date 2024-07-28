DROP DATABASE IF EXISTS library_management;
CREATE DATABASE library_management;
USE library_management;

CREATE TABLE users (
                       id INT AUTO_INCREMENT PRIMARY KEY,
                       username VARCHAR(50) NOT NULL UNIQUE,
                       password VARCHAR(255) NOT NULL,
                       role ENUM('user', 'employee', 'admin') NOT NULL,
                       approved BOOLEAN DEFAULT FALSE
);

-- Add test data
INSERT INTO users (username, password, role, approved) VALUES ('admin', 'adminpass', 'admin', TRUE);
