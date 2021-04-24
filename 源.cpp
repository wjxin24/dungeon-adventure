#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
using namespace std;


struct Position {
 	int x;
 	int y;
};

struct Player {
 	string name;
 	int HP;
 	int coin;
 	int LV;
 	int floor;
  int row;
  int column;
};

vector <Position> path;


void buy(Player &player);
void fight_monster(Player& player);
void generate_map(int map[4][4]);
void initialize_newplayerinfo(Player & player);
void movement(char move, Player &player, int map[4][4], Position & pos);
void next_floor(Player& player, int map[4][4], Position &pos);
void print_Intro();
void print_MapGuide(const Player player);
void print_map(const int row, const int col, Player player);
void print_Path();
void quit(Player player, string name);
void read_PlayerInput(Player &player, int map[4][4], Position & pos);
void startGame(Player &player, int map[4][4]);
void trigger(Player& player, int map[4][4]);

int main(){
  print_Intro();
  cout << "please type your name(no space allowed):" << endl;
  string username;
  cin >> username;
  Player player;
  string filename = username + ".txt";
  ifstream fin;
  fin.open(filename.c_str(),ios::in);
  if(fin){
    char input_norc;
    cout << "Hi, " << username << "! You have an unfinished game." << endl;
    cout << "Do you want to Start A New Game (please type N) or Continue (please type C)?" << endl;
    bool flag = true;
    while (flag == true){
      cin >> input_norc;
      if (input_norc == 'N'){
        cout << "Hi, "<<username <<"! Welcome to new game." << endl;
        player.name = username;
        initialize_newplayerinfo(player);
        flag = false;
        break;
      }
      else if (input_norc == 'C'){
        cout << "Hi, " << username << "! Continue last try." << endl;
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
        cout << "Invalid input! Please type again (N/C):" << endl;
      }
    }
    fin.close();
    remove(filename.c_str());
  }

  else{
    cout << "Hi, " << username << "! Welcome to new game" << endl;
    player.name = username;
    initialize_newplayerinfo(player);
    fin.close();
  }

  int floorcount = 1;
  int map[4][4] = {0};
  while (floorcount < 4){
    startGame(player,map);//yao fuzhi'
    player.row = 0;
    player.column = 0;
    player.floor++;
    floorcount++;

  }
  if (floorcount == 4){
    cout << "Congratulations! You win!" << endl;
    exit(0);
  }
  return 0;

}


