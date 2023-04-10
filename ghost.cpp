#include <string>
#include <curses.h>
#include "entities.h"
using namespace std;

Ghost::Ghost(int posX, int posY)
{
    x = posX;
    y = posY;    
}

void Ghost::update(int playerPosX, int playerPosY)
{
    //Implementation to update posX and posY every frame to chase Pac-Man
}

int Ghost::getX()
{
    return x;
}

int Ghost::getY()
{
    return y;
}