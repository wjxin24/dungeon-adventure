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
