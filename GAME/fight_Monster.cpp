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

// handle the fight with the monster
// input: a Player struct of the player's information
void fight_Monster(Player& player) {
	// a monster's level is randomly generated according to the floor number
	srand(time(NULL));
	int monster_lv = player.floor * 3 - rand() % 3;

	if (player.LV < monster_lv) {
		cout << "The monster is lv" << monster_lv << ". You lost the fight!"
			<< " HP-" << 10 * (monster_lv - player.LV) << endl;
		player.HP -= 10 * (monster_lv - player.LV);

		if (player.HP <= 0) {
			cout << "Sorry, you lose the game!" << endl;
			exit(0);
		}
		cout << "Update: " << "HP=" << player.HP << ", LV="
			<< player.LV << ", coins=" << player.coin << endl;
	}

	if (player.LV > monster_lv) {
		cout << "The monster is lv" << monster_lv << ". You win the fight! Well Done!"
			<< " coins+" << 25 * (player.LV - monster_lv) << endl;
		player.coin += 25 * (player.LV - monster_lv);
		cout << "Update: " << "HP=" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
	}

	if (player.LV == monster_lv) {
		cout << "The monster is lv" << monster_lv << ". Ended in a draw. Nothing happen!" << endl;
	}
	cout << endl;
}
