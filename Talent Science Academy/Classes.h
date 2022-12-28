#pragma once
#include"Student.h"
#include"Attendence.h"
#include<list>
class Classes {
	int classNo;	//to store which class's data is being stored

public:
	list<Student*> st;	//aggregation of students in the class
	Classes(int c = 0) : classNo(c) { }
	void addStudent(Student* s) {
		st.push_back(s);
	}
	void printAttendenceforToday() {
		cout << endl;
		if (st.empty()) {
			cout << "No Student Registered in class " << classNo << "." << endl;
			return;
		}
		cout << "Attendence for Class " << classNo << "  Dated: " << (*st.begin())->getLastAttendenceDate() << endl;
		cout << setw(10) << left << "Id"
			<< setw(12) << left << "Roll No" <<
			setw(12) << left << "Name" << " " <<
			setw(14) << left << "F. Name  " <<
			setw(12) << left << "Date   " << " " <<
			setw(5) << left << "Attendence " << endl;
		for (auto it = st.begin(); it != st.end(); it++) {
			(*it)->printLastAttendence();
			//cout << ((*it)->attendence.end()--)->getPresent() << endl;
		}
		cout << endl;
	}
	void markAbsentees(long int date) {
		if (st.empty())
			return;
		for (auto it = st.begin(); it != st.end(); it++) {
			(*it)->markAbsentees(date);
		}
	}

};



Classes classesArray[noOfClasses] = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };		//size is 13 as will require indices till 12
