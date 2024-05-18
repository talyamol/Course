#include "Family.h"
#include <iostream>
using namespace std;

Family::Family() {
	id = 0;
	char nameFamily1[20] = {0};
	strcpy_s(nameFamily, 20, nameFamily1);
	countInFamily = 0;
	phone = 0;
	this->courses[6] = { false};

}
Family::Family(int id, const char* name, int count, int phone, bool* course) {
	this->id= id;
	strcpy_s(this->nameFamily, strlen(name) + 1, name);
	countInFamily = count;
	this->phone = phone;
	for (int i = 0; i < 6; i++)
	{
		courses[i] = course[i];
	}
}
ostream& operator<<(ostream& os, Family& f) {
	os << "Id: " << f.id << endl<<
		" Name: " << f.nameFamily << endl<<
		" Count in family: " << f.countInFamily 
		<< " Phone: " << f.phone << endl;
	for (int i = 0; i < 6; i++)
	{
		if (f.courses[i])
			os << "course " << i + 1 << " Y"<<endl;
		else
			os << "course " << i + 1 << " N" << endl;

	}
	return os;
}
