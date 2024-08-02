#pragma once
#include <iostream>
#include <string>

using namespace std;

class Reservation {
private:
	int year;
	int month;
	int day;
	int time;
	string name;

public:
	Reservation(int _year, int _month, int _day, int _time, string _name);
	
	void print();


};