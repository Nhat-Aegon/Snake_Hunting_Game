#include"projectPrototype.h"
using namespace std;
void DrawBoard(DATA* dataGame, int x, int y, int width, int height, vector<POINT> obstacle){
	// draw up and low walls
	SetColor(50);
	for (int i = 0; i <= width; i++)
	{
		Sleep(5);
		GotoXY(x + i, y);
		cout << char(177);
		GotoXY(x + (width - i), y + height);
		cout << char(177);
	}
	// Draw 2 side walls
	for (int i = 1; i <= height; i++)
	{
		Sleep(30);
		GotoXY(x, y + i);
		cout << char(177);
		GotoXY(x + width, y + (height - i));
		cout << char(177);
	}
	int n = obstacle.size();
	SetColor(12);
	if (n > 0) {
		for (int i = 0; i < obstacle.size(); i++) {
			GotoXY(obstacle[i].x, obstacle[i].y);
			cout << char(177);
		}
	}
	SetColor(7);
}
void DrawSnakeAndFoodBefore(DATA*& dataGame, char* str, GATE*& gate){
	if (gate->isGate == false)
	{
		GotoXY(dataGame->food[dataGame->FOOD_INDEX].x, dataGame->food[dataGame->FOOD_INDEX].y);
		if (str == " ")
			cout << str;
	}
	for (int i = 0; i < dataGame->SIZE_SNAKE; i++) {
		GotoXY(dataGame->snake[i].x, dataGame->snake[i].y);
		cout << ' ';
	}
}
void DrawSnakeAndFoodAfter(DATA*& dataGame, GATE*& gate){
	if (gate->isGate == false)
	{
		GotoXY(dataGame->food[dataGame->FOOD_INDEX].x, dataGame->food[dataGame->FOOD_INDEX].y);
		cout << ID[dataGame->SIZE_SNAKE];
	}
	for (int i = dataGame->SIZE_SNAKE - 1; i >= 0; i--) {
		GotoXY(dataGame->snake[i].x, dataGame->snake[i].y);
		cout << ID[dataGame->SIZE_SNAKE - i - 1];
	}
	GotoXY(dataGame->snake[dataGame->SIZE_SNAKE - 1].x, dataGame->snake[dataGame->SIZE_SNAKE - 1].y);
}
