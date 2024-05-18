

#include <iostream>
#include "Family.h"
#include <fstream>
#include <cstring> 
#include <queue>
using namespace std;

void setFile(fstream& file) {

	Family family;
	for (int i = 0; i < 100; i++)
	{
		file.write((char*)&family, sizeof(Family));
	}
	//	file.close();
}


void add(fstream& file) {
	Family family;

	int id, count, phone;
	char name[20];
	bool courses[6], exist = false;


	cout << "enter family name" << endl;
	cin >> name;
	cout << "enter id of family" << endl;
	cin >> id;
	cout << "enter count of people" << endl;
	cin >> count;
	cout << "enter phone" << endl;
	cin >> phone;
	for (int i = 0; i < 6; i++) {
		courses[i] = false;
	}

	file.seekp((id - 1) * sizeof(Family));
	file.read((char*)&family, sizeof(Family));
	if (family.id == id)
		throw "ERROR: family is already in the file";

	if (id < 1 || id>100)
		throw "ERROR: invalid family number";
	Family newFamily(id, name, count, phone, courses);

	file.seekp((id - 1) * sizeof(Family));
	file.write((char*)&newFamily, sizeof(Family));
	//	file.close();

}
void del(fstream& file, int id) {
	if (id < 1 || id>100)
		throw "ERROR: invalid family number";

	Family family;
	file.seekp(((id - 1) * sizeof(Family)));
	file.write((char*)&family, sizeof(Family));
}


void update(fstream& file, int id, queue<Family>& waitingQueue) {
	Family family;
	if (id < 1 || id>100)
		throw "ERROR: invalid family number";

	file.seekp((id - 1) * sizeof(Family));
	file.read((char*)&family, sizeof(Family));
	if (family.id == 0)
		throw "ERROR:  family is not in the file";

	bool courses[6];
	for (int i = 0; i < 6; i++)
	{
		cout << "enter true/false or 0/1 if you in the course" << i + 1 << endl;
		cin >> courses[i];
	}


	bool flag = false;
	for (int i = 0; i < 6; i++)
	{
		Family f;
		int countCourse = 0;
		if (courses[i])
		{
			file.seekg(0, ios::beg);
			for (int j = 0; j < 100; j++)
			{
				file.read((char*)&f, sizeof(Family));
				if (f.id != 0)
				{
					if (f.courses[i])
						countCourse++;
				}
			}
			if (countCourse < 10)
			{
				family.courses[i] = true;
				courses[i] = false;
			}
			else
			{
				cout << "there is more 10 member in course " << endl;
				family.courses[i] = false;
				flag = true;
			}
		}
	}
	file.seekp((id - 1) * sizeof(Family));
	file.write((char*)&family, sizeof(Family));
	if (flag)
	{
		for (int i = 0; i < 6; i++)
		{
			family.courses[i] = courses[i];
		}
		waitingQueue.push(family);
	}
}

void waiting(fstream& file, queue<Family>& waitingQueue) {

	queue<Family> newWaitingQueue;
	Family f;
	bool flag = false;
	while (!waitingQueue.empty())
	{
		Family waitF = waitingQueue.front();
		waitingQueue.pop();

		file.seekp((waitF.id - 1) * sizeof(Family));
		Family family;
		file.read((char*)&family, sizeof(Family));

		for (int i = 0; i < 6; i++)
		{
			int countCourse = 0;
			if (waitF.courses[i])
			{
				file.seekg(0, ios::beg);
				for (int j = 0; j < 100; j++)
				{
					file.read((char*)&f, sizeof(Family));
					if (f.id != 0)
					{
						if (f.courses[i])
							countCourse++;
					}
				}
				if (countCourse < 10)
				{
					cout << "family " << family.nameFamily << endl;
					cout << "phone " << family.phone << endl;
					cout << "DO you want to enter the course" << i + 1 << "enter y/n" << endl;
					char c;
					cin >> c;
					if (c == 'Y' || c == 'y') {
						family.courses[i] == true;
						waitF.courses[i] = false;
					}
					else
					{
						family.courses[i] = false;
						flag = true;
					}
				}
				else
				{
					family.courses[i] = false;
					flag = true;
				}
			}
		}
		file.seekp((family.id - 1) * sizeof(Family));
		file.write((char*)&family, sizeof(Family));
		if (flag)
			newWaitingQueue.push(family);
	}
	waitingQueue = newWaitingQueue;
}

bool rishum(fstream& file, int id, int num) {
	if (num < 6 || num>0)
		throw "ERROR: Invalid class number";
	if (id < 1 || id>100)
		throw "ERROR: invalid family number";

	Family family;
	file.seekg((family.id - 1) * sizeof(Family));
	file.read((char*)&family, sizeof(Family));
	if (family.id == 0)
		throw "ERROR:  family is not in the file";

	return family.courses[num];
}

void print(fstream& file, int id) {

	if (id < 1 || id>100)
		throw "ERROR: invalid family number";

	Family family;
	file.seekg((family.id - 1) * sizeof(Family));
	file.read((char*)&family, sizeof(Family));
	if (family.id == 0)
		throw "ERROR:  family is not in the file";
	cout << family << endl;
}
void inClass(fstream& file, int num) {
	if (num < 6 || num>0)
		throw "ERROR: Invalid class number";

	Family f;
	file.seekg(0, ios::beg);
	for (int j = 0; j < 100; j++)
	{
		
		file.read((char*)&f, sizeof(Family));
		if (f.id != 0&&f.courses[num]!=false)
		{
			cout << "Family: " << f.nameFamily << endl;
		}
	}	
}

int main()
{
	queue<Family>q;
	fstream file;
	file.open("families.txt", ios::binary | ios::in, ios::out);
	if (!file)
	{
		cout << "ERROR: couldn't open file\n";
		return 0;
	}
	setFile(file);
	int choice;
	int snum;
	int cnum;
	cout << "Choices are:\n 0 to exit\n 1 to add family\n 2 to delete a family\n 3 to update rishum to classes\n 4 to update waiting to classes \n 5 to check rishum for a classes \n to print a family \n 7 to print all families that participate in a specific class\n  ";
	cout << "enter 0-7\n";
	cin >> choice;
	while (choice)
	{
		switch (choice) {
		case 1:
			try { add(file); }
			catch (const char* msg) { cout << msg; }
			break;
		case 2:
			cout << "enter number of family to delete\n";
			cin >> snum;
			try { del(file, snum); }
			catch (const char* msg) { cout << msg; }
			break;
		case 3:
			cout << "enter number of family to update\n";
			cin >> snum;
			try { update(file, snum, q); }
			catch (const char* msg) { cout << msg; }
			break;
		case 4:
			waiting(file, q);
			break;
		case 5: 
			cout << "enter number of family to check rishum\n";
			cin >> snum;
			cout<< "enter number of class to check rishum\n";
			cin >> cnum;
			try {
				cout << "The family is" << (rishum(file, snum, cnum) ? " " : "not ") << "takig the class";
			}
			catch (const char* msg) { cout << msg; }
			break;
		case 6:
			cout << "enter number of family to print\n";
			cin >> snum;
			try { print(file, snum); }
			catch (const char* msg) { cout << msg; }
			break;
		case 7:
			cout << "enter number of class to chack rishum:\n";
			cin >> cnum;
			try { inClass(file, cnum); }
			catch (const char* msg) { cout << msg; }
			break;
		default:
			cout << "ERROR: invalid choice\n";
		}
		cout << "enter 0-7\n";
		cin >> choice;
	}
	file.close();
	return 0;

}

