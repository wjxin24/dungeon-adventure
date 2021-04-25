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
// print the player's current attributes and a guide for input
// input: a Player struct of the player's information
void print_MapGuide(const Player player) {
	cout << "Your Current Attributes: " << "HP=" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
	cout << "enter 'W'/'A'/'S'/'D' to move upward/leftward/downward/rightward;" << endl;
	cout << "enter 'B' to buy HP or upgrade your LV;" << endl;
	cout << "enter 'Q' to save and quit the game;" << endl;
	cout << "Please enter:";

}
