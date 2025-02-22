// #include <ncurses.h>
#include <curses.h>
// #include <windows.h>
#include <unistd.h> //replace w windows.h for windows
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "./entities/entities.h"
#include "./sequences/sequences.h"
using namespace std;

//Notes:
//Compile with "g++ -pedantic-errors -std=c++11 maincursewithnewmap.cpp ghost.cpp -lncurses -o mainCurses", any method of compilation is allowed for this project 
//Make sure terminal is big enough BEFORE starting the game
//DON'T ADJUST TERMINAL SIZE WHILE PLAYING GAME, IT WILL BREAK!

// face is the direction pacman is facing
// direction is the input of the user

void display(Pacman &Pacman, Ghost &Blinky, Ghost &Pinky, Ghost &Inky, Ghost &Clyde, string map[19][20]){
    int xMax,yMax;
    int xCursor, yCursor; //Placement of cursor in "stdscr" window

    getmaxyx(stdscr,yMax,xMax);

    attron(COLOR_PAIR(9));
    xCursor = (xMax/2)-21;
    yCursor = (yMax/2)-21;
    move(yCursor,xCursor);
    addstr("                                           ");
    move(++yCursor,xCursor);
    for(int i = 0; i < 20; i++) {
        addstr("  ");
        if (i == 19) {
            move(yCursor,xCursor+1);
            addstr("  W - Up; A - Left; S - Down; D - Right  ");
        }
        move(yCursor,xCursor+41);
        addstr("  ");
        ++yCursor;
        move(yCursor,xCursor);
    }
    addstr("                                           ");
    attroff(COLOR_PAIR(9));

    xCursor = (xMax/2)-20;
    yCursor = (yMax/2)-20;
    move(yCursor, xCursor);

    // erasing the old Pacman and ghosts
    map[Pacman.getLastY()][Pacman.getLastX()] = "  ";
    if (Blinky.ateApple) {map[Blinky.getLastY()][Blinky.getLastX()] = "''";}
    else if (Blinky.atePowerPellet) {map[Blinky.getLastY()][Blinky.getLastX()] = "||";}
    else {map[Blinky.getLastY()][Blinky.getLastX()] = "  ";}

    if (Pinky.ateApple) {map[Pinky.getLastY()][Pinky.getLastX()] = "''";}
    else if (Pinky.atePowerPellet) {map[Pinky.getLastY()][Pinky.getLastX()] = "||";}
    else {map[Pinky.getLastY()][Pinky.getLastX()] = "  ";}

    if (Inky.ateApple) {map[Inky.getLastY()][Inky.getLastX()] = "''";}
    else if (Inky.atePowerPellet) {map[Inky.getLastY()][Inky.getLastX()] = "||";}
    else {map[Inky.getLastY()][Inky.getLastX()] = "  ";}

    if (Clyde.ateApple) {map[Clyde.getLastY()][Clyde.getLastX()] = "''";}
    else if (Clyde.atePowerPellet) {map[Clyde.getLastY()][Clyde.getLastX()] = "||";}
    else {map[Clyde.getLastY()][Clyde.getLastX()] = "  ";}

    // map[Blinky.getLastY()][Blinky.getLastX()] = "  ";
    // map[Pinky.getLastY()][Pinky.getLastX()] = "  ";
    // map[Inky.getLastY()][Inky.getLastX()] = "  ";
    // map[Clyde.getLastY()][Clyde.getLastX()] = "  ";

    map[8][9] = "=="; // why tis here help, ;This is here so that when ghost cross it, it wont be replaced by blank space
    map[8][10] = "==";

    // updating position of Pacman
    if (Pacman.getFaceDirection() == 1){
        map[Pacman.getY()][Pacman.getX()] = "(<"; // Pacman is facing right
    } else {
        map[Pacman.getY()][Pacman.getX()] = ">)"; // Pacman is facing left
    }

    // updating positions of ghosts
    map[Blinky.getY()][Blinky.getX()] = "[]";
    map[Pinky.getY()][Pinky.getX()] = "()";
    map[Inky.getY()][Inky.getX()] = "{}";
    map[Clyde.getY()][Clyde.getX()] = "<>";
    // attron(COLOR_PAIR(1));

    // prints the actual map
    attron(COLOR_PAIR(1));
    for (int i = 0; i < 19; i++) 
    {
            for (int j = 0; j < 20; j++) {
                    if (i == Blinky.getY() && j == Blinky.getX()) {
                        if (Blinky.getCurrentState() == 0 || Blinky.getCurrentState() == 1){
                            attron(COLOR_PAIR(3));
                        } else if (Blinky.getCurrentState() == 2){
                            attron(COLOR_PAIR(8));
                        } else if (Blinky.getCurrentState() == 3){
                            attron(COLOR_PAIR(1));
                        }
                    } else if (i == Pinky.getY() && j == Pinky.getX()) {
                        if (Pinky.getCurrentState() == 0 || Pinky.getCurrentState() == 1){
                            attron(COLOR_PAIR(4));
                        } else if (Pinky.getCurrentState() == 2){
                            attron(COLOR_PAIR(8));
                        } else if (Pinky.getCurrentState() == 3){
                            attron(COLOR_PAIR(1));
                        }
                    } else if (i == Inky.getY() && j == Inky.getX()) {
                        if (Inky.getCurrentState() == 0 || Inky.getCurrentState() == 1){
                            attron(COLOR_PAIR(5));
                        } else if (Inky.getCurrentState() == 2){
                            attron(COLOR_PAIR(8));
                        } else if (Inky.getCurrentState() == 3){
                            attron(COLOR_PAIR(1));
                        }
                    } else if (i == Clyde.getY() && j == Clyde.getX()) {
                        if (Clyde.getCurrentState() == 0 || Clyde.getCurrentState() == 1){
                            attron(COLOR_PAIR(6));
                        } else if (Clyde.getCurrentState() == 2){
                            attron(COLOR_PAIR(8));
                        } else if (Clyde.getCurrentState() == 3){
                            attron(COLOR_PAIR(1));
                        }
                    } else if (i == Pacman.getY() && j == Pacman.getX()) {
                        attron(COLOR_PAIR(2));
                    }
                    addch(map[i][j][0]);
                    addch(map[i][j][1]);
                    attron(COLOR_PAIR(1));
            }
            move(++yCursor, xCursor); //Moves the cursor position to a new line!
    }

    // // state bug tester
    // mvaddch(0,0,char(Blinky.getCurrentState()+ '0'));
    // mvaddch(0,1,char(Pinky.getCurrentState()+ '0'));
    // mvaddch(0,2,char(Inky.getCurrentState()+ '0'));
    // mvaddch(0,3,char(Clyde.getCurrentState()+ '0'));
    attroff(COLOR_PAIR(1));
    refresh(); //Print output to window "stdscr"
}

