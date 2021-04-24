#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
using namespace std;

// a struct for the coordinate of a position
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
vector <Position> path;

void print_Intro();

void initialize_newplayerinfo(Player& player);

void startGame(Player& player, int map[4][4]);

void generate_map(int map[4][4]);

void print_map(const int row, const int col, Player player);

void print_MapGuide(const Player player);

void read_PlayerInput(Player& player, int map[4][4], Position& pos);

void print_Path();

void movement(char move, Player& player, int map[4][4], Position& pos);

void trigger(Player& player, int map[4][4]);

void fight_monster(Player& player);

void buy(Player& player);

void quit(Player player);



int main() {
	string username;
	Player player;
	
	print_Intro();

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
				initialize_newplayerinfo(player);
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
		initialize_newplayerinfo(player);
	}

	int floorcount = 1;		// an interger to count the floor number

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

// print the game description and basic rules
void print_Intro() {
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
}

// initialize the default values for a new player
// input: a Player struct of a new player
void initialize_newplayerinfo(Player& player) {
	player.HP = 100;
	player.coin = 0;
	player.LV = 1;
	player.floor = 1;
	player.row = 0;
	player.column = 0;
}

// start the game on a new floor, and generate a random map for this floor,
// initialize the player's position,and begin to read the player's input
// input: a Player struct of the player's information,
//		  a zero 4*4 array to store the map of the current floor
void startGame(Player& player, int map[4][4]) {
	generate_map(map);
	Position pos;
	pos.x = 0;
	pos.y = 0;
	read_PlayerInput(player, map, pos);
}

