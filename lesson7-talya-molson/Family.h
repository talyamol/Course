#pragma once
#include <string>
#include <fstream>
using namespace std;
class Family
{
public:
	int id;
	char nameFamily[20];
	int countInFamily;
	int phone;
	bool courses[6];

	Family();
	Family(int id, const char* name, int count, int phone,  bool* course);
	
	
	friend ostream& operator<<(ostream& os, Family& f);
	


};