void input(int& direction){ // wasdq = 12345
    char ch = getch();
    switch(ch){
            case 'w':
            direction = 1;
            break;
            case 'a':
            direction = 2;
            break;
            case 's':
            direction = 3;
            break;
            case 'd':
            direction = 4;
            break;
            case 'q':
            direction = 5;
            break;
    }
}

int haveCollided(Pacman &Pacman, Ghost &Blinky, Ghost &Pinky, Ghost &Inky, Ghost &Clyde){
/*  Checks if pacman has collided with either of the ghosts; the return value depends on what Pacman has collided with.
    0: No collision, 1: Blinky, 2: Pinky, 3: Inky, 4: Clyde */
    if (((Pacman.getX() == Blinky.getX()) && (Pacman.getY() == Blinky.getY())) || ((Pacman.getLastX() == Blinky.getX() && Pacman.getLastY() == Blinky.getY()) 
    && (Pacman.getX() == Blinky.getLastX() && Pacman.getY() == Blinky.getLastY()))){
        return 1;
    } else if (((Pacman.getX() == Pinky.getX()) && (Pacman.getY() == Pinky.getY())) || ((Pacman.getLastX() == Pinky.getX() && Pacman.getLastY() == Pinky.getY()) 
    && (Pacman.getX() == Pinky.getLastX() && Pacman.getY() == Pinky.getLastY()))){
        return 2;
    } else if (((Pacman.getX() == Inky.getX()) && (Pacman.getY() == Inky.getY())) || ((Pacman.getLastX() == Inky.getX() && Pacman.getLastY() == Inky.getY()) 
    && (Pacman.getX() == Inky.getLastX() && Pacman.getY() == Inky.getLastY()))){
        return 3;
    } else if (((Pacman.getX() == Clyde.getX()) && (Pacman.getY() == Clyde.getY())) || ((Pacman.getLastX() == Clyde.getX() && Pacman.getLastY() == Clyde.getY()) 
    && (Pacman.getX() == Clyde.getLastX() && Pacman.getY() == Clyde.getLastY()))){
        return 4;
    } else {
        return 0;
    }
}

