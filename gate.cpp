#include"projectPrototype.h"
using namespace std;

void DrawNGate(int x, int y)				// Ve cong
{
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y; j++)
		{
			GotoXY(i, j);
			cout << char(219);
		}									// Ve 6 dau X cho tat ca 6 o
	GotoXY(x, y);
	cout << char(220);							// Ve lai o chua vi tri cong
	GotoXY(x, y - 1);
	cout << ' ';							// Ve lai o truoc o chua vi tri cong *Lap lai cho E, S, W
}
void DrawEGate(int x, int y)
{
	for (int i = x; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
		{
			GotoXY(i, j);
			cout << char(219);
		}
	GotoXY(x, y);
	cout << char(219);
	GotoXY(x + 1, y);
	cout << ' ';
}
void DrawSGate(int x, int y)
{
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y; j <= y + 1; j++)
		{
			GotoXY(i, j);
			cout << char(219);
		}
	GotoXY(x, y);
	cout << char(219);
	GotoXY(x, y + 1);
	cout << ' ';
}
void DrawWGate(int x, int y)
{
	for (int i = x - 1; i <= x; i++)
		for (int j = y - 1; j <= y + 1; j++)
		{
			GotoXY(i, j);
			cout << char(22);
		}
	GotoXY(x, y);
	cout << char(221);
	GotoXY(x - 1, y);
	cout << ' ';
}

void DrawAndAssignGate(int x0, int y0, char drt, GATE*& gate)	// Ve cong va gan vi tri cac o lien quan vao op[]
{
	int n = 0;
	gate->g[4].x = x0;
	gate->g[4].y = y0;  // Gan dia chi cua cong cho op[4]
	int a = 0, b = 0;
	switch (drt)
	{
	case 'N':
	{
		DrawNGate(x0, y0);
		for (int a = x0 - 1; a <= x0 + 1; a++)
			for (int b = y0 - 1; b <= y0; b++)
				if (a != x0)
				{
					gate->g[n].x = a;
					gate->g[n].y = b;
					n++;
				}									// Gan 4 dia chi 4 o khong duoc cham gan cong vao op[0->3]
		gate->g[5].x = x0;
		gate->g[5].y = y0 - 1;							// Gan dia chi o truoc cong vao op[5] *Lap lai cho E, S va W*
		break;
	}
	case 'E':
	{
		DrawEGate(x0, y0);
		for (int a = x0; a <= x0 + 1; a++)
			for (int b = y0 - 1; b <= y0 + 1; b++)
				if (b != y0)
				{
					gate->g[n].x = a;
					gate->g[n].y = b;
					n++;
				}
		gate->g[5].x = x0 + 1;
		gate->g[5].y = y0;
		break;
	}
	case 'S':
	{
		DrawSGate(x0, y0);
		for (int a = x0 - 1; a <= x0 + 1; a++)
			for (int b = y0; b <= y0 + 1; b++)
				if (a != x0)
				{
					gate->g[n].x = a;
					gate->g[n].y = b;
					n++;
				}
		gate->g[5].x = x0;
		gate->g[5].y = y0 + 1;
		break;
	}
	case 'W':
	{
		DrawWGate(x0, y0);
		for (int a = x0 - 1; a <= x0; a++)
			for (int b = y0 - 1; b <= y0 + 1; b++)
				if (b != y0)
				{
					gate->g[n].x = a;
					gate->g[n].y = b;
					n++;
				}
		gate->g[5].x = x0 - 1;
		gate->g[5].y = y0;
		break;
	}
	}
}

void ProcessGate(DATA* dataGame, GATE*& gate, vector<POINT> obstacle)
{
	char direction[5] = { 'N','E','S','W' };
	int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
	srand(time(NULL));
	int i, j;
	char drt = direction[rand() % 4];			// Chon ra chieu ngau nhien
	do
	{
		x0 = rand() % dataGame->WIDTH_CONSOLE;
		y0 = rand() % dataGame->HEIGH_CONSOLE;
		for ( i = x0 - 2; i <= x0 + 2; i++)
		{
			for (j = y0 - 2; j <= y0 + 2; j++)
			{
				if (IsValid(dataGame, i, j, obstacle) == false)
					break;
			}
			if (IsValid(dataGame, i, j, obstacle) == false)
				break;
		}
	} while (x0<7 || x0>(dataGame->WIDTH_CONSOLE - 7) || y0<7 || y0>(dataGame->HEIGH_CONSOLE - 7) || IsValid(dataGame, i, j, obstacle) == false); // Chon vi tri cong ngau nhien
	DrawAndAssignGate(x0, y0, drt, gate); // Ve cong va gan cac gia tri vi tri lien quan
}
int IsGateTouch(DATA*& dataGame, POINT snake[], GATE*& gate, vector<POINT>& obstacle)// Kiem tra cham cong( 0: khong cham tuong, 1:cham tuong -> chet, 2:cham tuong -> qua man
{
	int flag = 0;
	if (snake[dataGame->SIZE_SNAKE - 1].x == gate->g[4].x && snake[dataGame->SIZE_SNAKE - 1].y == gate->g[4].y && snake[dataGame->SIZE_SNAKE - 2].x == gate->g[5].x && snake[dataGame->SIZE_SNAKE - 2].y == gate->g[5].y) // Ran di qua o truoc cong
	{
		TransitionNewMap(dataGame, snake, gate, obstacle);
		if (dataGame->SIZE_SNAKE == 6 + (gate->countGate - 1) * 3)
		{
			for (int i = 78 - 1; i <= 78; i++)
				for (int j = 14 - 1; j <= 14 + 1; j++)
				{
					GotoXY(i, j);
					printf(" ");
					Sleep(300);
				}
		}
		return 2;
	}
	for (int temp1 = 0; temp1 < 4; temp1++)
	{
		if (snake[dataGame->SIZE_SNAKE - 1].x == gate->g[temp1].x && snake[dataGame->SIZE_SNAKE - 1].y == gate->g[temp1].y)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		return 0;
	return 1;
}
