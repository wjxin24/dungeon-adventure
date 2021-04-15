#include <iostream>
#include <cstdlib>
#include <ctime>
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

void generate_map(int* map[4][4]);

void print_MapGuide();

void read_PlayerInput();

//调整坐标 player.coor,添加path,触发怪兽,把到过的格子清空
void movement(char move, Player &player, int map[4][4], coor path[]);

void trigger(Player& player, int map);

// monster level的范围根据player.floor决定
void fight_monster(Player& player);

void buy(Player &player);

void quit(Player player);

int main() {
	Player player;
	int map[4][4];
	coor *path = new coor[];
	char input;
	string game_description; //还没写

	cout << game_description << endl;
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