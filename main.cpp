#include <iostream>
#include <Windows.h>
#include "life.h"
using namespace std;

int tryCin(istream&);

int main() {
	int generations = 500, width = 60, height = 20, choice, speed = 10;
	char style = 'O';

	cout << "Please select an option:\n"
		 << "(1) Default Settings\n"
		 << "(2) Custom Settings (Best with custom pattern.txt)\n\n"
		 << "Choice: ";
	cin >> choice;
	if (tryCin(cin) != 0)
		choice = 1;

	//options
	system("cls");
	if (choice == 1) {
		cout << "Ok.";
	} else if (choice == 2) {
		cout << "Enter width (default is 60): ";
		cin >> width;
		tryCin(cin);
		cout << "Enter height (default is 20): ";
		cin >> height;
		cout << "Choose a character (for style): ";
		cin >> style;
		cout << "\nEnter how many generations: ";
		cin >> generations;
		cout << "\nEnter speed (in milliseconds): ";
		cin >> speed;
	} else {
		cerr << "Please try again later!\n";
		system("pause");
		return 6;
	}
	
	//position:
	system("cls");
	cout << "Please select a pattern:\n"
		<< "(1) Gosper Gun\n(2) Glider\n(3) Pulsar\n(4) Ten Line\n\n"
		<< "Choice: ";
	cin >> choice;

	//create Life object
	Life myLife(width, height, style, choice);

	//Main Program
	system("cls");
	for (int i=0; i<generations; i++) {
		system("cls");
		cout << myLife;
		Sleep(speed);
	}
	
	cout << "\n\n\n";
	system("pause");
	return 0;
}

int tryCin(istream& in) {
	if (in.fail()) {
		in.clear();
		in.ignore(256, '\n');
		return 1;
	} else {
		return 0;
	}
}