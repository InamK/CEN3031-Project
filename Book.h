#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;


class Book {
	string name;
	//I'm using int for author and genre because every author will be assigned an int key,this will make sorting easier and we will
	//easily know how many authors in total we have
	int author;
	int genre;
	string publishDate;
	int pageCount;

public:
	Book(string _name, int _author, int _genre, string _publishDate, int _pageCount);

	void bookDetails(unordered_map<int, string> authorKey, unordered_map<int, string> genreKey);
};