#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <fstream>
#include <unordered_map>
#include<iterator>
using namespace std;
#include "Book.h"

void readFile(unordered_map<string, Book>& data, unordered_map<int, string>& authorKey, unordered_map<int, string>& genreKey);
int setAuthorKey(unordered_map<int, string>& authorKey, string author);
int setGenreKey(unordered_map<int, string>& genreKey, string genre);
int main() {
	//ifstream file("BooksFile.csv");
	unordered_map<string, Book> data;

	unordered_map<int, string> authorKey;
	unordered_map<int, string> genreKey;

	readFile(data, authorKey, genreKey);
	auto iter = data.begin();
	while (iter != data.end()) {
		//cout << iter->first << endl;
		iter->second.bookDetails(authorKey, genreKey);
		iter++;
	}

	int choice;
	cout << "Here is a recommendation for displaying books: \n" <<
		"1. By Author\n" <<
		"2. By Genre\n" <<
		"3. By Book Length\n";
	cin >> choice;

	if (choice == 1) {
		cout << "You Chose Author" << endl;
	}
	else if (choice == 2) {
		cout << "You Chose Genre" << endl;
	}
	else if (choice == 3) {
		cout << "You Chose Book Length" << endl;
	}
	return 0;
}

void readFile(unordered_map<string, Book>& data, unordered_map<int, string>& authorKey, unordered_map<int, string>& genreKey) {
	ifstream file("BooksFile.csv");
	string line;

	getline(file, line);
	string bookName;
	string author;
	string genre;
	string publishDate;
	int count = 1;
	while (true) {
		while (count != 5 && getline(file, line, ',')) {
			//cout << line << endl;
			if (count == 1) {
				bookName = line;
				//cout << bookName << " ";
			}
			else if (count == 2) {
				author = line;
				//cout << author << " ";
			}
			else if (count == 3) {
				genre = line;
				//cout << genre << " ";
			}
			else if (count == 4) {
				publishDate = line;
				//cout << publishDate << " ";
			}
			count++;
		}
		if (count == 5 && getline(file, line)) {
			int pageCount = stoi(line);
			//cout << pageCount << endl;
			int aKey = setAuthorKey(authorKey, author);
			int gKey = setGenreKey(genreKey, genre);
			data.emplace(bookName, Book(bookName, aKey, gKey, publishDate, pageCount));
			count = 1;
			continue;
		}
		break;
	}
	file.close();
}

int setAuthorKey(unordered_map<int, string>& authorKey, string author) {
	auto itr = authorKey.begin();
	while (itr != authorKey.end()) {
		if (itr->second.compare(author) == 0) {
			//author is already in the key map
			return itr->first;;
		}
		itr++;
	}
	authorKey[authorKey.size()] = author;
	return authorKey.size() - 1;
}

int setGenreKey(unordered_map<int, string>& genreKey, string genre){
	auto itr = genreKey.begin();
	while (itr != genreKey.end()) {
		if (itr->second.compare(genre) == 0) {
			//author is already in the key map
			return itr->first;
		}
		itr++;
	}
	genreKey[genreKey.size()] = genre;
	return genreKey.size() - 1;
}