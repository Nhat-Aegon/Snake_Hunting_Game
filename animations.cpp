#include"projectPrototype.h"
using namespace std;

void TransitionNewMap(DATA*& dataGame, POINT snake[], GATE*& gate, vector<POINT>& obstacle)
{
	dataGame->SIZE_SNAKE--;
	if (dataGame->SIZE_SNAKE == 0)
	{
		if (gate->countGate == 4)
		{
			TriAngle();
			return;
		}
		/////////// xoa cong ////////////
		for (int i = 0; i < 6; i++)
		{
			GotoXY(gate->g[i].x, gate->g[i].y);
			cout << " ";
		}
		/////////// tao congratulation ////////////
		GotoXY(20, 13);
		SetColor(12);
		cout << " Congratulations, you have passed the " << gate->countGate << " round";
		SetColor(7);
		Sleep(500);
		/////////// xoa congratulation ////////////
		GotoXY(20, 13);
		cout << "                                                  ";
		/////////// ve lai cong ////////////
		DrawWGate(78, 14);
		/////////// gan lai snake ///////////
		snake[0].x = 77;
		snake[0].y = 14;
		dataGame->SIZE_SNAKE = 0;
		dataGame->MOVING = 'A';
		dataGame->CHAR_LOCK = 'D';
		while (dataGame->SIZE_SNAKE < 6 + (gate->countGate - 1) * 3)
		{
			for (int i = 0; i < dataGame->SIZE_SNAKE; i++)
			{
				GotoXY(snake[i].x, snake[i].y);
				cout << ' ';
			}
			dataGame->SIZE_SNAKE++;
			if (dataGame->SIZE_SNAKE != 1)
			{
				snake[dataGame->SIZE_SNAKE - 1].y = 14;
				snake[dataGame->SIZE_SNAKE - 1].x = snake[dataGame->SIZE_SNAKE - 2].x;
				for (int i = 0; i < dataGame->SIZE_SNAKE - 1; i++)
				{
					snake[i].x = snake[i + 1].x;
					snake[i].y = snake[i + 1].y;
				}
			}
			Sleep(20);
			for (int i = dataGame->SIZE_SNAKE - 1; i >= 0; i--)
			{
				GotoXY(snake[i].x, snake[i].y);
				cout << ID[dataGame->SIZE_SNAKE - i - 1];
			}
		}
		gate->isGate = false;
	}
	if (gate->isGate == false)
		CreateMap(obstacle, gate->countGate);
}
void CreateMap(vector<POINT>& obstacle, int countGate)
{
	for (int i = 0; i < obstacle.size(); i++)
	{
		GotoXY(obstacle[i].x, obstacle[i].y);
		cout << " ";
	}
	obstacle.resize(0);
	switch (countGate)
	{
	case 2:
	{
		for (int i = 0; i < 8; i++)
		{
			SetColor(69);
			GotoXY(15, i + 5);
			cout << char(177);
			GotoXY(45, i + 5);
			cout << char(177);
			obstacle.push_back({ 15,i + 5 });
			obstacle.push_back({ 45,i + 5 });
			SetColor(7);
		}
		for (int i = 0; i < 8; i++)
		{
			SetColor(69);
			GotoXY(30, i + 16);
			cout << char(177);
			GotoXY(60, i + 16);
			cout << char(177);
			obstacle.push_back({ 30,i + 16 });
			obstacle.push_back({ 60,i + 16 });
			SetColor(7);
		}
		break;
	}
	case 3:
	{
		for (int i = 0; i < 6; i++)
		{
			SetColor(69);
			GotoXY(15, i + 5);
			cout << char(177);
			GotoXY(70, i + 5);
			cout << char(177);
			obstacle.push_back({ 15,i + 5 });
			obstacle.push_back({ 70,i + 5 });
			SetColor(7);
		}
		for (int i = 0; i < 6; i++)
		{
			SetColor(69);
			GotoXY(15, i + 18);
			cout << char(177);
			GotoXY(70, i + 18);
			cout << char(177);
			obstacle.push_back({ 15,i + 18 });
			obstacle.push_back({ 70,i + 18 });
			SetColor(7);
		}
		for (int i = 0; i < 5; i++)
		{
			SetColor(69);
			GotoXY(25, i + 12);
			cout << char(177);
			GotoXY(33, i + 12);
			cout << char(177);
			GotoXY(41, i + 12);
			cout << char(177);
			GotoXY(54, i + 12);
			cout << char(177);
			obstacle.push_back({ 25, i + 12 });
			obstacle.push_back({ 33, i + 12 });
			obstacle.push_back({ 41, i + 12 });
			obstacle.push_back({ 54, i + 12 });
			SetColor(7);
		}
		for (int i = 0; i < 5; i++)
		{
			SetColor(69);
			GotoXY(i + 26, 12);
			cout << char(177);
			GotoXY(i + 42, 12);
			cout << char(177);
			GotoXY(i + 52, 12);
			cout << char(177);
			obstacle.push_back({ i + 26, 12 });
			obstacle.push_back({ i + 42, 12 });
			obstacle.push_back({ i + 52, 12 });
			SetColor(7);
		}
		for (int i = 0; i < 5; i++)
		{
			SetColor(69);
			GotoXY(i + 26, 16);
			cout << char(177);
			GotoXY(i + 34, 16);
			cout << char(177);
			GotoXY(i + 42, 16);
			cout << char(177);
			GotoXY(i + 52, 16);
			cout << char(177);
			obstacle.push_back({ i + 26, 16 });
			obstacle.push_back({ i + 34, 16 });
			obstacle.push_back({ i + 42, 16 });
			obstacle.push_back({ i + 52, 16 });
			SetColor(7);
		}
		break;
	}
	}
}