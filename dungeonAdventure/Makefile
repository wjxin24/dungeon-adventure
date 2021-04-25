FLAGS = -pedantic-errors -std=c++11
fight_Monster.o: fight_Monster.cpp dungeon.h
	g++ $(FLAGS) -c $<
trigger.o: trigger.cpp  dungeon.h
	g++ $(FLAGS) -c $<
print_Path.o: print_Path.cpp dungeon.h
	g++ $(FLAGS) -c $<
movement.o: movement.cpp dungeon.h
	g++ $(FLAGS) -c $<
quit.o: quit.cpp dungeon.h
	g++ $(FLAGS) -c $<
buy.o: buy.cpp dungeon.h
	g++ $(FLAGS) -c $<
print_Map.o: print_Map.cpp dungeon.h
	g++ $(FLAGS) -c $<
print_MapGuide.o: print_MapGuide.cpp dungeon.h
	g++ $(FLAGS) -c $<
read_PlayerInput.o: read_PlayerInput.cpp dungeon.h
	g++ $(FLAGS) -c $<
generate_Map.o: generate_Map.cpp dungeon.h
	g++ $(FLAGS) -c $<
startGame.o: startGame.cpp dungeon.h
	g++ $(FLAGS) -c $<
initialize_Newplayerinfo.o: initialize_Newplayerinfo.cpp dungeon.h
	g++ $(FLAGS) -c $<
main.o: main.cpp dungeon.h
	g++ $(FLAGS) -c $<

dungeonAdventure: fight_Monster.o trigger.o print_Path.o movement.o quit.o buy.o print_Map.o print_MapGuide.o read_PlayerInput.o generate_Map.o startGame.o initialize_Newplayerinfo.o main.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f dungeonAdventure fight_Monster.o trigger.o print_Path.o movement.o quit.o buy.o print_Map.o print_MapGuide.o read_PlayerInput.o generate_Map.o startGame.o initialize_Newplayerinfo.o main.o dungeonAdventure.tgz

tar:
	tar -czvf dungeonAdventure.tgz *.cpp *.h

.PHONY: clean tar