void print_Intro(){
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




void print_Path(){
  vector<Position>::iterator itr;
  for (itr = path.begin(); itr != path.end(); itr++)
     cout << '(' << (*itr).x << ','<<(*itr).y << ") -> ";
}


void initialize_newplayerinfo(Player & player){
  player.HP = 100;
  player.coin = 0;
  player.LV = 1;
  player.floor = 1;
  player.row = 0;
  player.column = 0;
}


void quit(Player player, string name){
  string filename = name + ".txt";
  ofstream fout(filename.c_str());//erase yes
  if (fout.fail()){
    cout << "Error in file opening!" << endl;
    exit(1);
  }
  fout << player.name << " " << player.HP << " " << player.coin << " " << player.LV << " " << player.floor << " " << player.row<<" " <<player.column<<endl;
  fout.close();
  cout << name << ", Your archive has been saved." << endl;
  cout << "Quit the game, see you again!" << endl;
  exit(0);
}

void read_PlayerInput(Player &player, int map[4][4], Position &pos){
  if (player.HP <= 0) {
    cout << "Sorry, you lose the game!" << endl;
    exit(0);
  }
  print_map(player.row, player.column, player);
  print_MapGuide(player);
  char userinput;
  cin >> userinput;
  cout << endl;
  if (userinput == 'Q'){
    quit(player, player.name);
  }
  else {
    if (userinput == 'W' || userinput == 'S' || userinput == 'A' || userinput == 'D'){
      movement(userinput, player, map, pos);
      if (player.floor==4)
	      return;
    }
    else if (userinput == 'B'){
      buy(player);
    }
    else {
      cout<< "Invalid input! Please type again." << endl;
    }
    if(player.row == 3 && player.column == 3){
      return;
    }
    else{
      read_PlayerInput(player, map, pos);
    }
  }
}

//   movement generate map  buy
void startGame(Player &player, int map[4][4]){
  generate_map(map);
  Position pos;
  pos.x = 0;
  pos.y = 0;
  read_PlayerInput(player, map, pos);
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
	// generate coins in 6 random empty girds except entrance and exit
	int j = 0;
	while (j < 6) {
		int grid = rand() % 14 + 1;
		if (map[grid / 4][grid % 4] == 0)
			map[grid / 4][grid % 4] = 2;
		j++;
	}
}

void print_MapGuide(const Player player) {
	cout << "Your Current Attributes: "<<"HP=" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
	cout << "enter 'W'/'A'/'S'/'D' to move upward/leftward/downward/rightward;" << endl;
	cout << "enter 'B' to buy HP or upgrade your LV;" << endl;
	cout << "enter 'Q' to save and quit the game;" << endl;
  cout<< "Please enter:";

}

void print_map(const int row, const int col, Player player) {
  cout << endl;
  if (player.floor == 1){
    cout << "Dungeon LG2! Run!" << endl;
  }
  else if (player.floor == 2){
    cout << "Dungeon LG1! Run!" << endl;
  }
  else if (player.floor == 3){
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
      cout << "Your current HP = " << player.HP << ". You have " << player.coin << " coins now." << endl;
      cout << "Your HP should not exceed 100" << endl;
			cout << "How much health points do you want to buy?(1 coin for 1 health point):";
			cin >> amount;
			cout << endl;
			while (amount < 0){
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
			cout <<"Update: HP=" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
		}
		if (choice == 2) {
			char respond;
			cout << "Your current level = " << player.LV << ". You have " << player.coin << " coins now." << endl;
      if (player.coin < player.LV * 5){
        cout << "Upgrading to level " << player.LV + 1 << " will cost "
  				<< player.LV * 5 << " coins. Sorry, you don't have enough coins!"<<endl;
      }
      else{
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
		while (choice != 1 && choice != 2 && choice != 0) {
			cout << "Invalid input! Please enter '1'/'2'/'0':";
			cin >> choice;
			cout << endl;
		}
	}
	cout << "Thanks for visiting Dungeon Shop! Good luck! Bye!" << endl << endl;
}

void trigger(Player& player, int map[4][4]) {
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
		if (choice == 'Y') {
			fight_monster(player);
			map[player.row][player.column] = 0;	  // reset to an empty grid
		}
		else {
			cout << "Ouch! You were attacked by the monster while fleeing away... HP-10" << endl;
      cout<<endl;
			player.HP -= 10;
			if (player.HP <= 0) {
				cout << "Sorry, you lose the game!" << endl;
				exit(0);
			}
			cout << "HP:" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
		}
	}
	if (map[player.row][player.column] == 2) {
		cout << "You found some coins! coins+20" << endl;
    cout<<endl;
		player.coin += 20;
		cout << "HP:" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
		map[player.row][player.column] = 0;	  // reset to an empty grid
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
			cout << "Sorry, you lose the game!" << endl;
			exit(0);
		}
		cout << "Update: "<<"HP=" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
	}
	if (player.LV > monster_lv) {
		cout << "The monster is lv" << monster_lv << ". You win the fight! Well Done!"
			<< " coins+" << 40 * (player.LV - monster_lv) << endl;
		player.coin += 40 * (player.LV - monster_lv);
		cout << "Update: "<<"HP=" << player.HP << ", LV=" << player.LV << ", coins=" << player.coin << endl;
	}
  if (player.LV == monster_lv){
    cout << "The monster is lv" << monster_lv <<". Ended in a draw. Nothing happen!" << endl;

  }
  cout << endl;
}

void movement(char move, Player& player, int map[4][4], Position& pos) {

	if (move == 'W') {
		if (player.row < 3){
		player.row++;
    		pos.x = player.row;
		path.push_back(pos);
		}
		else{
			cout << "Oops! You bumped into the wall" << endl;
			return;
		}
	}
	else if (move == 'A'){
		if (player.column > 0) {
		player.column--;
    		pos.y = player.column;
		path.push_back(pos);
		}
		else{
			cout << "Oops! You bumped into the wall" << endl;
			return;
		}
	}
	else if (move == 'S'){
		if (player.row > 0) {
		player.row--;
    		pos.x = player.row;
		path.push_back(pos);
		}
		else{
			cout << "Oops! You bumped into the wall" << endl;
			return;
		}
	}
	else if (move == 'D'){ 
		if (player.column < 3) {
		player.column++;
    		pos.y = player.column;
		path.push_back(pos);
		}
		else{
			cout << "Oops! You bumped into the wall" << endl;
			return;
		}
	}
  
  print_Path();
  cout << " " <<endl;

 if (player.row == 3 && player.column == 3 ) {
     path.clear();
     pos.x = 0;
     pos.y = 0;
     path.push_back(pos);
     return;
	}
  else{
    trigger(player, map);
  }

}


