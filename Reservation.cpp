
#include "Reservation.h"
Reservation::Reservation(int _year, int _month, int _day, int _time, string _name) {
	year = _year;
	month = _month;
	day = _day;
	time = _time;
	name = _name;
}

void Reservation::print() {
	cout << year << "\t" << month << "\t" << day << "\t" << time << "\t" << name << endl;
}
