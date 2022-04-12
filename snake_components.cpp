#include"projectPrototype.h"
using namespace std;

void Eat(DATA*& dataGame, GATE*& gate, vector<POINT> obstacle) {
	ScoreAndLevels(dataGame);
	dataGame->snake[dataGame->SIZE_SNAKE] = dataGame->food[dataGame->FOOD_INDEX];
	GotoXY(dataGame->food[dataGame->FOOD_INDEX].x, dataGame->food[dataGame->FOOD_INDEX].y);
	printf(" ");
	if (!gate->isGate)
	{
		if (dataGame->SCORE % 300 == 0)
		{
			gate->isGate = true;
			gate->countGate++;
			ProcessGate(dataGame, gate, obstacle);

			if (dataGame->SPEED == MAX_SPEED)
				dataGame->SPEED = 1;
			else dataGame->SPEED++;
		}
		else {
			GenerateFood(dataGame, obstacle);
			dataGame->SIZE_SNAKE++;
		}
	}
	PlaySound(TEXT("Chomp.wav"), NULL, SND_FILENAME | SND_ASYNC);
} //khi ran an moi thi do dai ran tang va vi tri moi duoc thay doi de tranh viec vi tri moi xuat hien tai vi tri con ran
void MoveRight(DATA*& dataGame, GATE*& gate, vector<POINT> &obstacle)
{
	if (IsTouchwall(dataGame, dataGame->snake[dataGame->SIZE_SNAKE - 1].x + 1, dataGame->snake[dataGame->SIZE_SNAKE - 1].y, obstacle))
	{
		ProcessDead(dataGame);
		return;
	}
	if (IsTouchBody(dataGame))
	{
		ProcessDead(dataGame);
		return;
	}
	if (gate->isGate == true)
	{
		if (IsGateTouch(dataGame, dataGame->snake, gate, obstacle) == 1)
		{
			ProcessDead(dataGame);
			return;
		}
	}
	if (dataGame->snake[dataGame->SIZE_SNAKE - 1].x + 1 == dataGame->food[dataGame->FOOD_INDEX].x && dataGame->snake[dataGame->SIZE_SNAKE - 1].y == dataGame->food[dataGame->FOOD_INDEX].y)
	{
		Eat(dataGame, gate, obstacle);
	}
	for (int i = 0; i < dataGame->SIZE_SNAKE - 1; i++)
	{
		dataGame->snake[i].x = dataGame->snake[i + 1].x;
		dataGame->snake[i].y = dataGame->snake[i + 1].y;
	}
	dataGame->snake[dataGame->SIZE_SNAKE - 1].x++;
}
void MoveLeft(DATA*& dataGame, GATE*& gate, vector<POINT> &obstacle) {
	if (IsTouchwall(dataGame, dataGame->snake[dataGame->SIZE_SNAKE - 1].x, dataGame->snake[dataGame->SIZE_SNAKE - 1].y, obstacle))
	{
		ProcessDead(dataGame);
		return;
	}
	if (IsTouchBody(dataGame))
	{
		ProcessDead(dataGame);
		return;
	}
	if (gate->isGate == true)
	{
		if (IsGateTouch(dataGame, dataGame->snake, gate, obstacle) == 1)
		{
			ProcessDead(dataGame);
			return;
		}
	}
	if (dataGame->snake[dataGame->SIZE_SNAKE - 1].x - 1 == dataGame->food[dataGame->FOOD_INDEX].x && dataGame->snake[dataGame->SIZE_SNAKE - 1].y == dataGame->food[dataGame->FOOD_INDEX].y)
	{
		Eat(dataGame, gate, obstacle);
	}
	for (int i = 0; i < dataGame->SIZE_SNAKE - 1; i++)
	{
		dataGame->snake[i].x = dataGame->snake[i + 1].x;
		dataGame->snake[i].y = dataGame->snake[i + 1].y;

	}
	dataGame->snake[dataGame->SIZE_SNAKE - 1].x--;
}
void MoveDown(DATA*& dataGame, GATE*& gate, vector<POINT> &obstacle)
{
	if (IsTouchwall(dataGame, dataGame->snake[dataGame->SIZE_SNAKE - 1].x, dataGame->snake[dataGame->SIZE_SNAKE - 1].y, obstacle))
	{
		ProcessDead(dataGame);
		return;
	}
	if (IsTouchBody(dataGame))
	{
		ProcessDead(dataGame);
		return;
	}
	if (gate->isGate == true)
	{
		if (IsGateTouch(dataGame, dataGame->snake, gate, obstacle) == 1)
		{
			ProcessDead(dataGame);
			return;
		}
	}
	if (dataGame->snake[dataGame->SIZE_SNAKE - 1].x == dataGame->food[dataGame->FOOD_INDEX].x && dataGame->snake[dataGame->SIZE_SNAKE - 1].y + 1 == dataGame->food[dataGame->FOOD_INDEX].y)
	{
		Eat(dataGame, gate, obstacle);
	}
	for (int i = 0; i < dataGame->SIZE_SNAKE - 1; i++)
	{
		dataGame->snake[i].x = dataGame->snake[i + 1].x;
		dataGame->snake[i].y = dataGame->snake[i + 1].y;

	}
	dataGame->snake[dataGame->SIZE_SNAKE - 1].y++;
}
void MoveUp(DATA*& dataGame, GATE*& gate, vector<POINT> &obstacle)
{
	if (IsTouchwall(dataGame, dataGame->snake[dataGame->SIZE_SNAKE - 1].x, dataGame->snake[dataGame->SIZE_SNAKE - 1].y, obstacle))
	{
		ProcessDead(dataGame);
		return;
	}
	if (IsTouchBody(dataGame))
	{
		ProcessDead(dataGame);
		return;
	}
	if (gate->isGate == true)
	{
		if (IsGateTouch(dataGame, dataGame->snake, gate, obstacle) == 1)
		{
			ProcessDead(dataGame);
			return;
		}
	}
	if (dataGame->snake[dataGame->SIZE_SNAKE - 1].x == dataGame->food[dataGame->FOOD_INDEX].x && dataGame->snake[dataGame->SIZE_SNAKE - 1].y - 1 == dataGame->food[dataGame->FOOD_INDEX].y)
	{
		Eat(dataGame, gate, obstacle);
	}
	for (int i = 0; i < dataGame->SIZE_SNAKE - 1; i++)
	{
		dataGame->snake[i].x = dataGame->snake[i + 1].x;
		dataGame->snake[i].y = dataGame->snake[i + 1].y;

	}
	dataGame->snake[dataGame->SIZE_SNAKE - 1].y--;
}
void GenerateFood(DATA*& dataGame, vector<POINT>& obstacle) {
	int x, y;
	srand(time(NULL));
	do {
		x = rand() % (dataGame->WIDTH_CONSOLE + 4) + 1;
		y = rand() % (dataGame->HEIGH_CONSOLE + 4) + 1;
		if (x <= 4) x = 5;
		if (x >= dataGame->WIDTH_CONSOLE + 4) x = dataGame->WIDTH_CONSOLE - 1;
		if (y <= 4) y = 5;
		if (y >= dataGame->HEIGH_CONSOLE + 4) y = dataGame->HEIGH_CONSOLE - 1;
	} while (!IsValid(dataGame, x, y, obstacle));
	dataGame->food[++dataGame->FOOD_INDEX] = { x,y };
}
