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
// generate a random 4*4 map for a new floor
// input: a zero 4*4 array to store the map of the current floor
void generate_Map(int map[4][4]) {
	srand(time(NULL));
	// generate monsters in 5 random empty girds except entrance and exit
	int i = 0;
	while (i < 5) {
		int grid = rand() % 14 + 1;
		if (map[grid / 4][grid % 4] == 0)
			map[grid / 4][grid % 4] = 1;
		i++;
	}
	// generate coins in 6 random empty girds except entrance and exit
	int j = 0;
	while (j < 6) {
		int grid = rand() % 14 + 1;
		if (map[grid / 4][grid % 4] == 0)
			map[grid / 4][grid % 4] = 2;
		j++;
	}
}
