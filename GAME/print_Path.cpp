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
// print player's path on the current floor
void print_Path() {
	vector<Position>::iterator itr;
	for (itr = path.begin(); itr != path.end(); itr++)
		cout << '(' << (*itr).x << ',' << (*itr).y << ") -> ";
}
