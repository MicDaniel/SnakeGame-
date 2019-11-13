#include"Snake.h"


void SetupGame(bool &gameOver, int &score) {
	DrawMap();
	gameOver = false;
	srand(time(NULL));
	dir = NONE;
	head.x = width / 2;
	head.y = height / 2;
	do {
		Spawn(fruit, 0);
	} while (fruit.x == head.x && fruit.y == head.y);
	score = 0;
}

void DrawMap() {
	SetCursorPosition(0, 0);
	for (int i = 0; i < width; i++) {
		printf("#");
	}
	printf("\n");
	for (int i = 0; i < height - 2; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				printf("|");
			else
				printf(" ");
		}
		printf("\n");
	}
	for (int i = 0; i < width; i++) {
		printf("#");
	}
}

void DrawGame(int score, int nTail, int p, int difficulty) {
	Sleep(difficulty);
	SetCursorPosition(head.x, head.y);
	printf("O");
	SetCursorPosition(fruit.x, fruit.y);
	printf("F");

	if (nTail >= 9) {
		SetCursorPosition(poison[p - 1].x, poison[p - 1].y);
		printf("P");
	}

	for (int idx = 0; idx < nTail; idx++) {
		SetCursorPosition(Tail.x[idx], Tail.y[idx]);
		printf("o");
	}

	if (nTail) {
		SetCursorPosition(oldTail.x, oldTail.y);
		printf(" ");
	}
	else
	{
		SetCursorPosition(oldHead.x, oldHead.y);
		printf(" ");
	}

	SetCursorPosition(0, 0);
	printf("#");
	SetCursorPosition(0, height);
	printf("Score: %d\n", score);
	printf("Press x to end the game.\n");
	printf("Use WASD or arrow keys to control the snake!\n");
	if (p > 0)
		printf("Be careful! Poison was generated. Do not eat the Ps or you will die!\n");
}

void InputGame(bool &gameOver) {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'w':
		case 72:
		{
			dir = UP;
			break;
		}
		case 'a':
		case 75:
		{
			dir = LEFT;
			break;
		}
		case 's':
		case 80:
		{
			dir = DOWN;
			break;
		}
		case 'd':
		case 77:
		{
			dir = RIGHT;
			break;
		}
		case 'x':
		{
			gameOver = true;
			break;
		}
		default:
			break;
		}
	}
}

void LogicGame(bool &gameOver, bool &spawned, int &score, int &nTail, int &speed, int &p) {
	// primele 2 elemente din coada
	coords first;
	coords second;

	first.x = Tail.x[0];
	first.y = Tail.y[0];
	Tail.x[0] = head.x;
	Tail.y[0] = head.y;

	for (int i = 1; i < nTail; i++) {
		second.x = Tail.x[i];
		second.y = Tail.y[i];
		Tail.x[i] = first.x;
		Tail.y[i] = first.y;
		first.x = second.x;
		first.y = second.y;
	}

	oldTail = first;

	switch (dir)
	{
	case LEFT:
		oldHead = head;
		head.x -= speed;
		break;
	case RIGHT:
		oldHead = head;
		head.x += speed;
		break;
	case UP:
		oldHead = head;
		head.y -= speed;
		break;
	case DOWN:
		oldHead = head;
		head.y += speed;
		break;
	default:
		break;
	}

	if (head.x >= width - 1 || head.x <= 0)
		gameOver = true;
	
	if (head.y >= height - 1 || head.y <= 0)
		gameOver = true;
	
	for (int i = 0; i < p; i++) {
		if (head.x == poison[i].x && head.y == poison[i].y)
			gameOver = true;
	}
	
	for (int i = 0; i < nTail; i++) {
		if (head.x == Tail.x[i] && head.y == Tail.y[i])
			gameOver = true;
	}

	if (head.x == fruit.x && head.y == fruit.y) {
		Spawn(fruit, nTail);
		spawned = false;
		score += 1;
		nTail++;
	}

	if (nTail >= 9 && spawned == false) {
		Spawn(poison[p], nTail);
		p++;
		spawned = true;
	}
}

void Spawn(coords &object, int nTail) {
	bool illegalPos;
	
	do {
		illegalPos = false;
		object.x = rand() % (width - 1);
		object.y = rand() % (height - 1);

		if (object.x == head.x && object.y == head.y)
			illegalPos = true;
		else
			if (object.x <= 0 || object.y <= 0 || object.x >= width - 1 || object.y >= height - 1)
				illegalPos = true;
			else
				for (int idx = 0; idx < nTail; idx++) {
					if (object.x == Tail.x[idx] && object.y == Tail.y[idx])
						illegalPos = true;
				}
	} while (illegalPos == true);
}

void SetCursorPosition(int x, int y) {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(output, pos);
}

void EndGame(int score, bool &restart, int nTail) {
	char decision = NULL;
	
	if (score == 1)
		printf("Game Over! Your final lenght was %d and you scored %d point.\n", nTail + 1, score);
	else
		printf("Game Over! Your final lenght was %d and you scored %d points.\n", nTail + 1, score);
	
	printf("Do you want to play again?");

	do {
		scanf_s("%c", &decision);
		decision = tolower(decision);
		if (decision == 'y' || decision == 'n')
			break;
	} while (true);

	if (decision == 'y') {
		restart = true;
		system("cls");
	}
	else {
		restart = false;
	}
}
int Difficulty(int &difficulty)
{
	printf("Please select your desired difficulty. A greater number signifies a more intense experience.\n");
	printf("1) Slow\n");
	printf("2) Normal\n");
	printf("3) Fast\n");
	printf("4) Ludicrous (Do not pick this one)\n");
	
	scanf_s("%d", &difficulty);
	
	switch (difficulty)
	{
	case 1:
		difficulty = 100;
		break;
	case 2:
		difficulty = 75;
		break;
	case 3:
		difficulty = 50;
		break;
	case 4:
		difficulty = 25;
		break;
	default:
		printf("Invalid choice. Difficulty autoset to normal.");
		difficulty = 75;
		Sleep(2000);
		break;
	}

	return 0;
}
