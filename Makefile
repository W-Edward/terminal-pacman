# makes an executable file called main
GENERAL_FLAGS = -pedantic-errors -std=c++11
POSTFILE_FLAGS = -lncurses
STARTINGSEQ = StartnEndSequence
GHOST = ghost
GHOST_HEADER = entities
MAIN = main

# starting and end sequence
STARTINGSEQ_OBJ = StartnEndSequence.o
STARTINGSEQ_SRC = StartnEndSequence.cpp
STARTINGSEQ_HEADER = StartnEndSequence.h
# ghost
GHOST_OBJ = ghost.o
GHOST_SRC = ghost.cpp
GHOST_HEADER = entities.h
# main program
MAIN_OBJ = main.o
MAIN_SRC = main.cpp

$(STARTINGSEQ_OBJ): $(STARTINGSEQ_SRC) $(STARTINGSEQ_HEADER)
	g++ $(GENERAL_FLAGS) -c $(STARTINGSEQ_SRC)

$(GHOST_OBJ): $(GHOST_SRC) $(GHOST_HEADER)
	g++ $(GENERAL_FLAGS) -c $(GHOST_SRC)

$(MAIN_OBJ): $(MAIN_SRC) $(GHOST_HEADER) $(STARTINGSEQ_HEADER)
	g++ $(GENERAL_FLAGS) -c $(MAIN_SRC)

pacman: $(STARTINGSEQ_OBJ) $(GHOST_OBJ) $(MAIN_OBJ)
	g++ $(GENERAL_FLAGS) $^ $(LINKER_FLAGS) -o $@

clean:
	rm -f *.o

clean_all:
	rm -f *.o pacman *.h.gch

.PHONY: clean clean_all 