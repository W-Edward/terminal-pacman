// #include <ncurses.h>
#include <curses.h>
// #include <windows.h>
#include <unistd.h> //replace w windows.h for windows
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include"StartnEndSequence.h"
#include"../entities/entities.h"
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
	string menuitem[17] = {
		"***********************************", 
		" Welcome to Pac-Man: Alpha Edition ", 
		"***********************************",
		"",
		"Play The Pac-Man Game !",
		"Load Player Profile",
		"How to Play",
		"View Game Statistics",
		"Export Player Profile",
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
	for (int i = 0; i < 17; i++) {
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
				return 1;
			}else if (selection == 1) {
				// Load Player Profile
				return 2;
			}else if (selection == 2) {
				// How to Play
				return 3;
			}else if (selection == 3) {
				// Load game statistics
				return 4;
			}else if (selection == 4) {
				// Export Player Profile
				return 5;
			}else if (selection == 5) {
				// exit the game
				return 6;
			}
		} else if (cinput == KEY_DOWN) {
			if (selection < 5) {
				selection++;
			} else { // loop back to the first option
				selection = 0;
			}
		} else if (cinput== KEY_UP) {
			if (selection > 0) {
				selection--;
			} else { // loop back to the last option
				selection = 5;
			}
		}
		usleep(150000);
	}

	getch();
	endwin();

	return 0;
}

int EndingSequence() {
	int yMax, xMax;
	string endingScreen[9] = {
		"  _ __   __ _  ___ _ __ ___   __ _ _ __  ",
		" | '_ \\ / _` |/ __| '_ ` _ \\ / _` | '_ \\ ",
		" | |_) | (_| | (__| | | | | | (_| | | | |",
		" | .__/ \\__,_|\\___|_| |_| |_|\\__,_|_| |_|",
		" |_|                                     ",
		"       Thanks for playing our game!      ",
		"",
		"      This game is jointly created by    ",
		"    Edward, Lewis, Kelly, Felix & Jason  ",
	};

    getmaxyx(stdscr,yMax,xMax);
    attron(COLOR_PAIR(1));
    for (int i = 0; i<9; i++) {
        move((yMax/2) - endingScreen->length()/2 + i,(xMax/2) - endingScreen[i].length()/2);
        addstr(endingScreen[i].c_str());
    }
    attroff(COLOR_PAIR(1));
    refresh();
    usleep(5000000);
	return 0;
}

void howToPlay(){
	int yMax, xMax;
	string instructions[19] = { // 44 spaces across
		"                How to Play!                ",
		"    ------------------------------------    ",
		"",
		"   The aim of the game is to capture the    ",
		"highest score before being eaten by ghosts. ",
		"",
		"   Control pacman to evade the ghosts and   ",
		"     capture as many fruits as you can!     ",
		"",
		" Ghosts have different colours to represent ",
		"  the states they are in, aside from their  ",
		"               normal colour.               ",
		"",
		"    Black and Gray for Frightened Mode:     ",
		" Pac-man can consume ghosts in this state.  ",
		"",
		"        Blue & Yellow for Eaten Mode:       ",
		"Pac-man cannot interact with ghosts in this ",
		"                   state.                   "
	};

	getmaxyx(stdscr,yMax,xMax);
    attron(COLOR_PAIR(1));
    for (int i = 0; i<19; i++) {
        move((yMax/2) - instructions->length()/2 + i,(xMax/2) - instructions[i].length()/2);
		if (i == 13 || i == 14) {
			attron(COLOR_PAIR(8));
			addstr(instructions[i].c_str());
			attron(COLOR_PAIR(1));
		} else {
			addstr(instructions[i].c_str());
		}
        
    }
    attroff(COLOR_PAIR(1));
    refresh();
	usleep(5000000);
}

int GameOver(int score){
	int yMax, xMax;
	string FinishScreen[9] = {
		" ____  ____ ________   ___    ___  __    __  ___  ____  ",
		"/  _ |/ _  |  _   _ \\ / _ \\  / _ \\ \\ \\  / / / _ \\|  __| ",
		"| (_|| (_| | | | | | |  __/ | (_) | \\ \\/ / |  __/| /    ",
		"\\__  |\\____|_| |_| |_|\\___|  \\___/   \\__/   \\___||_|    ",
		"|___/                                                   ",
		"        Oh no, Pac-Man got eaten by the ghosts!         ",
		"",
		"              Your score in this round is:              ",
		""	
	};

	int n = (54-to_string(score).size())/2; // number of blank spaces needed on either side of the score
	string spacing(n, ' ');
	FinishScreen[8] = spacing + to_string(score) + spacing;

    getmaxyx(stdscr,yMax,xMax);
    attron(COLOR_PAIR(1));
    for (int i = 0; i<9; i++) {
        move((yMax/2) - FinishScreen->length()/2 + i,(xMax/2) - FinishScreen[i].length()/2);
        addstr(FinishScreen[i].c_str());
    }
    attroff(COLOR_PAIR(1));
    refresh();
    usleep(5000000);
	return 0;
}

