#include <string>
#include <curses.h>
#include <cmath>
#include "entities.h"
using namespace std;

//Notes:
//Ghost should never turn around unless when changing states

// tempa[y][x]
string tempa[19][20] = { // ref of map; 19 rows, 20 columnns; y refers to the row it is on, x refers to the column it is on
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

int Ghost::findOppositeDirection(int currentDir) // finds the opposite direction of the direction the ghost is facing
{
    int direction = (currentDir+2)%4;
    if (direction == 0)
    {
        direction = 4;
    }
    return direction;
}

Ghost::Ghost(int posX, int posY, string ghostName) // initializes the ghosts' information
{
    x = posX;
    y = posY;
    name = ghostName;
    currentDirection = 2; //1 is up, 2 is left, 3 is down and 4 is right
    isFrightened = false; // checks if ghost is in frightened state
    isEaten = false; // checks if ghost is in eaten state
}

void Ghost::chaseTargetTile(int targetX, int targetY)
/*  this function will update ghosts' position linearly towards the target tile. Ghosts cannot move backwards unless when changing modes and follows the following
    move priority if more than one options are available (same linear distance to target tile): up, left, down, right. */
{
    int availableDirections[4] = {4, 3, 2, 1}; //According to the priority list for ghost movement! 

    double shortestDistance = 1e5;
    double distance = 0;
    int originalDirection = currentDirection;
    for (int i = 0; i < 4; i++)
    {
        int tempX = x, tempY = y;
        if (availableDirections[i] == 1 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[--tempY][tempX] != "##")
        {
            distance = sqrt( pow( (tempX-targetX) , 2 ) + pow( (tempY-targetY) , 2 )); //Linear Distance formula
            if (distance <= shortestDistance) 
            {
                shortestDistance = distance;
                currentDirection = availableDirections[i];
            }
        }
        else if (availableDirections[i] == 2 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[tempY][--tempX] != "##")
        {
            distance = sqrt( pow( (tempX-targetX) , 2 ) + pow( (tempY-targetY) , 2 )); //Linear Distance formula
            if (distance <= shortestDistance) 
            {
                shortestDistance = distance;
                currentDirection = availableDirections[i];
            }
        }
        else if (availableDirections[i] == 3 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[++tempY][tempX] != "##" && tempa[tempY][tempX] != "==")
        {
            distance = sqrt( pow( (tempX-targetX) , 2 ) + pow( (tempY-targetY) , 2 )); //Linear Distance formula
            if (distance <= shortestDistance) 
            {
                shortestDistance = distance;
                currentDirection = availableDirections[i];
            }
        }
        else if (availableDirections[i] == 4 && availableDirections[i] != findOppositeDirection(originalDirection) && tempa[tempY][++tempX] != "##")
        {
            distance = sqrt( pow( (tempX-targetX) , 2 ) + pow( (tempY-targetY) , 2 )); //Linear Distance formula
            if (distance <= shortestDistance) 
            {
                shortestDistance = distance;
                currentDirection = availableDirections[i];
            }
        }
    }

    switch (currentDirection)
    {
        case 1:
            y--;
            break;
        case 2:
            x--;
            //Handles Looping
            if (x == -1)
            {
                x = 19;
            }
            break;
        case 3:
            y++;
            break;
        case 4:
            x++;
            //Handles Looping
            if (x == 20)
            {
                x = 0;
            }
            break;
    }
}

void Ghost::scatter()
/*  scatter state pathfinding (crucial such that ghosts arent hunting pacman 24/7)
    This function updates the ghost so they target their respective corner tiles of the map while in this state */
{
    if (name == "Blinky")
    //Goes to top right direction
    {
        chaseTargetTile(18, 21);
    }

    else if (name == "Pinky")
    {
    //Goes to top left direction
        chaseTargetTile(1, 21);
    }

    else if (name == "Inky")
    {
    //Goes to bottom right direction
        chaseTargetTile(19, 20);
    }

    else if (name == "Clyde")
    {
    //Goes to bottom left direction
        chaseTargetTile(0, 20);
    }

}

void Ghost::chase(int playerPosX, int playerPosY, int blinkyPosX, int blinkyPosY, int direction) 
/*playerPosX and Y are Pac-Man's X and Y Coordinates, direction is Pac-Man's current direction, blinkyPosX and blinkyPosY are x and y positions of Blinky.
This function updates x and y coordinates + currentDirection of ghosts in chase mode */
{
    //Implementation to update posX and posY every frame to chase Pac-Man

    if (name == "Blinky")
    //Blinky chases Pac-Man directly (linearly)
    {
        chaseTargetTile(playerPosX, playerPosY);
    }

    else if (name == "Pinky") 
    /*Pinky chases the tile that is 4 tiles in front of Pac-Man's direction (exception when Pac-Man is facing 'up', in that case pinky chases 4 tiles in front +
    4 tiles to the left of Pac-Man )*/
    {
        int target[2];

        //Pinky determines target tile here

        if (direction == 1)
        {
            target[0] = playerPosX - 4;
            target[1] = playerPosY + 4;
        }
        else if (direction == 2)
        {
            target[0] = playerPosX - 4;
            target[1] = playerPosY;
        }
        else if (direction == 3)
        {
            target[0] = playerPosX;
            target[1] = playerPosY - 4;
        }
        else if (direction == 4)
        {
            target[0] = playerPosX + 4;
            target[1] = playerPosY;
        }
        else //just in case there is undefined behaviour
        {
            target[0] = playerPosX;
            target[1] = playerPosY;
        }
        
        chaseTargetTile(target[0], target[1]);   
    }
    
    else if (name == "Inky")
    /*Inky chases the tile that is rotated 180 degrees from Blinky's tile position around
    Point A: tile that is 2 tiles ahead of Pac-Man except 'up' direction, which is 2 tiles ahead and 2 tiles left.
    Let's call Blinky's position Point B and target tile Point C.*/
    {
        int pointA[2];

        if (direction == 1)
        {
            pointA[0] = playerPosX - 2;
            pointA[1] = playerPosY + 2;
        }
        else if (direction == 2)
        {
            pointA[0] = playerPosX - 2;
            pointA[1] = playerPosY;
        }
        else if (direction == 3)
        {
            pointA[0] = playerPosX;
            pointA[1] = playerPosY - 2;
        }
        else if (direction == 4)
        {
            pointA[0] = playerPosX + 2;
            pointA[1] = playerPosY;
        }
        else //just in case there is undefined behaviour
        {
            pointA[0] = playerPosX;
            pointA[1] = playerPosY;
        }

        int pointC[2];
        //rotate point B around point A 180 degrees to get point C
        pointC[0] = -(blinkyPosX - pointA[0]) + pointA[0];
        pointC[1] = -(blinkyPosY - pointA[1]) + pointA[1];

        chaseTargetTile(pointC[0], pointC[1]);
    }
    else if (name == "Clyde")
    //Clyde behaves similarly to Blinky but if Clyde is 8 tiles or closer to Pac-Man, he will turn to scatter mode.
    {
        if (sqrt( pow( (x-playerPosX) , 2 ) + pow( (y-playerPosY) , 2 )) <= 8)
        {
            //algo for scatter mode (bottomleft)
            scatter();
        } 
        else
        {
            chaseTargetTile(playerPosX, playerPosY);
        }
    }
}

void Ghost::frightened() // frightened mode movement and pathfinding
{
    isFrightened = true;
    // add these codes when pacman touches power pellet, outside this function
    // isFrightened = true;
    // currentDirection = findOppositeDirection(currentDirection);
    // frightened();

    // always have this between:
    // if (Ghost::isFrightened){Ghost::frightened();}

    // add these codes when power pellet is used up
    // isFrightened = false;

    // notes: If when debugging, ghosts always go back to unfrightened after one time frame, check line 48 of ghost.cpp
    // also consider adding a visual of whenever ghosts are in frightened mode, and a pre-exist frightened mode visual thign


    // check directions that are "  "
    int availableDirections[4] = {1, 2, 3, 4}; // = up, left, down, right
    if (tempa[y-1][x] != "  "){availableDirections[0] = -1;} // up
    if (tempa[y+1][x] != "  "){availableDirections[0] = -1;} // down
    
    // checks if ghost is on the edge of the map and handles looping for direction checking
    if (x==0){
        if (tempa[y][19] != "  "){availableDirections[0] = -1;} // left
        if (tempa[y][x+1] != "  "){availableDirections[0] = -1;} // right
    } else if (x==19){
        if (tempa[y][x-1] != "  "){availableDirections[0] = -1;} // left
        if (tempa[y][0] != "  "){availableDirections[0] = -1;} // right
    } else {
        if (tempa[y][x-1] != "  "){availableDirections[0] = -1;} // left
        if (tempa[y][x+1] != "  "){availableDirections[0] = -1;} // right
    }

    // block off opposite direction since ghosts cant walk backwards
    int oppDirection = findOppositeDirection(currentDirection);
    availableDirections[oppDirection-1] = -1;

    // roll a random direction that isn't blocked off
    int roll = rand() % 4;
    while (availableDirections[roll] == -1){roll = rand() % 4;}
    
    switch (availableDirections[roll]){
        case 1:
            x--;
            break;
        case 2:
            y--;
            break;
        case 3:
            x++;
            break;
        case 4:
            y++;
            break;
    }
}

void Ghost::eaten()
{
    // Remember to isEaten = true; after pacman touches the ghost
    // then if (isEaten){eaten();}

    // notes: If when debugging, ghosts always go back to uneaten after one time frame, check line 49 of ghost.cpp
    // ghosts cannot interact with pacman in this state. Remember to check the eaten flag every time upon interaction
    // Implement eaten visual

    if ((x == 7 && y == 9) || (x == 8 && y == 9)){ // ghost should enter ghost house here
        chaseTargetTile(9, 9);
    } else if (x == 9 && y == 9){ // ghost is inside ghost house; exit frightened mode and go back to chase mode here
        isFrightened = false;
        isEaten = false;
        // should be able to return to chase mode after this
    } else {
        chaseTargetTile(7, 9); // chase the tile directly in front of the ghost gate
    }
}

void Ghost::escape()
{
    //To be implemented
}

int Ghost::getX() // returns X coord of ghost
{
    return x;
}

int Ghost::getY() // returns Y coord of ghost
{
    return y;
}

bool Ghost::getFrightened() { // returns the frightened state of ghost
    return isFrightened;
}

bool Ghost::getEaten() { // returns the eaten state of the ghost
    return isEaten;
}