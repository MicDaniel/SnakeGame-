#include"Snake.h"


int main()
{
	bool restart;
	
	do {
		int p = 0; // poison counter;
		int speed = 1;
		int nTail = 0;
		int score;
		bool spawned = false;
		bool gameOver;
		int difficulty = 0;

		restart = false;
		Difficulty(difficulty);
		system("cls");
		SetupGame(gameOver, score);
		while (!gameOver) {
			DrawGame(score, nTail, p, difficulty);
			InputGame(gameOver);
			LogicGame(gameOver, spawned, score, nTail, speed, p);
		}
		EndGame(score, restart, nTail);
	} while (restart == true);

	return 0;
}