bool uponCollision(Ghost &lost, int &score){ // handles actions upon collision; returns "quit" value
    if (lost.getCurrentState() == 0 || lost.getCurrentState() == 1){ // Normal/Scatter mode
        // game over screen (+ score if applicable)
        return true;
    } else if (lost.getCurrentState() == 2) { // Frightened mode
        lost.setPotentialState(3); // sets ghost to eaten mode
        score += 300;
    }
    // Eaten mode is ignored because there is no effect
    return false;
}

int gameplay(){
    // Screen Settings
    initscr();
    start_color();
    if(can_change_color()) {
        init_color(COLOR_BLACK,0,0,0);
        init_color(COLOR_CYAN,0,0,888);
        init_color(COLOR_GREEN,0,888,666);
        init_color(COLOR_RED,888,0,0);
    }

    // colour init
    //background colur
    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    //pacman colour
    init_pair(2,COLOR_YELLOW,COLOR_BLACK);
    //Blinky colour
    init_pair(3,COLOR_RED,COLOR_BLACK);
    //Pinky colour
    init_pair(4,COLOR_MAGENTA,COLOR_BLACK);
    //Inky colour
    init_pair(5,COLOR_BLUE,COLOR_BLACK);
    //Clyde colour
    init_pair(7,COLOR_GREEN,COLOR_BLACK);
    //Ghost frighten mode colour
    init_pair(8,COLOR_WHITE,COLOR_BLACK);
    //colour for the frame
    init_pair(9,COLOR_GREEN,COLOR_GREEN);


    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    // Game Startup
    int xMax, yMax;
    string map[19][20] = { //y max = 18, x max = 19
        {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
        {"##","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","##"},
        {"##","''","''","##","''","''","''","##","##","''","''","##","##","''","''","''","##","''","''","##"},
        {"##","||","##","##","''","##","''","''","##","''","''","##","''","''","##","''","##","##","||","##"},
        {"##","''","''","##","''","##","''","''","##","''","''","##","''","''","##","''","##","''","''","##"},
        {"##","''","''","##","''","''","''","''","##","''","''","##","''","''","''","''","##","''","''","##"},
        {"##","''","''","''","''","''","''","##","##","''","''","##","##","''","''","''","''","''","''","##"},
        {"##","##","''","##","##","##","''","''","''","''","''","''","''","''","##","##","##","''","##","##"},
        {"  ","''","''","''","''","''","''","##","##","==","==","##","##","''","''","''","''","''","''","  "},
        {"##","''","##","''","##","''","''","##","  ","  ","  ","  ","##","''","''","##","''","##","''","##"},
        {"##","''","##","''","##","''","''","##","  ","  ","  ","  ","##","''","''","##","''","##","''","##"},
        {"##","''","##","''","##","''","''","##","##","##","##","##","##","''","''","##","''","##","''","##"},
        {"##","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","##"},
        {"##","''","''","##","''","##","##","''","##","##","##","##","''","##","##","''","##","''","''","##"},
        {"##","||","''","##","''","''","''","''","''","''","''","''","''","''","''","''","##","''","||","##"},
        {"##","''","##","##","''","''","##","##","##","''","''","##","##","##","''","''","##","##","''","##"},
        {"##","''","''","##","''","''","##","##","##","''","''","##","##","##","''","''","##","''","''","##"},
        {"##","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","''","##"},
        {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"}
    };
    vector<vector<string>>vecmap = {vector<string>(begin(map[0]), end(map[0])), //2D vectir conversion of the 2D string map
						vector<string>(begin(map[1]), end(map[1])),
						vector<string>(begin(map[2]), end(map[2])),
						vector<string>(begin(map[3]), end(map[3])),
						vector<string>(begin(map[4]), end(map[4])),
						vector<string>(begin(map[5]), end(map[5])),
						vector<string>(begin(map[6]), end(map[6])),
						vector<string>(begin(map[7]), end(map[7])),
						vector<string>(begin(map[8]), end(map[8])),
						vector<string>(begin(map[9]), end(map[9])),
						vector<string>(begin(map[10]), end(map[10])),
						vector<string>(begin(map[11]), end(map[11])),
						vector<string>(begin(map[12]), end(map[12])),
						vector<string>(begin(map[13]), end(map[13])),
						vector<string>(begin(map[14]), end(map[14])),
						vector<string>(begin(map[15]), end(map[15])),
						vector<string>(begin(map[16]), end(map[16])),
						vector<string>(begin(map[17]), end(map[17])),
						vector<string>(begin(map[18]), end(map[18]))};
    bool quit = false;
    int eatenghosts = 0, powerPelletTime = 0, internalTimer = 0, scatterTimer = 0, roll = 0, score = 0;
    // powerPelletTime is the timer for power pellets to control how long they last for
    // internalTimer is the timer for how long the game has been running for
    // scatterTimer is the timer to track how long scatter state is
    // roll is for random roll for scatter() implementation
    
    // Character Startup
    int x = 2, y = 13; // initial pos of pacman; keeps track of pacman's x and y
    Pacman Pacman(x, y); // x = 2, y = 13
    Ghost Blinky(4, 5, "Blinky"); // x = 4, y = 5
    Ghost Pinky(18, 6, "Pinky");
    Ghost Inky(1, 8, "Inky");
    Ghost Clyde(18, 17, "Clyde");
    int direction = 4, collisionStatus = 0;

    display(Pacman, Blinky, Pinky, Inky, Clyde, map);
    // getch() || Usleep()
    while (!quit) {
        input(direction);
        
        // update position of Pacman
        switch (direction) {
            case 1: //up
                if (y > 1 && map[y-1][x]!="##") {y--;}
                break;
            case 2: //left
                if (x > 1 && map[y][x-1]!="##") {x--;}
                else if ( x <= 1 && y == 8) //used for Pac-Man Looping
                {
                    x--;
                    if (x == -1)
                    {
                        x = 19;
                    }
                } 
                break;
            case 3: //down
                if (y < 17 && map[y+1][x]!="##" && map[y+1][x]!="==") {y++;}
                break;
            case 4: //right
                if (x < 18 && map[y][x+1]!="##") {x++;}
                else if (x >= 18 && y == 8) //used for Pac-Man Looping
                {
                    x++;
                    if (x == 20)
                    {
                        x = 0;
                    }
                } 
                break;
            case 5:
                quit = true;
        }
        if (quit) {
            break;
        }

        // handles collisions (Normal >> Game over >> Break/game over || Frightened >> Eaten mode)
        collisionStatus = haveCollided(Pacman, Blinky, Pinky, Inky, Clyde);
        switch (collisionStatus){
            case 1: // Collision with Blinky
                quit = uponCollision(Blinky, score);
                map[0][0] = to_string(Blinky.getPotentialState()) + "0";
                break;
            case 2: // Collision with Pinky
                quit = uponCollision(Pinky, score);
                break;
            case 3: // Collision with Inky
                quit = uponCollision(Inky, score);
                break;
            case 4: // Collision with Clyde
                quit = uponCollision(Clyde, score);
                break;
        }
        if (quit) {
            break;
        }

        Pacman.updatePosition(x, y);
        Pacman.toggleFaceDirection();

        if (map[Pacman.getY()][Pacman.getX()] == "''")
        {
            Blinky.emptyMap(Pacman.getX(), Pacman.getY());
            Pinky.emptyMap(Pacman.getX(), Pacman.getY());
            Inky.emptyMap(Pacman.getX(), Pacman.getY());
            Clyde.emptyMap(Pacman.getX(), Pacman.getY());
            score += 20; // points for staying alive
        }
        else if (map[Pacman.getY()][Pacman.getX()] == "||")
        {
            Blinky.emptyMap(Pacman.getX(), Pacman.getY());
            Pinky.emptyMap(Pacman.getX(), Pacman.getY());
            Inky.emptyMap(Pacman.getX(), Pacman.getY());
            Clyde.emptyMap(Pacman.getX(), Pacman.getY());
            powerPelletTime++;
            score += 100;
        }

        //scatter mode implementation
        if (scatterTimer % 30 == 0 && scatterTimer != 0){ // Ghosts returns to chase mode
            if (Blinky.getPotentialState() == 1){
                Blinky.toggleCurrentDirection();
                Blinky.setPotentialState(0);
            }
            if (Pinky.getPotentialState() == 1){
                Pinky.toggleCurrentDirection();
                Pinky.setPotentialState(0);
            }
            if (Inky.getPotentialState() == 1){
                Inky.toggleCurrentDirection();
                Inky.setPotentialState(0);
            }
            if (Clyde.getPotentialState() == 1){
                Clyde.toggleCurrentDirection();
                Clyde.setPotentialState(0);
            }
        }
        if ((internalTimer % 90) == 0 && internalTimer != 0){ //Ghosts switch to scatter mode
            roll = rand() % 4;
            if (roll == 0 && Blinky.getPotentialState() <= 1){
                Blinky.toggleCurrentDirection();
                Blinky.setPotentialState(1);
            } else if (roll == 1 && Pinky.getPotentialState() <= 1){
                Pinky.toggleCurrentDirection();
                Pinky.setPotentialState(1);
            } else if (roll == 2 && Inky.getPotentialState() <= 1){
                Inky.toggleCurrentDirection();
                Inky.setPotentialState(1);
            } else if (roll == 3 && Clyde.getPotentialState() <= 1){
                Clyde.toggleCurrentDirection();
                Clyde.setPotentialState(1);
            }
        }
        scatterTimer++;

        // handle if power pellet consumed (handle entering and staying in frightened mode)
        if (powerPelletTime == 1){ // stage 1 of power pellet
            Blinky.toggleCurrentDirection();
            Blinky.setPotentialState(2);
            Pinky.toggleCurrentDirection();
            Pinky.setPotentialState(2);
            Inky.toggleCurrentDirection();
            Inky.setPotentialState(2);
            Clyde.toggleCurrentDirection();
            Clyde.setPotentialState(2);
            ++powerPelletTime;
        } else if (powerPelletTime > 1 && powerPelletTime < 30){ // stage 2 and up of power pellet
            powerPelletTime++;
            if (Blinky.getPotentialState() == 2){ // getPotentialState instead cause could be alr eatens
                Blinky.setPotentialState(2);
            }
            else if (Blinky.getPotentialState() == 0)
            {
                Blinky.setPotentialState(0);
            }
            if (Pinky.getPotentialState() == 2){
                Pinky.setPotentialState(2);
            }
            else if (Pinky.getPotentialState() == 0)
            {
                Pinky.setPotentialState(0);
            }
            if (Inky.getPotentialState() == 2){
                Inky.setPotentialState(2);
            }
            else if (Inky.getPotentialState() == 0)
            {
                Inky.setPotentialState(0);
            }
            if (Clyde.getPotentialState() == 2){
                Clyde.setPotentialState(2);
            }
            else if (Clyde.getPotentialState() == 0)
            {
                Clyde.setPotentialState(0);
            }
        } else if (powerPelletTime >= 30){
            powerPelletTime = 0;
            if (Blinky.getPotentialState() == 2){ // getPotentialState instead cause could be alr eaten
                Blinky.setPotentialState(0);
            }
            if (Pinky.getPotentialState() == 2){
                Pinky.setPotentialState(0);
            }
            if (Inky.getPotentialState() == 2){
                Inky.setPotentialState(0);
            }
            if (Clyde.getPotentialState() == 2){
                Clyde.setPotentialState(0);
            }
        }
        
        // update position of ghost
        switch(Blinky.getPotentialState()){
            case 0: // Normal/Chase mode
                Blinky.chase(Pacman.getX(), Pacman.getY(), Blinky.getX(), Blinky.getY(), direction);
                break;
            case 1: // Scatter mode
                Blinky.scatter();
                break;
            case 2: // Frightened mode
                Blinky.frightened();
                break;
            case 3: // Eaten mode
                Blinky.eaten();
                break;
        }
        switch(Pinky.getPotentialState()){
            case 0: // Normal/Chase mode
                Pinky.chase(Pacman.getX(), Pacman.getY(), Blinky.getX(), Blinky.getY(), direction);
                break;
            case 1: // Scatter mode
                Pinky.scatter();
                break;
            case 2: // Frightened mode
                Pinky.frightened();
                break;
            case 3: // Eaten mode
                Pinky.eaten();
                break;
        }
        switch(Inky.getPotentialState()){
            case 0: // Normal/Chase mode
                Inky.chase(Pacman.getX(), Pacman.getY(), Blinky.getX(), Blinky.getY(), direction);
                break;
            case 1: // Scatter mode
                Inky.scatter();
                break;
            case 2: // Frightened mode
                Inky.frightened();
                break;
            case 3: // Eaten mode
                Inky.eaten();
                break;
        }
        switch(Clyde.getPotentialState()){
            case 0: // Normal/Chase mode
                Clyde.chase(Pacman.getX(), Pacman.getY(), Blinky.getX(), Blinky.getY(), direction);
                break;
            case 1: // Scatter mode
                Clyde.scatter();
                break;
            case 2: // Frightened mode
                Clyde.frightened();
                break;
            case 3: // Eaten mode
                Clyde.eaten();
                break;
        }

        display(Pacman, Blinky, Pinky, Inky, Clyde, map);
        // Sleep(250);
        usleep(300000); // use this for linux
    }
    return score;
}

int main()
{
    string name="Guest-Player";
    int highscore=0;
    int score=0;
    int startgame = 0;
    startgame = StartingSequence();

    // Game Flow
    while (startgame != 7){ // Quit the Game
        clear();
        if (startgame == 1) { // Play the Game
            score = gameplay();
            clear();
            GameOver(score);
            clear();
            CheckScore(score, highscore);  //Check if score exceeded previous highest score record
            usleep(300000);
        } else if (startgame == 2) { // Load Saves
            loadprofile(highscore, name);
        } else if (startgame == 3) { // How to Play
            howToPlay();
        } else if (startgame == 4) { // Load Statistics
            loadStatistics(score, name, highscore);
        } else if (startgame == 5) { // Export Player Profile
            exportprofile(highscore, name);
	} else if (startgame == 6) { // Change Playername
            changename(name);
        }
        clear();
        startgame = StartingSequence();
    }

    clear();
    EndingSequence();
    
    getch();
    endwin();

    return 0;
}
