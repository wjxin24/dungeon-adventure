#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>

#include "dungeon.h"

using namespace std;

// change the player's position and add to the player's path,
// call the function trigger to trigger events when a player enters new grids
// input: a character of the direction of movement input by the player,
//		  a 4*4 array of the map of the current floor,
//		  a Position struct to store the current position of the player
void movement(char move, Player& player, int map[4][4], Position& pos) {

	if (move == 'W') {
		if (player.row < 3) {
			player.row++;
			pos.x = player.row;
			path.push_back(pos);
		}
		else {
			cout << "Oops! You bumped into the wall" << endl;
			return;
		}
	}
	else if (move == 'A') {
		if (player.column > 0) {
			player.column--;
			pos.y = player.column;
			path.push_back(pos);
		}
		else {
			cout << "Oops! You bumped into the wall" << endl;
			return;
		}
	}
	else if (move == 'S') {
		if (player.row > 0) {
			player.row--;
			pos.x = player.row;
			path.push_back(pos);
		}
		else {
			cout << "Oops! You bumped into the wall" << endl;
			return;
		}
	}
	else if (move == 'D') {
		if (player.column < 3) {
			player.column++;
			pos.y = player.column;
			path.push_back(pos);
		}
		else {
			cout << "Oops! You bumped into the wall" << endl;
			return;
		}
	}

	// print the player's path on this floor
	print_Path();
	cout << " " << endl;

	// when the player reaches the exit grid
	// clear the path on this floor, and initialize the player's position
	// return to the main function to continue the game on the next floor
	if (player.row == 3 && player.column == 3) {
		path.clear();
		pos.x = 0;
		pos.y = 0;
		path.push_back(pos);
		return;
	}
	else {
		trigger(player, map);
	}
}
