#define _CRT_SECURE_NO_WARNINGS 1
//#include<stdlib.h>

#include <iostream>
#include<windows.h> //Mot header cua Windows, chua cac ham trong windows api
#include<thread>
#include<conio.h>
#include<stdio.h>
#include<string>
#include<fstream>

using namespace std;

#define MAX_SIZE_SNAKE 8
#define MAX_SIZE_FOOD 10
#define MAX_SPEED 3
//Global variables

POINT snake[32]; //snake
POINT food[10]; // food
int ID[33] = { 2,1,1,2,7,1,2,6,2,1,1,2,7,5,1,8 };
int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is  one direction my snake cannot move to)
int MOVING;//used to determine the direction my snake moves (At a moment, there are three directions my snake can move)
int SPEED;// Standing for level, the higher the level, the quicker the speed
int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
int FOOD_INDEX; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size maybe 32)
int STATE; // State of snake: dead or alive
int load_Index = 0;
int count_savegame = 0;

struct OPSTACLE
{
	int x;
	int y;
};
OPSTACLE op[6] = { 0 };
bool gate = false;

void FixConsoleWindow() { // ham vo hieu khoa viec user thay doi kich thuoc cua so console
	HWND consoleWindow = GetConsoleWindow(); // HWND la 1 handle toi Window va la 1 kieu so dinh dang cua so Console, handle la 1 dinh dang chung ( thuong la con tro)
											// duoc su dung de bieu dien 1 dieu gi do
												// GetConsoleWindow la ham tra ve 1 handle toi window phu hop voi kieu du lieu duoc goi
	long style = GetWindowLong(consoleWindow, GWL_STYLE); // lay thong tin 32-bit cua 1 cua so, GWL_STYLE lay thong tin kieu cua cua so console
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME); // dieu chinh thong so cua style sao cho ngan nguoi dung phong to cua so hoac thay doi kich thuoc cua so
	SetWindowLong(consoleWindow, GWL_STYLE, style); // thay doi thong tin cua 1 cua so, gia tri muon thay the
}

void GotoXY(int x, int y) { // ham chuyen con tro chuot toi toa do (x,y)
	COORD coord; // bien luu toa do trong cua so console, toa do (0,0) nam tren cung ben trai
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // GetStdHandle:tra ve 1 handle tuong ung voi thiet bi tieu chuan ( cu the la window console), ham con lai la di chuyen con tro toi toa do tren cua so console
}
//Function to draw
void save_game()
{
	// khai bao
	system("cls");
	const char* filePath = "save_game.txt";
	char* name = new char(NULL);

	// kiem tra file name
	count_savegame++;
	char savegame1[50];
	if (count_savegame == 4)
	{
		strcpy(savegame1, name);

	}

	// doc du lieu
	GotoXY(58, 7);
	cout << "Enter your username:  ";
	cin.getline(name, 50);
	//save game vao file txt
	fstream f;
	f.open("Savegame.txt");
	f << name << endl;
	f << SIZE_SNAKE << endl;
	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		f << snake[i].x << ' ' << snake[i].y;
	}
	f << endl;
	f << SPEED << endl;
	f << MOVING << ' '<< CHAR_LOCK << endl;
	f << gate << endl; // =1 co nghia l?? xuat hien gate, =0 la khong co gate
	if (gate == 0) // neu khong co gate thi luu toa do cua food index
	{
		f << (food[FOOD_INDEX].x << ' ' << food[FOOD_INDEX].y);
	}
	f.close();
	if (!f)
		cout << "Can't save your file, please try another options!";
}

void DrawSnakeAndFoodBefore(char* str) {
	if (gate == false)
	{
		GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
		if (str == " ")
			cout << str;
	}
	for (int i = 0; i < SIZE_SNAKE; i++) {
		GotoXY(snake[i].x, snake[i].y);
		cout << ' ';
	}
}
void DrawSnakeAndFoodAfter() {
	if (gate == false)
	{
		GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
		cout << ID[SIZE_SNAKE];
	}
	for (int i = SIZE_SNAKE - 1; i >= 0; i--) {
		GotoXY(snake[i].x, snake[i].y);
		cout << ID[SIZE_SNAKE - i - 1];
	}
	GotoXY(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y);
}

