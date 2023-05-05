#include <string>
#include <curses.h>
#include <cmath>
#include "entities.h"
using namespace std;

Pacman::Pacman(int posX, int posY){
    x = posX;
    y = posY;
    last_x = posX;
    last_y = posY;
    faceDirection = 1; // defaults to facing right
}

int Pacman::getFaceDirection(){
    return faceDirection;
}

int Pacman::getX(){
    return x;
}

int Pacman::getY(){
    return y;
}

int Pacman::getLastX(){
    return last_x;
}

int Pacman::getLastY(){
    return last_y;
}

void Pacman::updatePosition(int posX, int posY){ // updates the location of pacman
    last_x = x;
    last_y = y;
    x = posX;
    y = posY;
}

void Pacman::toggleFaceDirection(){ // toggles faceDirection from left to right or right to left
    if (last_x > x){
        faceDirection = 0;
    } else {
        faceDirection = 1;
    }
}