#ifndef __SNAKE_H
#define __SNAKE_H

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>

#define maxLenght 500

const int width = 60;
const int height = 20;

 struct coords {
	int x;
	int y;
};
struct tail {
	int x[maxLenght];
	int y[maxLenght];
};

enum eDir {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

static eDir dir;
static coords head, fruit, oldHead, oldTail, poison[25];
static tail Tail;

void SetupGame(bool &gameOver, int &score);
void DrawMap();
void DrawGame(int score, int nTail, int p, int difficulty);
void InputGame(bool &gameOver);
void LogicGame(bool &gameOver, bool &spawned, int &score, int &nTail, int &speed, int &p);
void SetCursorPosition(int x, int y);
void Spawn(coords &object, int nTail);
void EndGame(int score, bool &restart, int nTail);
int Difficulty(int &difficulty);

#endif