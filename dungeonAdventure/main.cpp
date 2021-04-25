#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>

#include "dungeon.h"

using namespace std;

// a vector to record the path of a player
vector <Position> path;

int main() {
	string username;
	Player player;

	cout << "## Game Description ##" << endl;
	cout << "Welcome to Dungeon-Adventure!" << endl;
	cout << "You,a warrior, are caught in the dungeon now." << endl;
	cout << "The dungeon has 3 floors of 4*4 grid with ascending difficulties." << endl;
	cout << "(0,0) is the entrance and (3,3) is the exit." << endl;
	cout << "On each floor, monsters and coins will randomly appear." << endl;
	cout << "You will win the game if you successfully arrive (3,3) of the final floor." << endl;
	cout << "Good Luck!" << endl;
	cout << "######################" << endl;
	cout << " " << endl;

	cout << "please type your name(no space allowed):" << endl;
	cin >> username;

	// check if the player has an unfinished game
	string filename = username + ".txt";

	ifstream fin;
	fin.open(filename.c_str(), ios::in);
	if (fin) {
		char input_norc;
		cout << "Hi, " << username << "! You have an unfinished game." << endl;
		cout << "Do you want to Start A New Game (please type N) or Continue (please type C)?:";
		bool flag = true;
		while (flag == true) {
			cout << endl;
			cin >> input_norc;
			if (input_norc == 'N') {
				cout << "Hi, " << username << "! Welcome to your new game." << endl;
				player.name = username;
				initialize_Newplayerinfo(player);
				flag = false;
				break;
			}
			else if (input_norc == 'C') {
				cout << "Hi, " << username << "! Continue last try." << endl;
				// read the player's information from the corresponding file
				ifstream fin1(filename.c_str());
				string n;
				int hp;
				int coins;
				int lv;
				int f;
				int r;
				int c;
				fin1 >> n >> hp >> coins >> lv >> f >> r >> c;
				player.name = n;
				player.HP = hp;
				player.coin = coins;
				player.LV = lv;
				player.floor = f;
				player.row = r;
				player.column = c;
				fin1.close();
				flag = false;
				break;
			}
			else {
				cout << "Invalid input! Please type again (N/C):";
			}
		}
		fin.close();
		// remove the file after the player's information is imported
		// or the player starts a new game
		remove(filename.c_str());
	}

	else {
		cout << "Hi, " << username << "! Welcome to your new game" << endl;
		player.name = username;
		initialize_Newplayerinfo(player);
	}

	int floorcount = player.floor;		// an interger to count the floor number

	while (floorcount < 4) {
		int map[4][4] = { 0 };
		startGame(player, map);
		player.row = 0;
		player.column = 0;
		player.floor++;
		floorcount++;
	}
	if (floorcount == 4) {
		cout << "Congratulations! You win!" << endl;
		exit(0);
	}
	return 0;

}
