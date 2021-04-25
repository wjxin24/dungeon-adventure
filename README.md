# dungeon-advanture
## team members:
- Wu Jiaxin (3035770886)
- Chan KwanYi (3035691561)
## Game Description
This is an adventure game that the player, a warrior who is caught in the dungeon, wins the game if she/he successfully escapes from the nightmare. On the road to the exit of the dungeon, the player could beat back the monsters, gain rewards and enhance the strength. 

## Game Rule 
The dungeon has 3 floors LG2/LG1/G with ascending levels. On each floor, it is designed as a 4*4 table among which (0,0) is the entrance and (3,3) is the exit. The player who arrives (3,3) of the G floor is regarded as winning the game.

3

2

1

0

`     `0`      `1`      `2`      `3

On each floor, there are 3 monsters whose coordinates and levels are randomly generated. The range of monster levels on each floor increases. For example, on the 1st floor, the monster level: lv1-lv3. On the 2rd floor: lv4-lv6, etc.

For the player, there are 3 int attributes: HP (health points), combat-level, coin.
The player has 4 basic operations (press) W-S-A-D ←↑→↓to move around the grids. 

Coins could be used to buy HP or increase combat-level. (press B to enter the shop)

If the player meets the monsters (when moving to the coordinate where the monster lies), the player can know the range of the monster level but can not know the exact level number. And the player could gamble to join the battle or reject the battle with the monsters. 
If he joins, three results: 
wins if player-combat-level>monster-level, then coins gained;  
loses if player-combat-level>monster-level, then HP deducted ; 
if player-combat-level=monster-level, then nothing happens. 
If he rejects, a certain number of HP deducted.

On each floor, there are several coins whose coordinates are randomly generated. 
If the player meets the coin reward (move to the coordinate where the coin reward lies), then the player can gain the coins.

During the escape, if the player's HP=0, then he dies and the game is over. If the player could survive and arrive at (3,3) of the 3rd floor with HP>0, he wins the game. 

Player could choose to start a new game or continue last attempt (if exists).


## Coding elements and related features:
1. Generation of random game sets or events: 
    - Monsters and coins are generated in random grids (coordinate) whenever the player enters a new floor.
    - The levels of monsters are generated randomly within a given range on each floor.
2. Data structures for storing game status
    - An array is used to store the map of monsters and coins on each floor.
    - Status of the player (health points, combat level, the coordinate of the current grid, coins, path) is updated and stored by int or string variables after each move.
3. Dynamic memory management 
    - A vector is created to store the path (the grid that the player passed by) on each floor to remind him/her. 
    - Data of the path previous floors is deleted after the player enters a new floor, and the path date will be regenerated and stored in the memory.
4. File input/output (e.g., for loading/saving game status)
    - The player can save the game status, including health points, combat level and floor number, and quit the game at any time. The game status will be output as a file named after his/her name.
    - If this player chooses to continue the unfinished game (if exists), the file containing the game status of the unfinished game will be input. 
5. Program codes in multiple files 
    The program will include main() function and following functions:
    - the function to generate a random map of monsters and coins (generate_Map.cpp)
    - the function to process the player’s move (move.cpp)
    - the function to buy HP or increase combat level (buy.cpp)
    etc.
    
    Different functions are separately put in multiple files to make the code clearer.
   
## Non-standard C++ libraries used in the program:
#include <iostream> : cout/cin - read player's input and output guideline or information
#include <fstream>  : file input/output - If user quit game at any time, a file including game record named after his/her name will be outputed. If this player chooses to continue the unfinished game (if exists), the file containing the game status of the unfinished game will be input.
#include <string>   : the usage of string varaible. for example, player's name
#include <cstdlib>  : file input/output - fin.open(filename.c_str(),ios::in)
#include <cstdio>   : remove(filename.c_str()) - remove the file with records of last attempt if the player want to start a new game
#include <ctime>    : srand(time(NULL)) - time used to generate random numbers
#include <vector>   : vector <Position> path - a vector to store the path (the grid where the player passed by) on each floor

