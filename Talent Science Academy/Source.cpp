////sre project driver program
// unique id for all academy students
// unique roll no for all students in a class

#include <iostream>
#include <fstream> //for file read write
#include <map>	   //for getting classes no according to the id
#include "Student.h"
#include "StudentNode.h"
#include "Date.h"
#include "Classes.h"
using namespace std;
map<int, int> getClassNo; // to get class no against the id
// set<StudentNode*> allStd;

// function prototype
void markAbsentees(long int date);	 // will mark remaining students as absent for the current date
void printSpecificClassAttendence(); // last day attendence of spcific class
void printallClassesAttendence();	 // print all classes last day attendence
void academyMenu();					 // menu for functions
void writeData();					 // existing the program
void addStudent(long int);			 // new admission in academy
void printInfo();
void markPresent(long int, long int);
long int getCurrDate();
void readFile();
void printStudentAttendenceRecord(long int, long int);

int main()
{
	readFile();
	long int date = getCurrDate();
	char choice = '0';
	do
	{
		academyMenu();
		cout << "Enter Choice. " << endl;
		cin >> choice;
		if (choice == '1')
			addStudent(date);
		else if (choice == '2')
			markAbsentees(date);
		else if (choice == '3')
		{
			int id;
			cout << "Enter the Id of the Student: ";
			cin >> id;
			markPresent(id, date);
		}
		else if (choice == '4')
		{
			markAbsentees(date);
			printallClassesAttendence();
		}
		else if (choice == '5')
		{
			markAbsentees(date);
			printSpecificClassAttendence();
		}
		else if (choice == '6')
			printInfo();
		else if (choice == '7')
		{
			int id;
			cout << "Enter the Id of the Student: ";
			cin >> id;
			printStudentAttendenceRecord(id, date);
		}
		else if (choice == '8')
		{
			writeData();
			break;
		}
		else
			cout << "Invalid choice!!! " << endl;
	} while (true);
	return 0;
}

