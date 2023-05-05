# makes the game an executable file called pacman
GENERAL_FLAGS = -pedantic-errors -std=c++11
LINKER_FLAGS = -lncurses

# starting and end sequence
STARTINGSEQ_OBJ = StartnEndSequence.o
STARTINGSEQ_SRC = StartnEndSequence.cpp
STARTINGSEQ_HEADER = StartnEndSequence.h
# ghost
GHOST_OBJ = ghost.o
GHOST_SRC = ghost.cpp
ENTITIES_HEADER = entities.h
# pacman
PACMAN_OBJ = pacman.o
PACMAN_SRC = pacman.cpp
# main program
MAIN_OBJ = main.o
MAIN_SRC = main.cpp

$(STARTINGSEQ_OBJ): $(STARTINGSEQ_SRC) $(STARTINGSEQ_HEADER)
	g++ $(GENERAL_FLAGS) -c $(STARTINGSEQ_SRC)

$(GHOST_OBJ): $(GHOST_SRC) $(ENTITIES_HEADER)
	g++ $(GENERAL_FLAGS) -c $(GHOST_SRC)

$(PACMAN_OBJ): $(PACMAN_SRC) $(ENTITIES_HEADER)
	g++ $(GENERAL_FLAGS) -c $(PACMAN_SRC)

$(MAIN_OBJ): $(MAIN_SRC) $(ENTITIES_HEADER) $(STARTINGSEQ_HEADER)
	g++ $(GENERAL_FLAGS) -c $(MAIN_SRC)

pacman: $(STARTINGSEQ_OBJ) $(GHOST_OBJ) $(PACMAN_OBJ) $(MAIN_OBJ)
	g++ $(GENERAL_FLAGS) $^ $(LINKER_FLAGS) -o $@

clean:
	rm -f *.o
clean_all:
	rm -f *.o pacman
	
.PHONY: clean clean_all