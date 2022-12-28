#pragma once
#include<iostream>
#include<iomanip>
#include<list>
#include"Attendence.h"
#include"Date.h"
using namespace std;
int const noOfClasses = 13;
int noOfStudentInClass[noOfClasses] = { 0 };//store the no of students in each class
class Student {
	int rollNo;	//according to class
	int id;
	string fatherName;
	string name; //next id will be lastId+1
	int classNo;
	long int dateOfJoin;	//reference for starting date in attendence
	long int lastAttendenceDate;	//reference for last date of attendence
protected:
public:
	list<Attendence> attendence;
	//setters
	void setId(int id) { this->id = id; }
	void setRollNo(int rollNo) { this->rollNo = rollNo; }
	void setName(string name) { this->name = name; }
	void setFatherName(string fname) { this->fatherName = fname; }
	void setDateOfJoin(long int d) { dateOfJoin = d; }
	void setLastAttendnceDate(long int d) { lastAttendenceDate = d; }
	//getters
	long int getDateofJoin()const { return dateOfJoin; }
	long int getLastAttendenceDate()const { return lastAttendenceDate; }
	int getId() const { return id; }
	string getName() const { return name; }
	string getFatherName() const { return fatherName; }
	int getRollNo() { return rollNo; }
	int getClassNo() { return classNo; }
	//constructors
	Student(int);
	Student(string, string);
	void markAbsentees(long int date);
	void printInfo();
	void printAttendence();
	void addAttendence(long int, bool);
	void printLastAttendence();
	void printAttendenceRecord();
};
void Student::printAttendenceRecord() {
	auto att_it = attendence.begin();
	auto att_it_end = attendence.end();
	while (att_it != att_it_end) {
		Date::printDate((*att_it).getDate());
		cout << "\t";
		cout << ((*att_it).getPresent() ? "P\n" : "A\n");
		att_it++;
	}
}
void Student::markAbsentees(long int date) {
	if (date != lastAttendenceDate) {
		addAttendence(date, false);
	}
}
void Student::printInfo() {
	cout << setw(8) << left << id << "\t"
		<< setw(14) << left << getName() << "\t"
		<< setw(14) << left << getFatherName() << "\t"
		<< setw(5) << right << getClassNo() << endl;
}
//constructors
Student::Student(int classNo = -1) {
	this->classNo = classNo;
	if (classNo != -1)rollNo = ++noOfStudentInClass[classNo];
	fatherName = name = "";
	id = 0;
}
Student::Student(string name, string fatherName) {
	this->name = name; this->fatherName = fatherName;	classNo = 0;
	if (classNo != -1) {
		rollNo = noOfStudentInClass[classNo];
		noOfStudentInClass[classNo] = noOfStudentInClass[classNo] + 1;
	}
	else rollNo = 0;
	id = 0;
}
void Student::printAttendence() {
	cout << "	 Attendence sheet for Roll No " << rollNo << endl;
	if (attendence.empty()) {
		cout << " No Record Found. " << endl;
		return;
	}
	for (auto it = attendence.begin(); it != attendence.end(); it++) {
		cout << *it;
	}
}
void Student::addAttendence(long int date, bool present = false) {
	Attendence newRecord(date, present);
	attendence.push_back(newRecord);
	lastAttendenceDate = date;
}
void Student::printLastAttendence() {
	auto it = attendence.end();
	it--;
	cout << setw(10) << left << id <<
		setw(12) << left << rollNo <<
		setw(12) << left << name << " " <<
		setw(12) << left << fatherName << " ";
	Date::printDate((it)->getDate()); cout << " " <<
		setw(5) << right;
	(it)->getPresent() ? cout << 'P' : cout << 'A';
	cout << endl;
}