// function defintion
void printInfo()
{
	// getClassNo of each id  and then display its info by finding that id in the class
	for (int i = 10000; i <= StudentNode::static_id; i++)
	{
		int classNo = getClassNo[i];
		auto it = classesArray[classNo].st.begin();
		auto it_end = classesArray[classNo].st.end();

		while (it != it_end)
		{ // iterate classArray[classNo].st->list
			if ((*it)->getId() == i)
			{
				(*it)->printInfo();
				break;
			}
			it++;
		}
	}
}
void printStudentAttendenceRecord(long int id, long int date)
{
	int classNo = getClassNo[id];
	auto it = classesArray[classNo].st.begin();
	auto it_end = classesArray[classNo].st.end();
	// bool stFound = false;
	while (it != it_end)
	{ // iterate classArray[classNo].st->list
		if ((*it)->getId() == id)
		{
			// stFound = true;
			(*it)->printAttendenceRecord();
			break; // to avoid comparing remaing ids in the class
		}
		it++;
	}
	// if(!stFound)cout<<""
}
void markPresent(long int id, long int date)
{
	int classNo = getClassNo[id];
	auto it = classesArray[classNo].st.begin();
	auto it_end = classesArray[classNo].st.end();

	while (it != it_end)
	{ // iterate classArray[classNo].st->list
		if ((*it)->getId() == id)
		{
			auto attendence_it = ((*it)->attendence.end());
			((*(attendence_it--)).getDate() == date) ? (*attendence_it).setPresent(true) : (*it)->addAttendence(date, true);
			// can be used instead of above 2 lines
			//((*((*it)->attendence.end()--)).getDate() == date) ? (*(*it)->attendence.end()).setPresent(true) : (*it)->addAttendence(date, true);

			break; // to avoid comparing remaing ids in the class
		}
		it++;
	}
}
long int getCurrDate()
{
	string dateSt = __DATE__;
	long int date = 0; // to be returned
	int day = 0,
		month = 0,
		year = 0;
	for (int i = 0; i < dateSt.length(); i++)
	{
		cout << __DATE__ << endl;
		string monthSt = "", daySt = "", yearSt = "";
		while (i < dateSt.length() && dateSt[i] != ' ')
		{
			monthSt += dateSt[i]; // to get month;
			i++;
		}
		while (dateSt[i] == ' ')
		{
			i++;
		}
		while (i < dateSt.length() && dateSt[i] != ' ')
		{
			daySt += dateSt[i]; // to get month;
			i++;
		}
		while (dateSt[i] == ' ')
		{
			i++;
		}
		while (i < dateSt.length() && dateSt[i] != ' ')
		{
			yearSt += dateSt[i]; // to get month;
			i++;
		}
		day = stoi(daySt);
		if (monthSt == "Jan")
			month = 1;
		else if (monthSt == "Feb")
			month = 2;
		else if (monthSt == "Mar")
			month = 3;
		else if (monthSt == "Apr")
			month = 4;
		else if (monthSt == "May")
			month = 5;
		else if (monthSt == "Jun")
			month = 6;
		else if (monthSt == "Jul")
			month = 7;
		else if (monthSt == "Aug")
			month = 8;
		else if (monthSt == "Sep")
			month = 9;
		else if (monthSt == "Oct")
			month = 10;
		else if (monthSt == "Nov")
			month = 11;
		else if (monthSt == "Dec")
			month = 12;
		year = stoi(yearSt);
	}
	date = day * 1000000;
	date += month * 10000;
	date += year;
	return date;
}
void printallClassesAttendence()
{
	for (int i = 1; i < noOfClasses; i++) // starting from class 1
		classesArray[i].printAttendenceforToday();
}
void markAbsentees(long int date)
{
	for (int i = 1; i < noOfClasses; i++) // starting from class 1
		classesArray[i].markAbsentees(date);
}
void printSpecificClassAttendence()
{
	int tempInt = 0;
	do
	{
		cout << "Enter class No: " << endl;
		cin >> tempInt;
		if (tempInt <= 0 && tempInt >= noOfClasses)
			cout << "Invalid Class No Entered... " << endl;
	} while (tempInt <= 0 && tempInt >= noOfClasses); // from 1 to 12
	classesArray[tempInt].printAttendenceforToday();
}
void academyMenu()
{
	cout << "			  >>>> Academy Management System <<<< " << endl;
	cout << " 1- Register New Student. " << endl;
	cout << " 2- Mark Absantees(all remaining). " << endl;
	cout << " 3- Mark Student as Present(By ID). " << endl;
	cout << " 4- Print Attendence Sheet of All classes. " << endl;
	cout << " 5- Print Attendence Sheet of a specific class. " << endl;
	cout << " 6- Print List of Registered Students. " << endl;
	cout << " 7- Print Attendence Record of specific student. " << endl;
	cout << " 8- Exit" << endl;
}
void writeData()
{
	ofstream out("data.txt");
	for (int i = 1; i < noOfClasses; i++)
	{ // starting from class 1
		auto st_iterator = classesArray[i].st.begin();
		auto st_it_end = classesArray[i].st.end();
		for (; st_iterator != st_it_end; st_iterator++)
		{
			out << (*st_iterator)->getClassNo() << "\t";
			out << (*st_iterator)->getName() << "\t";
			out << (*st_iterator)->getFatherName() << "\t";
			out << (*st_iterator)->getDateofJoin() << "\t";
			out << (*st_iterator)->getId() << "\t";
			auto attendence_it = (*st_iterator)->attendence.begin();
			auto attendence_it_end = (*st_iterator)->attendence.end();
			while (attendence_it != attendence_it_end)
			{
				((attendence_it)->getPresent() == 1) ? out << "P " : out << "A ";
				attendence_it++;
			}
			out << endl;
		}
	}
	out.close();
}
void addStudent(long int date)
{
	long int tempInt = 0;
	string tempStr;
	int classNo;
	do
	{
		cout << "Enter class No: " << endl;
		cin >> classNo;
		if (classNo <= 0 && classNo >= noOfClasses)
		{
			cout << "Invalid Class No Entered... " << endl;
		}
	} while (classNo <= 0 && classNo >= noOfClasses); // from 1 to 12
	Student* newStudent = new Student(classNo);
	classesArray[classNo].addStudent(newStudent);

	cout << "Enter the name : " << endl;
	cin >> tempStr;
	newStudent->setName(tempStr);
	cout << "Enter the father name : " << endl;
	cin >> tempStr;
	newStudent->setFatherName(tempStr);
	newStudent->addAttendence(date, true); // will be marked as present today
	newStudent->setDateOfJoin(date);	   // todays date will be the date of join
	cout << "Enter today's date: " << endl;
	cin >> tempInt;
	newStudent->setDateOfJoin(tempInt);
	newStudent->setRollNo(noOfStudentInClass[classNo]);
	noOfStudentInClass[classNo] = noOfStudentInClass[classNo] + 1; // increment count
	newStudent->setId(StudentNode::static_id);					   // new id everytime
	// allStd.insert(new StudentNode(newStudent));
	getClassNo[newStudent->getId()] = newStudent->getClassNo();
}
void readFile()
{
	ifstream in;	   // for input from the file
	string tempString; // for holding data from file temporarily
	long int tempInt;
	in.open("data.txt");
	while (!in.eof())
	{
		in >> tempInt; // class no
		if (in.eof())
			break; // if cursor is on start of next line
		Student* newStudent = new Student(tempInt);
		classesArray[tempInt].addStudent(newStudent); // pushing student to specific class
		in >> tempString;							  // name
		newStudent->setName(tempString);
		in >> tempString; // father name
		newStudent->setFatherName(tempString);
		in >> tempInt; // date Of Join
		newStudent->setDateOfJoin(tempInt);
		Date tempDate(tempInt);
		in >> tempInt; // id
		newStudent->setId(tempInt);
		StudentNode::static_id++; //	we shall have a count of how many students were in the list
		//	although order of ids in the file will be irregular but it will give exact count after fully reading the file
		getline(in, tempString);
		for (int i = 0; i < tempString.size(); i++)
		{
			if (tempString[i] == 'A')
			{
				newStudent->addAttendence(tempDate.getCurrDate(), false);
				newStudent->setLastAttendnceDate(tempDate.getCurrDate());
				++tempDate;
			}
			else if (tempString[i] == 'P')
			{
				newStudent->addAttendence(tempDate.getCurrDate(), true);
				newStudent->setLastAttendnceDate(tempDate.getCurrDate());
				++tempDate;
			}
		}
		getClassNo[newStudent->getId()] = newStudent->getClassNo();
		// allStd.insert(new StudentNode(newStudent));
	}
	in.close();
}

// to do
//  academy class
//	date class to be used instead of long int
//  use time if greater than 4pm auto mark absant