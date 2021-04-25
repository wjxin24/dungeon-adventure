

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>

using namespace std;

#ifndef DUNGEON
#define DUNGEON


struct Position {
	int x;
	int y;
};

// a struct for the information of a player
struct Player {
	string name;
	int HP;
	int coin;
	int LV;
	int floor;
	int row;
	int column;
};

// a vector to record the path of a player




void initialize_Newplayerinfo(Player& player);

void startGame(Player& player, int map[4][4]);

void generate_Map(int map[4][4]);

void print_Map(const int row, const int col, int floor);

void print_MapGuide(const Player player);

void read_PlayerInput(Player& player, int map[4][4], Position& pos);

void print_Path();

void movement(char move, Player& player, int map[4][4], Position& pos);

void trigger(Player& player, int map[4][4]);

void fight_Monster(Player& player);

void buy(Player& player);

void quit(Player player);



#endif