bool IsValid(int x, int y) {

	for (int i = 0; i < SIZE_SNAKE; i++) {

		if (snake[i].x == x && snake[i].y == y) {

			return false;

		}
	}
	return true;
}

void DrawNGate(int x, int y)
{
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y; j++)
		{
			GotoXY(i, j);
			printf("X");
		}
	GotoXY(x, y);
	printf("U");
	GotoXY(x, y - 1);
	printf(" ");
}
void DrawEGate(int x, int y)
{
	for (int i = x; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
		{
			GotoXY(i, j);
			printf("X");
		}
	GotoXY(x, y);
	printf("C");
	GotoXY(x + 1, y);
	printf(" ");
}
void DrawSGate(int x, int y)
{
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y; j <= y + 1; j++)
		{
			GotoXY(i, j);
			printf("X");
		}
	GotoXY(x, y);
	printf("n");
	GotoXY(x, y + 1);
	printf(" ");
}
void DrawWGate(int x, int y)
{
	for (int i = x - 1; i <= x; i++)
		for (int j = y - 1; j <= y + 1; j++)
		{
			GotoXY(i, j);
			printf("X");
		}
	GotoXY(x, y);
	printf("D");
	GotoXY(x - 1, y);
	printf(" ");
}
bool pass = false;

void ProcessGate()
{
	char direction[5] = { 'N','E','S','W' };
	int x0 = 0, y0 = 0;
	srand(time(NULL));
	char drt = direction[rand() % 4];
	do
	{
		x0 = rand() % WIDTH_CONSOLE;
		y0 = rand() % HEIGH_CONSOLE;
	} while (x0<4 || x0>(WIDTH_CONSOLE - 4) || y0<4 || y0>(HEIGH_CONSOLE - 4) || IsValid(x0, y0) == false);
	int n = 0;
	op[4].x = x0;
	op[4].y = y0;
	switch (drt)
	{
	case 'N':
	{
		DrawNGate(x0, y0);
		for (int a = x0 - 1; a <= x0 + 1; a++)
			for (int b = y0 - 1; b <= y0; b++)
				if (a != x0)
				{
					op[n].x = a;
					op[n].y = b;
					n++;
				}
		op[5].x = x0;
		op[5].y = y0 - 1;
		break;
	}
	case 'E':
	{
		DrawEGate(x0, y0);
		for (int a = x0; a <= x0 + 1; a++)
			for (int b = y0 - 1; b <= y0 + 1; b++)
				if (b != y0)
				{
					op[n].x = a;
					op[n].y = b;
					n++;
				}
		op[5].x = x0 + 1;
		op[5].y = y0;
		break;
	}
	case 'S':
	{
		DrawSGate(x0, y0);
		for (int a = x0 - 1; a <= x0 + 1; a++)
			for (int b = y0; b <= y0 + 1; b++)
				if (a != x0)
				{
					op[n].x = a;
					op[n].y = b;
					n++;
				}
		op[5].x = x0;
		op[5].y = y0 + 1;
		break;
	}
	case 'W':
	{
		DrawWGate(x0, y0);
		for (int a = x0 - 1; a <= x0; a++)
			for (int b = y0 - 1; b <= y0 + 1; b++)
				if (b != y0)
				{
					op[n].x = a;
					op[n].y = b;
					n++;
				}
		op[5].x = x0 - 1;
		op[5].y = y0;
		break;
	}
	}
}

bool IsGateTouch(POINT snake[], OPSTACLE op[])
{
	if (snake[SIZE_SNAKE - 1].x == op[5].x && snake[SIZE_SNAKE - 1].y == op[5].y)
		pass = true;
	for (int i = 0; i < 4; i++)
		if (snake[SIZE_SNAKE - 1].x == op[i].x && snake[SIZE_SNAKE - 1].y == op[i].y)
			return true;
	if (snake[SIZE_SNAKE - 1].x == op[4].x && snake[SIZE_SNAKE - 1].y == op[4].y && pass == false)
		return true;
	return false;
}

bool isTouchBody()
{
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
	{ // so luong: vd la 4 dot ran
		if (snake[SIZE_SNAKE - 1].x == snake[i].x && snake[SIZE_SNAKE - 1].y == snake[i].y)
		{
			return true;
		}
	}
	return false;
}
bool isTouchwall(int x_head_position, int y_head_position)
{
	if (x_head_position <= 0 || y_head_position <= 0 || x_head_position >= WIDTH_CONSOLE || y_head_position >= HEIGH_CONSOLE)
		return true;
	return false;
}

