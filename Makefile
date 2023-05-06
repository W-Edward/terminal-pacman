# makes the game an executable file called pacman
GENERAL_FLAGS = -pedantic-errors -std=c++11
LINKER_FLAGS = -lncurses

# starting and end sequence
STARTINGSEQ_OBJ = sequences.o
STARTINGSEQ_SRC = ./sequences/sequences.cpp
STARTINGSEQ_HEADER = ./sequences/sequences.h
# ghost
GHOST_OBJ = ghost.o
GHOST_SRC = ./entities/ghost.cpp
ENTITIES_HEADER = ./entities/entities.h
# pacman
PACMAN_OBJ = pacman.o
PACMAN_SRC = ./entities/pacman.cpp

PRINTASCII_OBJ = PrintASCII.o
PRINTASCII_SRC = PrintASCII.cpp
# main program
MAIN_OBJ = main.o
MAIN_SRC = main.cpp

$(GHOST_OBJ): $(GHOST_SRC) $(ENTITIES_HEADER)
	g++ $(GENERAL_FLAGS) -c $(GHOST_SRC)

$(PACMAN_OBJ): $(PACMAN_SRC) $(ENTITIES_HEADER)
	g++ $(GENERAL_FLAGS) -c $(PACMAN_SRC)

$(PRINTASCII_OBJ): $(PRINTASCII_SRC) $(ENTITIES_HEADER)
	g++ $(GENERAL_FLAGS) -c $(PRINTASCII_SRC)

$(STARTINGSEQ_OBJ): $(STARTINGSEQ_SRC) $(ENTITIES_HEADER) $(STARTINGSEQ_HEADER)
	g++ $(GENERAL_FLAGS) -c $(STARTINGSEQ_SRC)

$(MAIN_OBJ): $(MAIN_SRC) $(ENTITIES_HEADER) $(STARTINGSEQ_HEADER)
	g++ $(GENERAL_FLAGS) -c $(MAIN_SRC)

pacman: $(STARTINGSEQ_OBJ) $(GHOST_OBJ) $(PACMAN_OBJ) $(PACMAN_OBJ) $(MAIN_OBJ)
	g++ $(GENERAL_FLAGS) $^ $(LINKER_FLAGS) -o $@

clean:
	rm -f *.o
clean_all:
	rm -f *.o pacman
	
.PHONY: clean clean_all