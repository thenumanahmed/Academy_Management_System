#pragma once			
#include<iostream>
#include<string>
using namespace std;
class Date {
	int month;
	int year;
	int day;
	long int date;
	static int noOfDaysInMonth[13];
public:
	int getMonth();
	int getDay();
	int getYear();
	long int getCurrDate();
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	void setDate(long int);
	Date(long int);
	Date(int, int, int);
	void updateDate(int, int, int);
	Date& operator++();
	Date& operator--();
	bool operator==(Date&);
	friend ostream& operator<<(ostream& out, Date& d);
	bool checkInput(string);
	int validate(string);
	static void printDate(long int);
};
// each index of array will tell the no of days in each month
int Date::noOfDaysInMonth[13] = { -1,31,28,31,30,31,
			30,31,31,30,31,30,31 };

//function definitions
Date::Date(long int date = 0) : day(0), month(0), year(0), date(date) {
	if (date == 0)return;
	year = date % 10000;
	date /= 10000;	//will have day and month
	month = date % 100;
	date /= 100;
	day = date;
	updateDate(day, month, year);
}
Date::Date(int day, int month, int year) {
	updateDate(day, month, year);
}
void Date::updateDate(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
	string temp = "";
	if (day < 10)
		temp += "0" + to_string(day);
	else temp += to_string(day);
	if (month < 10)
		temp += "0" + to_string(month);
	else temp += to_string(month);
	temp += to_string(year);
	if (validate(temp))
		date = stoi(temp);
	else date = 0;
}
Date& Date::operator++() {
	if (noOfDaysInMonth[month] == day) {
		day = 1;
		if (month == 12) {
			month = 1;
			year++;
		}
		else
			month++;
	}
	else day++;
	updateDate(day, month, year);
	return *this;
}
Date& Date::operator--() {
	if (day == 1) {
		if (month == 1) {
			month = 12;
			year--;
		}
		else
			month--;
		day = noOfDaysInMonth[month];
	}
	else day--;
	updateDate(day, month, year);
	return *this;
}
int Date::getMonth() { return month; }
int Date::getDay() { return day; }
int Date::getYear() { return year; }
long int Date::getCurrDate() { return date; }
void Date::setDay(int d) { day = d; updateDate(day, month, year); }
void Date::setMonth(int m) { month = m; updateDate(day, month, year); }
void Date::setYear(int y) { year = y; updateDate(day, month, year); }
void Date::setDate(long int d) { date = d; updateDate(day, month, year); }
ostream& operator<<(ostream& out, Date& d) {
	(d.day < 10) ? cout << "0" << d.day : cout << d.day;
	cout << "/";
	(d.month < 10) ? cout << "0" << d.month : cout << d.month;
	cout << "/" << d.year;
	return out;
}
bool Date::operator==(Date& obj) {
	return (obj.day == day && obj.month == month && obj.year == year);
}
void Date::printDate(long int n) {
	if (n == 0)return;
	int year, day, month;
	year = n % 10000;
	n /= 10000;	//will have day and month
	month = n % 100;
	n /= 100;
	day = n;
	cout << day << "/" << month << "/" << year;
}
bool Date::checkInput(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}
int Date::validate(string str)
{
	if (checkInput(str))
		return 100;
	else
		return 10;
}
