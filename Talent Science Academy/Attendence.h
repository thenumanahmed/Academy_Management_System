#pragma once
#include<iostream>
using namespace std;
class Attendence {
	long int date;
	bool present;
public:
	Attendence() : date(0), present(0) {	}	//by default => absent
	Attendence(long int date, bool present = false) : date(date), present(present) {	}
	long int getDate() const { return date; }
	bool getPresent() const { return present; }
	void setDate(long int date) { this->date = date; }
	void setPresent(bool present) { this->present = present; }
	friend ostream& operator << (ostream& out, Attendence& a);
};
ostream& operator << (ostream& out, Attendence& a) {
	cout << a.date << " " << a.present << endl;
	return cout;
}


//present char instead of bool