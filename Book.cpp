#include "Book.h"

Book::Book(string _name, int _author, int _genre, string _publishDate, int _pageCount) {
	name = _name;
	author = _author;
	genre = _genre;
	publishDate = _publishDate;
	pageCount = _pageCount;
}

void Book::bookDetails(unordered_map<int, string> authorKey, unordered_map<int, string> genreKey) {
	cout << "Book Title: " << name << endl;
	cout << "Author: " << authorKey[author] << endl;
	cout << "Genre: " << genreKey[genre] << endl;
	cout << "Date Published: " << publishDate << endl;
	cout << "Page Count: " << pageCount << endl;
	cout << endl;
}