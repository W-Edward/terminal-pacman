// #include <ncurses.h>
#include <curses.h>
// #include <windows.h>
#include <unistd.h> //replace w windows.h for linux
#include <iostream>
#include <string>
#include <stdio.h>
#include "entities.h"
#include "StartnEndSequence.h"
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
    xCursor = (xMax/2)-20;
    yCursor = (yMax/2)-20;
    move(yCursor, xCursor);

    // erasing the old Pacman and ghosts
    map[Pacman.getLastY()][Pacman.getLastX()] = "  ";
    map[Blinky.getLastY()][Blinky.getLastX()] = "  ";
    map[Pinky.getLastY()][Pinky.getLastX()] = "  ";
    map[Inky.getLastY()][Inky.getLastX()] = "  ";
    map[Clyde.getLastY()][Clyde.getLastX()] = "  ";
    map[8][9] = "=="; // why tis here help
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
                    if (i == Pacman.getY() && j == Pacman.getX()) {
                        attron(COLOR_PAIR(2));
                    } else if (i == Blinky.getY() && j == Blinky.getX()) {
                        switch (Blinky.getCurrentState())
                        {
                        case 0:
                            attron(COLOR_PAIR(3));
                        
                        case 1:
                            attron(COLOR_PAIR(3));

                        case 2:
                            //frighten colour
                            attron(COLOR_PAIR(7));

                        case 3:
                            //eaton colour
                            attron(COLOR_PAIR(8));
                        
                        default:
                            attron(COLOR_PAIR(3));
                            break;
                        }
                    } else if (i == Pinky.getY() && j == Pinky.getX()) {
                        switch (Blinky.getCurrentState())
                        {
                        case 0:
                            attron(COLOR_PAIR(4));
                        
                        case 1:
                            attron(COLOR_PAIR(4));

                        case 2:
                            //frighten colour
                            attron(COLOR_PAIR(7));

                        case 3:
                            //eaton colour
                            attron(COLOR_PAIR(8));
                        
                        default:
                            attron(COLOR_PAIR(4));
                            break;
                        }
                    } else if (i == Inky.getY() && j == Inky.getX()) {
                        switch (Blinky.getCurrentState())
                        {
                        case 0:
                            attron(COLOR_PAIR(5));
                        
                        case 1:
                            attron(COLOR_PAIR(5));

                        case 2:
                            //frighten colour
                            attron(COLOR_PAIR(7));

                        case 3:
                            //eaton colour
                            attron(COLOR_PAIR(8));
                        
                        default:
                            attron(COLOR_PAIR(5));
                            break;
                        }
                    } else if (i == Clyde.getY() && j == Clyde.getX()) {
                        switch (Blinky.getCurrentState())
                        {
                        case 0:
                            attron(COLOR_PAIR(6));
                        
                        case 1:
                            attron(COLOR_PAIR(6));

                        case 2:
                            //frighten colour
                            attron(COLOR_PAIR(7));

                        case 3:
                            //eaton colour
                            attron(COLOR_PAIR(8));
                        
                        default:
                            attron(COLOR_PAIR(6));
                            break;
                        }
                    }
                    addch(map[i][j][0]);
                    addch(map[i][j][1]);
                    attron(COLOR_PAIR(1));
            }
            move(++yCursor, xCursor); //Moves the cursor position to a new line!
    }
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

bool haveCollided(Pacman &Pacman, Ghost &Blinky, Ghost &Pinky, Ghost &Inky, Ghost &Clyde){
/*  Checks if pacman has collided with either of the ghosts; the return value depends on what Pacman has collided with.
    0: No collision, 1: Blinky, 2: Pinky, 3: Inky, 4: Clyde */
    if ((Pacman.getX() == Blinky.getX()) && (Pacman.getY() == Blinky.getY())){
        return 1;
    } else if ((Pacman.getX() == Pinky.getX()) && (Pacman.getY() == Pinky.getY())){
        return 2;
    } else if ((Pacman.getX() == Inky.getX()) && (Pacman.getY() == Inky.getY())){
        return 3;
    } else if ((Pacman.getX() == Clyde.getX()) && (Pacman.getY() == Clyde.getY())){
        return 4;
    } else {
        return 0;
    }
}

bool uponCollision(Ghost &Ghost){ // handles actions upon collision; returns "quit" value
    if (Ghost.getCurrentState() == 0 || Ghost.getCurrentState() == 1){ // Normal/Scatter mode
        // game over screen (+ score if applicable)
        return true;
    } else if (Ghost.getCurrentState() == 2) { // Frightened mode
        Ghost.eaten();
    }
    // Eaten mode is ignored because there is no effect
    return false;
}