void loadStatistics(int score, string name, int highscore){
	int yMax, xMax;
	string stat[10] = {
		"                 Statistics                ",
		"    ----------------------------------     ",
		"",
		"                Player Name:               ",
		"",
		"            Highest Score Record:          ",
		"",
		"           Score of previous game:         ",
		"",
		"    ----------------------------------     ",
		};
	
	int n = (44-name.size())/2; // number of blank spaces needed on either side of the name
	string spacing(n, ' ');
	stat[4] = spacing + name + spacing;
	
	n = (44-to_string(highscore).size())/2; // number of blank spaces needed on either side of the highscore
	spacing.assign(n, ' ');
	stat[6] = spacing + to_string(highscore) + spacing;
	
	n = (44-to_string(score).size())/2; // number of blank spaces needed on either side of the score
	spacing.assign(n, ' ');
	stat[8] = spacing + to_string(score) + spacing;
	
    getmaxyx(stdscr,yMax,xMax);
    attron(COLOR_PAIR(1));
    for (int i = 0; i<10; i++) {
        move((yMax/2) - stat->length()/2 + i,(xMax/2) - stat[i].length()/2);
        addstr(stat[i].c_str());
    }
    attroff(COLOR_PAIR(1));
    refresh();
    usleep(5000000);
}

void CheckScore(int score, int &highscore){
	if (score>highscore)
		highscore=score;
}
	
void loadprofile(int &highscore, string &name){
	int yMax, xMax;
	ifstream fin;
	fin.open("Profile.txt");
	string loadscreen[10]={
	"           Import Player Profile          ",
	"    ----------------------------------    ",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"    ----------------------------------    	",
	};
	if (fin.fail()){
		loadscreen[2] ="";
		loadscreen[3] = "     Failed to import from Profile.txt!   ";
		loadscreen[4] ="";
		loadscreen[5] = "  Please put Profile.txt into the folder! ";
		loadscreen[6] ="";
		loadscreen[7] = " Example Profile.txt content: Andrew 3000 ";}
	else{
		fin >> name;
		fin >> highscore;
		loadscreen[2] = "  Successfully imported from Profile.txt! ";
		loadscreen[3] ="";
		loadscreen[4] = "               Player Name:               ";
		loadscreen[5] ="";
		loadscreen[6] = "           Highest Score Record:          ";
		loadscreen[7] ="";
		int n = (42-name.size())/2; // number of blank spaces needed on either side of the name
		string spacing(n, ' ');
		loadscreen[5] = spacing + name + spacing;
		n = (42-to_string(highscore).size())/2; // number of blank spaces needed on either side of the highscore
		spacing.assign(n, ' ');
		loadscreen[7] = spacing + to_string(highscore) + spacing;}
	fin.close();

	getmaxyx(stdscr,yMax,xMax);
    	attron(COLOR_PAIR(1));
    for (int i = 0; i<10; i++) {
        move((yMax/2) - loadscreen->length()/2 + i,(xMax/2) - loadscreen[i].length()/2);
        addstr(loadscreen[i].c_str());
    }
    attroff(COLOR_PAIR(1));
    refresh();
    usleep(5000000);
}

void exportprofile(int highscore, string name){
	int yMax, xMax;
	ofstream fout;
	fout.open("Profile.txt");
	string exportscreen[10]={
	"           Export Player Profile          ",
	"    ----------------------------------    ",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"    ----------------------------------    	",
	};
	if (fout.fail()){
		exportscreen[2] ="";
		exportscreen[3] = "      Failed to export to Profile.txt!    ";
		exportscreen[4] ="";
		exportscreen[5] = "  Try creating Profile.txt in the folder! ";
		exportscreen[6] ="";
		exportscreen[7] ="";}
	else{
		fout << name << endl;
		fout << highscore << endl;
		exportscreen[2] = "   Successfully exported to Profile.txt!  ";
		exportscreen[3] ="";
		exportscreen[4] = "               Player Name:               ";
		exportscreen[5] ="";
		exportscreen[6] = "           Highest Score Record:          ";
		exportscreen[7] ="";}
	fout.close();
		
	int n = (42-name.size())/2; // number of blank spaces needed on either side of the name
	string spacing(n, ' ');
	exportscreen[5] = spacing + name + spacing;
	
	n = (42-to_string(highscore).size())/2; // number of blank spaces needed on either side of the highscore
	spacing.assign(n, ' ');
	exportscreen[7] = spacing + to_string(highscore) + spacing;

	getmaxyx(stdscr,yMax,xMax);
    	attron(COLOR_PAIR(1));
    for (int i = 0; i<10; i++) {
        move((yMax/2) - exportscreen->length()/2 + i,(xMax/2) - exportscreen[i].length()/2);
        addstr(exportscreen[i].c_str());
    }
    attroff(COLOR_PAIR(1));
    refresh();
    usleep(5000000);
}