void GenerateFood() {
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < MAX_SIZE_FOOD; i++) {
		do {
			x = rand() % (WIDTH_CONSOLE - 1) + 1;
			y = rand() % (HEIGH_CONSOLE - 1) + 1;

		} while (!IsValid(x, y));
		food[i] = { x,y };
	}
}

void Eat() {
	snake[SIZE_SNAKE] = food[FOOD_INDEX];
	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
	printf(" ");
	if (FOOD_INDEX == MAX_SIZE_FOOD - 1)
	{
		gate = true;
		ProcessGate();
		
		if (SPEED == MAX_SPEED) 
			SPEED = 1;
		else SPEED++;
		GenerateFood();
	}
	else {
		FOOD_INDEX++;
		SIZE_SNAKE++;

	}
} //khi ran an moi thi do dai ran tang va vi tri moi duoc thay doi de tranh viec vi tri moi xuat hien tai vi tri con ran
void ProcessDead()
{
	STATE = 0;
	GotoXY(0, HEIGH_CONSOLE + 2);
	printf("Dead, type y to continue or anykey to exit");
}

void MoveRight()
{
	if (isTouchwall(snake[SIZE_SNAKE - 1].x + 1, snake[SIZE_SNAKE - 1].y))
		ProcessDead();
	if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
	{
		Eat();
	}
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
	{
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;
	}
	snake[SIZE_SNAKE - 1].x++;
}
void MoveLeft()
{
	if (isTouchwall(snake[SIZE_SNAKE - 1].x - 1, snake[SIZE_SNAKE - 1].y))
		ProcessDead();
	if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
	{
		Eat();
	}
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
	{
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;

	}
	snake[SIZE_SNAKE - 1].x--;
}
void MoveDown()
{
	if (isTouchwall(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y + 1))
		ProcessDead();

	if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y)
	{
		Eat();
	}
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
	{
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;

	}
	snake[SIZE_SNAKE - 1].y++;
}
void MoveUp()
{
	if (isTouchwall(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y - 1))
		ProcessDead();
	if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y)
	{
		Eat();
	}
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
	{
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;

	}
	snake[SIZE_SNAKE - 1].y--;
}

