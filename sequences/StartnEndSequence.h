#ifndef STARTNENDSEQUENCE
#define STARTNENDSEQUENCE

#include <iostream>
using namespace std;

int StartingSequence();
int EndingSequence();
void howToPlay();
void loadStatistics(int score, string name, int highscore);
void CheckScore(int score, int highscore);
void loadprofile(int highscore, string name);
void exportprofile(int highscore, string name);
int GameOver(int score);

#endif
