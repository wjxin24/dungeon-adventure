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

// print the current map and the map guide,
// read player's input continuously until the player quits/wins/loses,
// then calls the corresponding functions for different game events
// input: a Player struct of the current player's information,
//		  a 4*4 array of the map of current floor,
//		  a Position struct to store the current position of the player
void read_PlayerInput(Player& player, int map[4][4], Position& pos) {
	if (player.HP <= 0) {		// the player loses the game if HP <= 0
		cout << "Sorry, you lose the game!" << endl;
		exit(0);
	}
	print_Map(player.row, player.column, player.floor);
	print_MapGuide(player);

	char userinput;
	cin >> userinput;
	while (userinput != 'Q' && userinput != 'W' && userinput != 'S' &&
		userinput != 'D' && userinput != 'A' && userinput != 'B') {
		cout << endl << "Invalid input! Please type again:";
		cin >> userinput;
	}
	cout << endl;

	if (userinput == 'Q') {
		quit(player);
	}
	else {
		if (userinput == 'W' || userinput == 'S' || userinput == 'A' || userinput == 'D') {
			movement(userinput, player, map, pos);
			// a player enters the next floor if the player arrives at the exit
			if (player.row == 3 && player.column == 3)
				return;
		}

		else if (userinput == 'B') {
			buy(player);
		}

	}

	// keeps reading player's input until the player quits/wins/loses
	read_PlayerInput(player, map, pos);

}