void ThreadFunc() {
	while (true) {
		if (IsGateTouch(snake, op) || isTouchBody())
			ProcessDead();
		if (STATE == 1) {//If my snake is alive
			char* c = new char[2];
			strcpy(c, " ");
			DrawSnakeAndFoodBefore(c);
			switch (MOVING) {
			case 'A':
				MoveLeft();
				break;
			case 'D':
				MoveRight();
				break;
			case 'W':
				MoveUp();
				break;
			case 'S':
				MoveDown();
				break;
			}
			strcpy(c, "0");
			DrawSnakeAndFoodAfter();
			Sleep(100 / SPEED);
		}
	}
}
void DrawBoard(int x, int y, int width, int height)
{
	// draw up and low walls
	for (int i = 0; i <= width; i++)
	{
		GotoXY(x + i, y);
		cout << 'X';
		GotoXY(x + i, y + height);
		cout << 'X';
	}
	// Draw 2 side walls
	for (int i = 1; i <= height; i++)
	{
		GotoXY(x, y + i);
		cout << 'X';
		GotoXY(x + width, y + i);
		cout << 'X';
	}
	GotoXY(width + 1, height + 1);
}
void ResetData() {
	//Initialize the global values
	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 1; FOOD_INDEX = 0, WIDTH_CONSOLE = 100,
		HEIGH_CONSOLE = 20, SIZE_SNAKE = 6;
	// Initialize default values for snake
	snake[0] = { 10, 5 }; snake[1] = { 11, 5 }; // khoi tao giao tri cho ran
	GenerateFood();
	for (int i = 0; i < 6; i++)
	{
		snake[6 - i - 1].x = 15 - i;
		snake[6 - i - 1].y = 5;
	}
}
void StartGame() {
	system("cls"); // clear screen
	ResetData(); // Intialize original data
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE); // Draw game

	STATE = 1;//Start running Thread    
}
void ExitGame(HANDLE t) {
	system("cls");
	int temp = TerminateThread(t, 0);
	GotoXY(53, 6);
	cout << "THANKS FOR PLAYING";
}
//Function pause game
void PauseGame(HANDLE t) {
	SuspendThread(t);
}
void newGame()
{
	StartGame();
	thread t1(ThreadFunc); //Create thread for snake
	HANDLE handle_t1 = t1.native_handle(); //Take handle of thread
	int isPauseGame = 0;
	while (true) {
		int temp = 0;
		if (!STATE)
		{
			temp = _getch();
			if (temp >= 'a' && temp <= 'z')
				temp -= 32;
			if (temp == 'Y') StartGame();
			else
			{
				ExitGame(handle_t1); // int main thi return 0
			}
		}
		else if (STATE) {
			if (_kbhit())
			{
				temp = _getch();
				if (temp >= 'a' && temp <= 'z')
					temp -= 32;
			}
			if (temp == ' ' && !isPauseGame) {
					PauseGame(handle_t1);
					isPauseGame = 1;
			}
			else if (temp == 27) {
				ExitGame(handle_t1);
				return; // int main**
			}
			else {
				//ResumeThread(handle_t1); //neu de day thi khong the bam pause duoc
				if (temp == ' ' && isPauseGame)
				{
					switch (CHAR_LOCK)
					{
					case 'D':
					{
						temp = 'A';
						break;
					}
					case 'A':
					{
						temp = 'D';
						break;
					}
					case 'W':
					{
						temp = 'S';
						break;
					}
					case 'S':
					{
						temp = 'W';
					}
					}
					isPauseGame = 0;
				}
				if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S'))
				{
					ResumeThread(handle_t1); 
					if (temp == 'D') CHAR_LOCK = 'A';
					else if (temp == 'W') CHAR_LOCK = 'S';
					else if (temp == 'S') CHAR_LOCK = 'W';
					else CHAR_LOCK = 'D';
					MOVING = temp;
				}
			}
		}
	}
}
void setColor(int color) // ham doi mau chu
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void showCur(bool CursorVisibility) // ham hien/an con tro
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}
void main_menu() //xay dung menu
{
	int i = 1;
	int Set[] = { 12,7,7,7,7 }; // DEFAULT COLORS
	int counter = 1;
	char key;
	//setColor(i);	
	
	while (true)
	{
		i = !i;
		GotoXY(0, 0);
		if (i) {
			setColor(13);
		}
		else {
			setColor(10);
		}
		cout << R"(
			 _     _     _      _____  _  _      _____   ____  _      ____  _  __ _____
			/ \ /|/ \ /\/ \  /|/__ __\/ \/ \  /|/  __/  / ___\/ \  /|/  _ \/ |/ //  __/
			| |_||| | ||| |\ ||  / \  | || |\ ||| |  _  |    \| |\ ||| / \||   / |  \  
			| | ||| \_/|| | \||  | |  | || | \||| |_//  \___ || | \||| |-|||   \ |  /_ 
			\_/ \|\____/\_/  \|  \_/  \_/\_/  \|\____\  \____/\_/  \|\_/ \|\_|\_\\____\
                                                                           
		)";
		GotoXY(54, 9);
		setColor(Set[0]);
		cout << "NEW GAME";

		GotoXY(52, 10);
		setColor(Set[1]);
		cout << "HIGHEST SCORE";

		GotoXY(55, 11);
		setColor(Set[2]);
		cout << "CONTACT";

		GotoXY(54, 12);
		setColor(Set[3]);
		cout << "LAST GAME";

		GotoXY(56, 13);
		setColor(Set[4]);
		cout << "QUIT";

		key = _getch();

		if ((key == 'W' || key == 'w'))
		{
			counter--;
			if (counter == 0)
				counter = 5;
		}
		if ((key == 'S' || key == 's'))
		{
			counter++;
			if (counter > 5)
				counter = 1;

		}
		if (key == '\r')
		{
			switch (counter)
			{
			case 1:
			{
				newGame();
				return;
			}
			break;
			}
		}

		for (int i = 0; i < 5; i++)
		{
			Set[i] = 7;
		}

		if (counter != 0)
		{
			Set[counter - 1] = 12;
		}
	}

}

int main()
{
	showCur(0);
	FixConsoleWindow();
	main_menu();
	return 1;
}
