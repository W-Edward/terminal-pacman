#include <ncurses.h>
#include <curses.h>
// #include <windows.h>
#include <unistd.h> //replace w windows.h for linux
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include"StartnEndSequence.h"
using namespace std;

int fileline(string filename) {
	int nol=0;
	ifstream target;
	string lines;
	target.open(filename);
	if (target.fail()) {
		cout << "ERROR: Fail to open the file" << endl;
		return 0;
	}
	while (getline(target,lines)) {
		nol += 1;
	}
	target.close();
	return nol;
}

void mainmenu_display (int select) {
	int xMax,yMax,nol;
    int xCursor, yCursor;
	// ifstream art;
	// string logo;
	string menuitem[15] = {
		"***********************************", 
		" Welcome to Pac-Man: Alpha Edition ", 
		"***********************************",
		"",
		"Play The Pac-Man Game !",
		"Load Save",
		"Game Statistics",
		"Exit The Game",
		"",
		"Please ensure your terminal font size is 16!",
		"",
		"Please also do not adjust the terminal screen",
		" while playing to avoid text display errors! ",
		"",
		"Use keyboard arrow keys to navigate the menu.",

	};

	getmaxyx(stdscr,yMax,xMax);

	// art.open("./ascii_art/pacman_title.txt");
	// nol = fileline("./ascii_art/pacman_title.txt");
	// xCursor = (xMax/2);
    // yCursor = (yMax/2)-menuitem->length()/2-nol-1;
	// move(yCursor, xCursor);

	
	// while (getline(art,logo)) {
	// 	xCursor = (xMax/2) - logo.length()/2;
	// 	move(yCursor++, xCursor);
	// 	addstr(logo.c_str());
		
	// }
	
	attron(COLOR_PAIR(1));
	for (int i = 0; i < 15; i++) {
		if (i-4 == select) {
			attron(A_REVERSE);
		}
		xCursor = (xMax/2) - menuitem[i].length()/2;
		yCursor = (yMax/2) - menuitem->length()/2 + i;
		move(yCursor,xCursor);
		addstr(menuitem[i].c_str());
		if (i-4 == select) {
			attroff(A_REVERSE);
		}
	}
	attroff(COLOR_PAIR(1));

	refresh();
}

int StartingSequence(){
	initscr();
	start_color();
	if(can_change_color()) {
        init_color(COLOR_BLACK,0,0,0);
        init_color(COLOR_CYAN,0,0,888);
    }
	init_pair(1,COLOR_YELLOW,COLOR_CYAN);
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	int selection = 0;

	while (true) {
		mainmenu_display(selection);
		int cinput = getch();
		if (cinput == '\n') {
			if (selection == 0){
				//enter the main game
				cout << "asdf" << endl;
				return 1;
			}else if (selection == 1) {
				// Load save
				return 2;
			}else if (selection == 2) {
				// Load game statistics
				return 3;
			}else if (selection == 3) {
				// exit the game
				return 4;
			}
		} else if (cinput == KEY_DOWN) {
			if (selection < 3) {
				selection++;
			} else { // loop back to the first option
				selection = 0;
			}
		} else if (cinput== KEY_UP) {
			if (selection > 0) {
				selection--;
			} else { // loop back to the last option
				selection = 3;
			}
		}
		usleep(150000);
	}

	getch();
	endwin();

	return 0;
}

int EndingSequence(int score) {
	int yMax, xMax;
	string endingScreen[12] = {
		"  _ __   __ _  ___ _ __ ___   __ _ _ __  ",
		" | '_ \\ / _` |/ __| '_ ` _ \\ / _` | '_ \\ ",
		" | |_) | (_| | (__| | | | | | (_| | | | |",
		" | .__/ \\__,_|\\___|_| |_| |_|\\__,_|_| |_|",
		" |_|                                     ",
		"       Thanks for playing our game!      ",
		"",
		"      This game is jointly created by    ",
		"    Edward, Lewis, Kelly, Felix & Jason  ",
		"",
		"        Your score in this round is:     ",
		"" // to be replaced
	};
	/* "  _ __   __ _  ___ _ __ ___   __ _ _ __  ",
		" | '_ \\ / _` |/ __| '_ ` _ \\ / _` | '_ \\ ",
		" | |_) | (_| | (__| | | | | | (_| | | | |",
		" | .__/ \\__,_|\\___|_| |_| |_|\\__,_|_| |_|",
		" |_|                                     ", */

	int n = (41-to_string(score).size())/2; // number of blank spaces needed on either side of the score
	string spacing(n, ' ');
	endingScreen[11] = spacing + to_string(score) + spacing;

    getmaxyx(stdscr,yMax,xMax);
    attron(COLOR_PAIR(1));
    for (int i = 0; i<12; i++) {
        move((yMax/2) - endingScreen->length()/2 + i,(xMax/2) - endingScreen[i].length()/2);
        addstr(endingScreen[i].c_str());
    }
    attroff(COLOR_PAIR(1));
    refresh();
    usleep(5000000);
	return 0;
}