// generate a random 4*4 map for a new floor
// input: a zero 4*4 array to store the map of the current floor
void generate_map(int map[4][4]) {
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

// print a map to show the floor number and the player's current position
// input: the row and column of the current position, floor number of the player
void print_map(const int row, const int col, int floor) {
	cout << endl;
	if (floor == 1) {
		cout << "Dungeon LG2! Run!" << endl;
	}
	else if (floor == 2) {
		cout << "Dungeon LG1! Run!" << endl;
	}
	else if (floor == 3) {
		cout << "Dungeon G! Final floor! Run!" << endl;
	}

	cout << "  ____________\n3|";
	if (row == 3) {
		for (int i = 0; i < col; i++)
			cout << "   ";
		cout << " X ";
		for (int i = col + 1; i < 4; i++)
			cout << "   ";
		cout << '|' << endl << "2|";
	}
	else {
		cout << "            |\n2|";
	}
	if (row == 2) {
		for (int i = 0; i < col; i++)
			cout << "   ";
		cout << " X ";
		for (int i = col + 1; i < 4; i++)
			cout << "   ";
		cout << '|' << endl << "1|";
	}
	else {
		cout << "            |\n1|";
	}
	if (row == 1) {
		for (int i = 0; i < col; i++)
			cout << "   ";
		cout << " X ";
		for (int i = col + 1; i < 4; i++)
			cout << "   ";
		cout << '|' << endl << "0|";
	}
	else {
		cout << "            |\n0|";
	}
	if (row == 0) {
		for (int i = 0; i < col; i++)
			cout << "   ";
		cout << " X ";
		for (int i = col + 1; i < 4; i++)
			cout << "   ";
		cout << '|' << endl;
	}
	else {
		cout << "            |\n";
	}
	cout << " |____________|\n   0  1  2  3\n";
}

// print the player's current attributes and a guide for input
// input: a Player struct of the player's information
void print_MapGuide(const Player player) {
	cout << "Your Current Attributes: " << "HP=" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
	cout << "enter 'W'/'A'/'S'/'D' to move upward/leftward/downward/rightward;" << endl;
	cout << "enter 'B' to buy HP or upgrade your LV;" << endl;
	cout << "enter 'Q' to save and quit the game;" << endl;
	cout << "Please enter:";

}

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
	print_map(player.row, player.column, player.floor);
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

// print player's path on the current floor
void print_Path() {
	vector<Position>::iterator itr;
	for (itr = path.begin(); itr != path.end(); itr++)
		cout << '(' << (*itr).x << ',' << (*itr).y << ") -> ";
}

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
			fight_monster(player);
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

// handle the fight with the monster
// input: a Player struct of the player's information
void fight_monster(Player& player) {
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

// function for the player to buy HP or upgrade level
// input: a Player struct of the player's information
void buy(Player& player) {
	char choice;
	cout << "Welcome to Dungeon Shop!" << endl;
	cout << "What do you want to buy? 1: Health points  2: Level   0: leave" << endl;
	cout << "Please enter '1'/'2'/'0':";
	cin >> choice;
	cout << endl;
	while (choice != '1' && choice != '2' && choice != '0') {
		cout << "Invalid input! Please enter '1'/'2'/'0':";
		cin >> choice;
	}

	while (choice != '0') {
		// handle purchase of HP
		if (choice == '1') {
			int amount;
			cout << "Your current HP = " << player.HP << ". You have " << player.coin << " coins now." << endl;
			cout << "Your HP should not exceed 100" << endl;
			cout << "How much health points do you want to buy?(1 coin for 1 health point):";
			cin >> amount;
			cout << endl;
			while (amount < 0) {
				cout << "Invalid input! Please enter a positive interger or enter 0 to cancel your purchase:";
				cin >> amount;
				cout << endl;
			}
			while (amount > player.coin) {
				cout << "Sorry, you don't have enough coins! You may enter 0 to cancel your purchase." << endl;
				cout << "Your current HP = " << player.HP << ". You have " << player.coin << " coins now." << endl;
				cout << "How much health points do you want to buy?(1 coin for 1 health point):";
				cin >> amount;
				cout << endl;
			}
			while (player.HP + amount > 100) {
				cout << "Sorry, your health points should not exceed 100!" << endl;
				cout << "Your current HP = " << player.HP << ". You have " << player.coin << " coins now." << endl;
				cout << "How much health points do you want to buy?(1 coin for 1 health point):";
				cin >> amount;
				cout << endl;
			}
			player.coin -= amount;
			player.HP += amount;
			cout << "Update: HP=" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
		}
		// handle upgrading of player's level
		if (choice == '2') {
			char respond;
			cout << "Your current level = " << player.LV << ". You have " << player.coin << " coins now." << endl;
			if (player.coin < player.LV * 5) {
				cout << "Upgrading to level " << player.LV + 1 << " will cost "
					<< player.LV * 5 << " coins. Sorry, you don't have enough coins!" << endl;
			}
			else {
				cout << "Upgrading to level " << player.LV + 1 << " will cost "
					<< player.LV * 5 << " coins. Do you want to upgrade?(Y/N):";
				cin >> respond;
				while (respond != 'Y' && respond != 'N') {
					cout << "Invalid input! Please enter 'Y'/'N':";
					cin >> respond;
				}
				if (respond == 'Y') {
					player.coin -= player.LV * 5;
					player.LV++;
					cout << "Update: HP=" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
				}
			}

		}

		cout << "What else do you want to buy? 1: Health points  2: Level   0: leave" << endl;
		cout << "Please enter '1'/'2'/'0':";
		cin >> choice;
		cout << endl;
		while (choice != '1' && choice != '2' && choice != '0') {
			cout << "Invalid input! Please enter '1'/'2'/'0':";
			cin >> choice;
			cout << endl;
		}
	}
	cout << "Thanks for visiting Dungeon Shop! Good luck! Bye!" << endl << endl;
}

// save the player's information into a txt file named after the player's name,
// and then exit the program
// input: a Player struct of the current player's information
void quit(Player player) {
	string filename = player.name + ".txt";
	ofstream fout(filename.c_str());
	if (fout.fail()) {
		cout << "Error in file opening!" << endl;
		exit(1);
	}
	fout << player.name << " " << player.HP << " " << player.coin << " " << player.LV
		<< " " << player.floor << " " << player.row << " " << player.column << endl;
	fout.close();
	cout << player.name << ", Your archive has been saved." << endl;
	cout << "Quit the game, see you again!" << endl;
	exit(0);
}




