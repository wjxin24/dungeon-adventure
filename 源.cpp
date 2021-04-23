#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

struct coor {
	int row;
	int column;
};

struct Player {
	string name;
	int HP;
	int coin;
	int LV;
	coor pos;
	int floor;
};

void read_PlayerInfo(Player player);

void generate_map(int map[4][4]);

void print_MapGuide(const Player player);

void print_map(const int row, const int col);

void read_PlayerInput();

//调整坐标 player.coor,添加path,触发怪兽,把到过的格子清空
void movement(char move, Player &player, int map[4][4], vector<coor> path);

void trigger(Player& player, int map[4][4]);

// monster level的范围根据player.floor决定
void fight_monster(Player& player);

void buy(Player &player);

void lose_game(string player_name);

void quit(Player player);

int main() {
	Player player;
	int map[4][4] = { 0 };
	vector<coor> path;
	char input;
	string name;
	string game_description; //还没写

	cout << game_description << endl;
	cout << "Please enter your name(no space allowed):";
	cin >> name;
	// if(...)
	cout << "Do you want to start a new game(n) or continue your game(c)?:";
	cin >> input;
	switch (input) {
	case 'n':
		// ...
		cout << endl;
		break;

	case 'c':
		read_PlayerInfo(player);
		cout << endl;
		break;

	default:
		cout << "Invalid input! Please type again (n/c):";
		cin >> input;
		cout << endl;
	}
}

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
	// generate coins in 3 random empty girds except entrance and exit
	int i = 0;
	while (i < 3) {
		int grid = rand() % 14 + 1;
		if (map[grid / 4][grid % 4] == 0)
			map[grid / 4][grid % 4] = 2;
		i++;
	}
}

void print_MapGuide(const Player player) {
	cout << "HP:" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
	cout << "enter 'W'/'A'/'S'/'D' to move upward/leftward/downward/rightward;" << endl;
	cout << "enter 'B' to buy HP or upgrade your LV;" << endl;
	cout << "enter 'Q' to save and quit the game;" << endl;
}

void print_map(const int row, const int col) {
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

void buy(Player& player) {
	int choice;
	cout << "Welcome to Dungeon Shop!" << endl;
	cout << "What do you want to buy? 1: Health points  2: Level   0: leave" << endl;
	cout << "Please enter '1'/'2'/'0':";
	cin >> choice;
	cout << endl;
	while (choice != 1 && choice != 2 && choice != 0) {
		cout << "Invalid input! Please enter '1'/'2'/'0':";
		cin >> choice;
	}
	while (choice != 0) {
		if (choice == 1) {
			int amount;
			cout << "How much health points do you want to buy?(1 coin for 1 health point):";
			cin >> amount;

			while (amount < player.coin) {
				cout << endl << "Sorry, you don't have enough coins!" << endl;
				cout << "How much health points do you want to buy?(1 coin for 1 health point):";
				cin >> amount;
				cout << endl;
			}
			while (player.HP + amount > 100) {
				cout << endl << "Sorry, your health points should not exceed 100!" << endl;
				cout << "How much health points do you want to buy?(1 coin for 1 health point):";
				cin >> amount;
			}
			player.coin -= amount;
			player.HP += amount;
			cout << "HP:" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
		}
		if (choice == 2) {
			char respond;
			cout << "Your current level:" << player.LV << endl;
			cout << "Upgrading to level " << player.LV + 1 << " will cost "
				<< player.LV * 5 << " coins. Do you want to upgrade?(y/n):";
			cin >> respond;
			while (respond != 'y' && respond != 'n') {
				cout << "Invalid input! Please enter 'y'/'n':";
				cin >> respond;
			}
			if (respond == 'y') {
				player.coin -= player.LV * 5;
				player.LV++;
				cout << "HP:" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
			}
		}
		
		cout << "What else do you want to buy? 1: Health points  2: Level   0: leave" << endl;
		cout << "Please enter '1'/'2'/'0':";
		cin >> choice;
		cout << endl;
		while (choice != 1 && choice != 2 && choice != 0) {
			cout << "Invalid input! Please enter '1'/'2'/'0':";
			cin >> choice;
			cout << endl;
		}
	}
	cout << "Thanks for visiting Dungeon Shop! Bye!" << endl;
}

void trigger(Player& player, int map[4][4]) {
	if (map[player.pos.row][player.pos.column] == 1) {
		char choice;
		cout << "You met a monster! The level range of the monster is ["
			<< player.floor * 3 - 2 << ',' << player.floor * 3 << ']' << endl;
		cout << "Do you want to fight the monster? Enter 'y'/'n':";
		cin >> choice;
		cout << endl;
		while (choice != 'y' && choice != 'n') {
			cout << "Invalid input! Pleaze enter 'y'/'n':";
			cin >> choice;
		}
		if (choice == 'y') {
			fight_monster(player);
			map[player.pos.row][player.pos.column] = 0;	  // reset to an empty grid
		}
		else {
			cout << "You were attacked by the monster while fleeing away... HP-10" << endl;
			player.HP -= 10;
			if (player.HP <= 0) {
				lose_game(player.name);
				return;
			}
			cout << "HP:" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
		}
	}
	if (map[player.pos.row][player.pos.column] == 2) {
		cout << "You found some coins! coins+10" << endl;
		player.coin += 10;
		cout << "HP:" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
		map[player.pos.row][player.pos.column] = 0;	  // reset to an empty grid
	}
}

void fight_monster(Player& player) {
	srand(time(NULL));
	int monster_lv = player.floor * 3 - rand() % 3;
	if (player.LV < monster_lv) {
		cout << "The monster is lv" << monster_lv << ". You lost the fight!"
			<< " HP-" << 10 * (monster_lv - player.LV) << endl;
		player.HP -= 10 * (monster_lv - player.LV);
		if (player.HP <= 0) {
			lose_game(player.name);
			return;
		}
		cout << "HP:" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
	}
	if (player.LV > monster_lv) {
		cout << "The monster is lv" << monster_lv << ". You win the fight!"
			<< " coins+" << 20 * (player.LV - monster_lv) << endl;
		player.coin += 20 * (player.LV - monster_lv);
		cout << "HP:" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
	}
}

void movement(char move, Player& player, int map[4][4], vector<coor> path) {
	if (move == 'w' && player.pos.row < 3) {
		player.pos.row++;
		path.push_back(player.pos);
	}
	if (move == 'a' && player.pos.column > 0) {
		player.pos.column--;
		path.push_back(player.pos);
	}
	if (move == 's' && player.pos.row > 0) {
		player.pos.row--;
		path.push_back(player.pos);
	}
	if (move == 'd' && player.pos.column < 3) {
		player.pos.column++;
		path.push_back(player.pos);
	}
	print_map(player.pos.row, player.pos.column);
	trigger(player, map);
}

