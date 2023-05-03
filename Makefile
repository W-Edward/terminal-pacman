# makes an executable file called main
GENERAL_FLAGS = -pedantic-errors -std=c++11
POSTFILE_FLAGS = -lncurses
STARTINGSEQ = StartnEndSequence
GHOST = ghost
GHOST_HEADER = entities
MAIN = maincursewithnewmap

$(STARTINGSEQ).o: $(STARTINGSEQ).cpp $(STARTINGSEQ).h
	g++ $(GENERAL_FLAGS) -c $^ $(POSTFILE_FLAGS)

$(GHOST).o: $(GHOST).cpp $(GHOST_HEADER).h
	g++ $(GENERAL_FLAGS) -c $(GHOST).cpp $(POSTFILE_FLAGS)

$(MAIN).o: $(MAIN).cpp $(GHOST_HEADER).h $(STARTINGSEQ).h # might need to link StartingSeq's header file to this eventually
	g++ $(GENERAL_FLAGS) -c $(MAIN).cpp $(POSTFILE_FLAGS)

main: $(MAIN).o $(GHOST).o $(STARTINGSEQ).o # might need to link StartingSeq's object file to this eventually
	g++ $(GENERAL_FLAGS) $^ $(POSTFILE_FLAGS) -o $@

clean:
	rm -f *.o

clean_all:
	rm -f *.o main

.PHONY: clean clean_all