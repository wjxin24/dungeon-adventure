#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>

#include "dungeon.h"

using namespace std;

// start the game on a new floor, and generate a random map for this floor,
// initialize the player's position,and begin to read the player's input
// input: a Player struct of the player's information,
//		  a zero 4*4 array to store the map of the current floor
void startGame(Player& player, int map[4][4]) {
	generate_Map(map);
  Position pos;
	pos.x = 0;
	pos.y = 0;
	read_PlayerInput(player, map, pos);
}
