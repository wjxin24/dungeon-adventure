#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>

#include "dungeon.h"

using namespace std;

//use external defined variable 
extern Player player;

// initialize the default values for a new player
// input: a Player struct of a new player
void initialize_Newplayerinfo(Player& player) {
	player.HP = 100;
	player.coin = 0;
	player.LV = 1;
	player.floor = 1;
	player.row = 0;
	player.column = 0;
}
