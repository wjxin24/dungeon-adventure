#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>

#include "dungeon.h"
using namespace std;

extern Position pos;
extern vector <Position> path;
extern Player player;

// save the player's information into a txt file named after the player's name,
// and then exit the program
// input: a Player struct of the current player's information
void quit(Player player) {
	string filename = player.name + ".txt";
	ofstream fout(filename.c_str());
	if (fout.fail()) {
		cout << "Error in file opening!" << endl;
		exit(1);
	}
	fout << player.name << " " << player.HP << " " << player.coin << " " << player.LV
		<< " " << player.floor << " " << player.row << " " << player.column << endl;
	fout.close();
	cout << player.name << ", Your archive has been saved." << endl;
	cout << "Quit the game, see you again!" << endl;
	exit(0);
}
