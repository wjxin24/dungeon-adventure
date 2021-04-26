# Dungeon Adventure
## Team Members
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
    - Monsters and coins are generated in random grids whenever the player enters a new floor.
    - The levels of monsters are generated randomly within a given range on each floor.
2. Data structures for storing game status
    - An array is used to store the map of monsters and coins on each floor.
    - Status of the player (health points, combat level, coins, path, floor number, position) is updated and stored by int or string variables after each operation.
3. Dynamic memory management 
    - A vector is created to store the path (the grids that the player passed by) on each floor to remind him/her. 
    - Data of the path on previous floors will be deleted after the player enters a new floor, and the path data will be regenerated and stored in the memory.
4. File input/output (e.g., for loading/saving game status)
    - The player can save the game status, including health points, combat level, coins, floor number, position, and quit the game at any time. The game status will be output as a file named after his/her name.
    - If this player chooses to continue the unfinished game (if exists), the file containing the game status of the unfinished game will be input. 
5. Program codes in multiple files 
    - The program includes the following files:
      - the main function of the game (main.cpp)
      - the function to start the game after initializing game status (startGame.cpp)
      - the function to initialize the information for a new player (initialize_Newplayerinfo.cpp)
      - the function to read player input and call the corresponding functions (read_PlayerInput.cpp)
      - the function to print out the map and demonstrate the player's position (print_Map.cpp)
      - the function to print the guide (print_MapGuide.cpp)
      - the function to print the player's path on this floor (print_Path.cpp)
      - the function to generate a random map of monsters and coins (generate_Map.cpp)
      - the function to process the player’s move (movement.cpp)
      - the function to process the fight with a monster (fight_Monster.cpp)
      - the function to trigger different game events (trigger.cpp)
      - the function to buy HP or upgrade combat level (buy.cpp)
      - the function to save and output the game status to a file (quit.cpp)
      - a makefile to compile and link all the files (Makefile)
      - a header file to include the definition of structs and the declarations of all the functions (dungeon.h)
    
   - Different functions are separately put in multiple files to make the code clearer.
   
## Compilation and execution instructions:
- download and extract the files
- navigate to the directory "dungeonAdventure" (using command `cd`)
- enter `make dungeonAdventure`
- enter `./dungeonAdventure` to start the game
- input your name. If you are a newplayer or you choose to create a new game, it will open the new one. If you are a oldplayer who would like to continue last attemp, you input the same name with that of last attempt. Then the system will input and read your last attempt record file which is named after the player's name. For example, firstly save the file david.txt in 'file input and output' in the place where you put the programme cpp, then run the programme. choole input david and choose continue last attempt.

