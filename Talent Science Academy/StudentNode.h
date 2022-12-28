#pragma once
#include"Student.h"
class StudentNode {
	int id;
	Student* st;
public:
	static int static_id;
	StudentNode(Student* st, int id = 0) : st(st), id(id) {
		if (id != 0)this->id = static_id++;//if id is not passed it will be updated by static member 
	}
	int getId() { return id; }
	Student* getStudent() { return st; }
	void setId(int id) { this->id = id; }
	void setStudent(Student* st) { this->st = st; }
	bool operator>(StudentNode n) { return (id > n.id); }
	bool operator>=(StudentNode n) { return (id >= n.id); }
	bool operator<=(StudentNode n) { return (id <= n.id); }
	bool operator<(StudentNode n) { return (id < n.id); }
	bool operator==(StudentNode n) { return (id == n.id); }
	bool operator!=(StudentNode n) { return (id != n.id); }
	/*void printInfo() {
		cout << setw(8) << left << id << "\t"
			<< setw(14) << left << st->getName() << "\t"
			<< setw(14) << left << st->getFatherName() << "\t"
			<< setw(5) << right << st->getClassNo() << endl;
	}*/
	~StudentNode() {
		delete st;
	}
};
int StudentNode::static_id = 10000;