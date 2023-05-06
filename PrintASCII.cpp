#include <curses.h>
#include <fstream>
#include <string>
#include <iostream>
#include "./entities/entities.h"

void PrintASCII::txtprint(int deviationFromMidX, int deviationFromMidY, string filename, int colorpair) {\

	//variable setup
	int xMax,yMax;
    int xCursor, yCursor;

	//Cursor positioning
	getmaxyx(stdscr,yMax,xMax);
	yCursor = (yMax/2)-deviationFromMidY;
	xCursor = (xMax/2)-deviationFromMidX;
	move(yCursor,xCursor);

	//File IO setup
	ifstream txtfile;
	string line;
	txtfile.open(filename);
	 
	//error message for fail to open file
	 if (txtfile.fail()) {
		std::cerr << "ERROR: Fail to open the file" << endl;
		return;
	}

	//Drawing Loop
	attron(COLOR_PAIR(colorpair));
	for (int i=0; i < pictureHeight(filename); ++i){
		getline(txtfile,line);
		addstr(line.c_str());
		move(++yCursor,xCursor);
	}
	attroff(COLOR_PAIR(colorpair));
	txtfile.close();
	return;
}

int PrintASCII::pictureHeight(string filename) {
	 
	//variable setup
    int nol=0;

	//File IO setup
	ifstream target;
	string lines;
	target.open(filename);

	//error message for fail to open file
	if (target.fail()) {
		std::cout << "ERROR: Fail to open the file" << endl;
		return 0;
	}

	//getline loop for height
	while (getline(target,lines)) {
		nol += 1;
	}
	target.close();
	return nol;
}

int PrintASCII::pictureWidth(string filename) {
	
	//variable setup
	int now=0;
	
	//File IO setup
	ifstream target;
	string lines;
	target.open(filename);
	
	//error message for fail to open file
	if (target.fail()) {
		std::cout << "ERROR: Fail to open the file" << endl;
		return 0;
	}

	//count width
	getline(target, lines);
	now = lines.length();
	target.close();
	return now;
}