int main()
{
    // Screen Settings
    initscr();
    start_color();
    if(can_change_color()) {
        init_color(COLOR_BLACK,0,0,0);
        init_color(COLOR_CYAN,0,0,888);
    }
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
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    // Game Startup
    int xMax, yMax;
    string map[19][20] = { //y max = 18, x max = 19
        {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","  ","  ","##","  ","  ","  ","##","##","  ","  ","##","##","  ","  ","  ","##","  ","  ","##"},
        {"##","  ","##","##","  ","##","  ","  ","##","  ","  ","##","  ","  ","##","  ","##","##","  ","##"},
        {"##","  ","  ","##","  ","##","  ","  ","##","  ","  ","##","  ","  ","##","  ","##","  ","  ","##"},
        {"##","  ","  ","##","  ","  ","  ","  ","##","  ","  ","##","  ","  ","  ","  ","##","  ","  ","##"},
        {"##","  ","  ","  ","  ","  ","  ","##","##","  ","  ","##","##","  ","  ","  ","  ","  ","  ","##"},
        {"##","##","  ","##","##","##","  ","  ","  ","  ","  ","  ","  ","  ","##","##","##","  ","##","##"},
        {"  ","  ","  ","  ","  ","  ","  ","##","##","==","==","##","##","  ","  ","  ","  ","  ","  ","  "},
        {"##","  ","##","  ","##","  ","  ","##","  ","  ","  ","  ","##","  ","  ","##","  ","##","  ","##"},
        {"##","  ","##","  ","##","  ","  ","##","  ","  ","  ","  ","##","  ","  ","##","  ","##","  ","##"},
        {"##","  ","##","  ","##","  ","  ","##","##","##","##","##","##","  ","  ","##","  ","##","  ","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","  ","  ","##","  ","##","##","  ","##","##","##","##","  ","##","##","  ","##","  ","  ","##"},
        {"##","  ","  ","##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##","  ","  ","##"},
        {"##","  ","##","##","  ","  ","##","##","##","  ","  ","##","##","##","  ","  ","##","##","  ","##"},
        {"##","  ","  ","##","  ","  ","##","##","##","  ","  ","##","##","##","  ","  ","##","  ","  ","##"},
        {"##","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","##"},
        {"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"}
    };
    bool quit = false;
    int startgame = 0;
    int eatenghosts = 0;
    int score=0;
    
    // Character Startup
    int x = 2, y = 13; // initial pos of pacman; keeps track of pacman's x and y
    Pacman Pacman(x, y); // x = 2, y = 13
    Ghost Blinky(4, 5, "Blinky"); // x = 4, y = 5
    Ghost Pinky(18, 6, "Pinky");
    Ghost Inky(1, 8, "Inky");
    Ghost Clyde(18, 17, "Clyde");
    int direction = 4, collisionStatus = 0;

    startgame = StartingSequence();
    clear();

    // Game Flow
    if (startgame == 1 || startgame == 2) {
        display(Pacman, Blinky, Pinky, Inky, Clyde, map);
        // getch() || usleep()
        while (!quit) {
            input(direction);
            
            // update position of Pacman
            switch (direction) {
            case 1:
                if (y > 1 && map[y-1][x]!="##") {y--;}
                break;
            case 2:
                if (x > 1 && map[y][x-1]!="##") {x--;}
                else if ( x <= 1 && y == 8) //used for Pac-Man Looping
                {
                    x--;
                    if (x == -1)
                    {
                        x = 19;
                    }
                } 
                Pacman.toggleFaceDirection();
                break;
            case 3:
                if (y < 17 && map[y+1][x]!="##" && map[y+1][x]!="==") {y++;}
                break;
            case 4:
                if (x < 18 && map[y][x+1]!="##") {x++;}
                else if (x >= 18 && y == 8) //used for Pac-Man Looping
                {
                    x++;
                    if (x == 20)
                    {
                        x = 0;
                    }
                } 
                Pacman.toggleFaceDirection();
                break;
            case 5:
                quit = true;
        }
            Pacman.updatePosition(x, y);

            // handles collisions (Normal >> Game over >> Break/game over || Frightened >> Eaten mode)
            collisionStatus = haveCollided(Pacman, Blinky, Pinky, Inky, Clyde);
            switch (collisionStatus){
                case 1: // Collision with Blinky
                    quit = uponCollision(Blinky);
                    break;
                case 2: // Collision with Pinky
                    quit = uponCollision(Pinky);
                    break;
                case 3: // Collision with Inky
                    quit = uponCollision(Inky);
                    break;
                case 4: // Collision with Clyde
                    quit = uponCollision(Clyde);
                    break;
            }

            // handle if power pellet consumed (handle entering and staying in frightened mode)
            int powerPelletConsumed = 0; // temp variable to be replaced
            if (powerPelletConsumed){ // stage 1 of power pellet
                Blinky.toggleCurrentDirection();
                Blinky.frightened();
                Pinky.toggleCurrentDirection();
                Pinky.frightened();
                Inky.toggleCurrentDirection();
                Inky.frightened();
                Clyde.toggleCurrentDirection();
                Clyde.frightened();
            } else if (powerPelletConsumed){ // stage 2 and up of power pellet
                if (Blinky.getCurrentState() == 2){
                    Blinky.frightened();
                }
                if (Pinky.getCurrentState() == 2){
                    Pinky.frightened();
                }
                if (Inky.getCurrentState() == 2){
                    Inky.frightened();
                }
                if (Clyde.getCurrentState() == 2){
                    Clyde.frightened();
                }
            }

            // update position of ghost
            switch(Blinky.getCurrentState()){
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

            display(Pacman, Blinky, Pinky, Inky, Clyde, map);
            // Sleep(250);
            usleep(250000); // use this for linux
        }
    } else if (startgame == 3) {
        // load game statistics
    } // startgame == 4 >> Ending sequence

    clear();

    EndingSequence(score);
    
    getch();
    endwin();

    return 0;
}