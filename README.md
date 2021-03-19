# dungeon-advanture
## team members:
- Wu Jiaxin (3035770886)
- Chan KwanYi (3035691561)
## Game Description
This is an adventure game that the player, a warrior who is caught in the dungeon, wins the game if she/he successfully escapes from the nightmare. On the road to the exit of the dungeon, the player could beat back the monsters, gain rewards and enhance the strength. 

## Game Rule 
The dungeon has 5 floors where different floors stand for ascending levels. On each floor, it is designed as a 4*4 table with x-coordinate ( A B C D) and y-coordinate (0 1 2 3) among which A0 is the entrance and D3 is the exit. The player who arrives D3 of the 5-th floor is regarded as winning the game.

3

2

1

0

   A`      `B"      "C"      "D

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

During the escape, if the player's HP=0, then he dies and the game is over. If the player could survive and arrive at D3 of the 5-th floor with HP>0, he wins the game. 

## Features we want to implement:
- Monsters and coins are generated in random grids(coordinates) whenever the player enters a new floor.
- The levels of monsters are generated randomly within a given range on each floor.
- The player can see floor number, the coordinate of the current grid, health points, combat level, number of coins after each step.
- The coins a player can win after defeating a monster depends on level(player) - level(monster).
- The HP a player will lose after being defeated by a monster depends on level(monster) - level(player).
- The player can save the game status, including health points, combat level and floor number, and quit the game at any time.
- The player can start a new game or continue the unfinished game (if exists).

## Coding elements and related features:
1. Generation of random game sets or events: 
    - Monsters and coins are generated in random grids (coordinate) whenever the player enters a new floor.
    - The levels of monsters are generated randomly within a given range on each floor.
2. Data structures for storing game status
    - An array is used to store the map of monsters and coins on each floor.
    - Status of the player (health points, combat level, the coordinate of the current grid, coins, path) is updated and stored by int or string variables after each move.
3. Dynamic memory management 
    - Data of previous floors (map of monsters and coins, the path of the player) is deleted after the player enters a new floor, and a map of the new floor will be regenerated and stored in the memory.
    - Status of the player (health points, combat level, the coordinate of the current grid, coins, path) is updated and stored after each move.
4. File input/output (e.g., for loading/saving game status)
    - The player can save the game status, including health points, combat level and floor number, and quit the game at any time. The game status will be output as a file.
    - If the player starts a new game, a file containing the default starting status will be input. If the player continues the unfinished game (if exists), the file containing the game status of the unfinished game will be input.
5. Program codes in multiple files 
    The program will include main() function and following functions:
    - the function to generate a random map of monsters and coins
    - the function to process the player’s move, 
    - the function to make changes to the player’s status
    - the function to buy HP or increase combat level  
    etc.
    
    Different functions are separately put in multiple files to make the code clearer.

