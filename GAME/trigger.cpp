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
// trigger a corresponding event if the player enters a grid with monsters/coins
// input: a Player struct of the player's information,
//		  a 4*4 array of the map for the current floor
void trigger(Player& player, int map[4][4]) {

	// if the grid contains a monster
	if (map[player.row][player.column] == 1) {
		char choice;
		cout << "You met a monster! The level range of the monster is ["
			<< player.floor * 3 - 2 << ',' << player.floor * 3 << ']' << endl;
		cout << "Do you want to fight the monster? Enter 'Y'/'N':";
		cin >> choice;
		cout << endl;
		while (choice != 'Y' && choice != 'N') {
			cout << "Invalid input! Pleaze enter 'Y'/'N':";
			cin >> choice;
		}

		// call the function fight_monster if the player wants to fight
		if (choice == 'Y') {
			fight_Monster(player);
			map[player.row][player.column] = 0;	  // reset to an empty grid
		}
		else {
			cout << "Ouch! You were attacked by the monster while fleeing away. HP-20" << endl;
			cout << endl;
			player.HP -= 20;
			if (player.HP <= 0) {
				cout << "Sorry, you lose the game!" << endl;
				exit(0);
			}
			cout << "HP:" << player.HP << ", LV=" << player.LV
				<< ", coins=" << player.coin << endl;
		}
	}

	// if the grid contains coins
	if (map[player.row][player.column] == 2) {
		cout << "You found some coins! coins+20" << endl;
		cout << endl;
		player.coin += 20;
		cout << "HP:" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
		map[player.row][player.column] = 0;	  // reset to an empty grid
	}
}
