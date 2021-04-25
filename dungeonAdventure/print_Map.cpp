#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>

#include "dungeon.h"

using namespace std;

// print a map to show the floor number and the player's current position
// input: the row and column of the current position, floor number of the player
void print_Map(const int row, const int col, int floor) {
	cout << endl;
	if (floor == 1) {
		cout << "Dungeon LG2! Run!" << endl;
	}
	else if (floor == 2) {
		cout << "Dungeon LG1! Run!" << endl;
	}
	else if (floor == 3) {
		cout << "Dungeon G! Final floor! Run!" << endl;
	}

	cout << "  ____________\n3|";
	if (row == 3) {
		for (int i = 0; i < col; i++)
			cout << "   ";
		cout << " X ";
		for (int i = col + 1; i < 4; i++)
			cout << "   ";
		cout << '|' << endl << "2|";
	}
	else {
		cout << "            |\n2|";
	}
	if (row == 2) {
		for (int i = 0; i < col; i++)
			cout << "   ";
		cout << " X ";
		for (int i = col + 1; i < 4; i++)
			cout << "   ";
		cout << '|' << endl << "1|";
	}
	else {
		cout << "            |\n1|";
	}
	if (row == 1) {
		for (int i = 0; i < col; i++)
			cout << "   ";
		cout << " X ";
		for (int i = col + 1; i < 4; i++)
			cout << "   ";
		cout << '|' << endl << "0|";
	}
	else {
		cout << "            |\n0|";
	}
	if (row == 0) {
		for (int i = 0; i < col; i++)
			cout << "   ";
		cout << " X ";
		for (int i = col + 1; i < 4; i++)
			cout << "   ";
		cout << '|' << endl;
	}
	else {
		cout << "            |\n";
	}
	cout << " |____________|\n   0  1  2  3\n";
}
