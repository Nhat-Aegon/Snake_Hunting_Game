#define _CRT_SECURE_NO_WARNINGS 1
//#include<stdlib.h>

#include <iostream>
#include<windows.h> //Mot header cua Windows, chua cac ham trong windows api
#include<thread>
#include<conio.h>
#include<fstream>
#include<string.h>
#include <vector>

using namespace std;

#define MAX_SIZE_SNAKE 8
#define MAX_SIZE_FOOD 10
#define MAX_SPEED 3
//Global variables

POINT snake[32]; //snake
POINT food[10]; // food
int ID[32] = { 2,1,1,2,7,1,2,6,2,1,1,2,7,5,1,8,2,1,1,2,7,6,5,8,2,1,1,2,7,5,5,9 };
int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is  one direction my snake cannot move to)
int MOVING;//used to determine the direction my snake moves (At a moment, there are three directions my snake can move)
int SPEED;// Standing for level, the higher the level, the quicker the speed
int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
int FOOD_INDEX = -1; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size maybe 32)
int STATE; // State of snake: dead or alive
int load_Index = 0;
int count_savegame = 0;
bool gate = false;
int SCORE;
int LEVELS = 1;


///////////////////////////////////////////////////////////////////////////////Header 0: Useful Function	///////////////////////////////////////////////////////////////////////////////

struct GATE
{
	POINT g[6] = { 0 };
	bool isGate = false;
	int countGate = 1;
};
vector<POINT> obstacle;
void GotoXY(int x, int y);
void FixConsoleWindow();
void ShowCur(bool CursorVisibility);
void SetColor(int color);
void TextBackGround(WORD color);
bool IsValid(int x, int y, vector<POINT> obstacle);
void GenerateFood(vector<POINT>& obstacle);
void DrawBoard(int x, int y, int width, int height, vector<POINT> obstacle);
void DrawSnakeAndFoodBefore(char* str, GATE*& gate);
void DrawSnakeAndFoodAfter(GATE*& gate);
void DrawNGate(int x, int y);
void DrawEGate(int x, int y);
void DrawSGate(int x, int y);
void DrawWGate(int x, int y);
void DrawAndAssignGate(int x0, int y0, char drt, GATE*& gate);
void ProcessGate(GATE*& gate, vector<POINT> obstacle);
void CreateMap(vector<POINT>& obstacle, int countGate);
void TransitionNewMap(POINT snake[], GATE*& gate, vector<POINT>& obstacle);
int IsGateTouch(POINT snake[], GATE*& gate, vector<POINT>& obstacle);
void BlinkSnake();
void DrawScoreAndLevels();
void ScoreAndLevels();
void ProcessDead();
void PauseGame(HANDLE t);
//void ExitGame(HANDLE t);
void ExitGame(HANDLE t, GATE*& gate);
void SaveGame(GATE* gate, vector<POINT>obstacle);
void Eat(GATE*& gate, vector<POINT> obstacle);
bool IsTouchBody();
bool IsTouchwall(int x_head_position, int y_head_position, vector<POINT>& obstacle);
void MoveRight(GATE*& gate, vector<POINT> obstacle);
void MoveLeft(GATE*& gate, vector<POINT> obstacle);
void MoveDown(GATE*& gate, vector<POINT> obstacle);
void MoveUp(GATE*& gate, vector<POINT> obstacle);
void ResetData(GATE*& gate, vector<POINT>& obstacle);
void ResetDataLoadGame(GATE*& gate, vector<POINT>& obstacle);
void ThreadFunc(GATE*& gate, vector<POINT>& obstacle);
void StartGame(int x, GATE*& gate, vector<POINT>& obstacle);
void NewGame(int x, GATE*& gate, vector<POINT>& obstacle);
int LoadingAnimation();
void MainMenu(GATE*& gate, vector<POINT>& obstacle);

/////////////////////////////////////////////////////////////////////////				int main()				/////////////////////////////////////////
int main()
{

	GATE* gate = new GATE();
	ShowCur(0);
	FixConsoleWindow();
	MainMenu(gate, obstacle);
	delete gate;
	return 0;
}


void GotoXY(int x, int y) { // ham chuyen con tro chuot toi toa do (x,y)
	COORD coord; // bien luu toa do trong cua so console, toa do (0,0) nam tren cung ben trai
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // GetStdHandle:tra ve 1 handle tuong ung voi thiet bi tieu chuan ( cu the la window console), ham con lai la di chuyen con tro toi toa do tren cua so console
}

void noScrollbar() {
	// get handle to the console window
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// retrieve screen buffer info
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

	// current window size
	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

	// current screen buffer size
	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;

	// to remove the scrollbar, make sure the window height matches the screen buffer height
	COORD newSize;
	newSize.X = scrBufferWidth;
	newSize.Y = winHeight;

	// set the new screen buffer dimensions
	int Status = SetConsoleScreenBufferSize(hOut, newSize);
	//if (Status == 0)
	//{
	//    cout << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << endl;
	//    exit(Status);
	//}

	// print the current screen buffer dimensions
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
	//cout << "Screen Buffer Size : " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << endl;
}
void FixConsoleWindow() { // ham vo hieu khoa viec user thay doi kich thuoc cua so console
	HWND consoleWindow = GetConsoleWindow(); // HWND la 1 handle toi Window va la 1 kieu so dinh dang cua so Console, handle la 1 dinh dang chung ( thuong la con tro)
											// duoc su dung de bieu dien 1 dieu gi do
												// GetConsoleWindow la ham tra ve 1 handle toi window phu hop voi kieu du lieu duoc goi
	long style = GetWindowLong(consoleWindow, GWL_STYLE); // lay thong tin 32-bit cua 1 cua so, GWL_STYLE lay thong tin kieu cua cua so console
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME); // dieu chinh thong so cua style sao cho ngan nguoi dung phong to cua so hoac thay doi kich thuoc cua so
	SetWindowLong(consoleWindow, GWL_STYLE, style); // thay doi thong tin cua 1 cua so, gia tri muon thay the
}
void ShowCur(bool CursorVisibility) // ham hien/an con tro
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}
void SetColor(int color) // ham doi mau chu
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void TextBackGround(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

bool IsValid(int x, int y, vector<POINT> obstacle) {

	for (int i = 0; i < SIZE_SNAKE; i++) {

		if (snake[i].x == x && snake[i].y == y) {

			return false;

		}
	}
	for (int i = 0; i < obstacle.size(); i++) {

		if (obstacle[i].x == x && obstacle[i].y == y) {

			return false;

		}
	}
	return true;
}
// isGateTouch
void GenerateFood(vector<POINT>& obstacle) {
	int x, y;
	srand(time(NULL));
	do {
		x = rand() % (WIDTH_CONSOLE + 4) + 1;
		y = rand() % (HEIGH_CONSOLE + 4) + 1;
		if (x <= 4) x = 5;
		if (x >= WIDTH_CONSOLE + 4) x = WIDTH_CONSOLE - 1;
		if (y <= 4) y = 5;
		if (y >= HEIGH_CONSOLE + 4) y = HEIGH_CONSOLE - 1;
	} while (!IsValid(x, y, obstacle));
	food[++FOOD_INDEX] = { x,y };
}


//////////////////////////////////////////////////////////////////////////		 Header 1: Environment					///////////////////////////////////////////////////////////
void DrawBoard(int x, int y, int width, int height, vector<POINT>obstacle)
{
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


void DrawSnakeAndFoodBefore(char* str, GATE*& gate) {

	if (gate->isGate == false)
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
void DrawSnakeAndFoodAfter(GATE*& gate) {
	if (gate->isGate == false)
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
bool pass = false;

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

void ProcessGate(GATE*& gate, vector<POINT> obstacle)
{
	char direction[5] = { 'N','E','S','W' };
	int x0 = 0, y0 = 0, x1 = 0, y1 = 0,x2=0,y2=0;
	srand(time(NULL));
	char drt = direction[rand() % 4];			// Chon ra chieu ngau nhien
	do
	{
		x0 = rand() % WIDTH_CONSOLE;
		y0 = rand() % HEIGH_CONSOLE;
		switch (drt)
		{
		case 'N':
		{
			x1 = x0;
			x2 = x0;
			y1 = y0 - 1;
			y2 = y0 - 2;
			break;
		}
		case 'E':
		{
			x1 = x0 + 1;
			x2 = x0 + 2;
			y1 = y0;
			y2 = y0;
			break;
		}
		case 'S':
		{
			x1 = x0;
			x2 = x0;
			y1 = y0 + 1;
			y2 = y0 + 2;
			break;
		}
		case 'W':
		{
			x1 = x0 - 1;
			x2 = x0 - 2;
			y1 = y0;
			y2 = y0;
			break;
		}
		}
	} while (x0<7 || x0>(WIDTH_CONSOLE - 7) || y0<7 || y0>(HEIGH_CONSOLE - 7) || IsValid(x0, y0, obstacle) == false || IsValid(x1, y1, obstacle) == false || IsValid(x2, x2, obstacle) == false); // Chon vi tri cong ngau nhien
	DrawAndAssignGate(x0, y0, drt, gate); // Ve cong va gan cac gia tri vi tri lien quan
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

/////////////////////////////////////////////////////////////////////////				Header 4: Animations				/////////////////////////////////////////

void TransitionNewMap(POINT snake[], GATE*& gate, vector<POINT>& obstacle)
{
	SIZE_SNAKE--;
	if (SIZE_SNAKE == 0)
	{
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
		SIZE_SNAKE = 0;
		MOVING = 'A';
		CHAR_LOCK = 'D';
		while (SIZE_SNAKE < 6 + (gate->countGate - 1) * 3)
		{
			for (int i = 0; i < SIZE_SNAKE; i++)
			{
				GotoXY(snake[i].x, snake[i].y);
				cout << ' ';
			}
			SIZE_SNAKE++;
			if (SIZE_SNAKE != 1)
			{
				snake[SIZE_SNAKE - 1].y = 14;
				snake[SIZE_SNAKE - 1].x = snake[SIZE_SNAKE - 2].x;
				for (int i = 0; i < SIZE_SNAKE - 1; i++)
				{
					snake[i].x = snake[i + 1].x;
					snake[i].y = snake[i + 1].y;
				}
			}
			Sleep(20);
			for (int i = SIZE_SNAKE - 1; i >= 0; i--)
			{
				GotoXY(snake[i].x, snake[i].y);
				cout << ID[SIZE_SNAKE - i - 1];
			}
		}
		gate->isGate = false;
	}
	if (gate->isGate == false)
		CreateMap(obstacle, gate->countGate);
}

int IsGateTouch(POINT snake[], GATE*& gate, vector<POINT>& obstacle)	// Kiem tra cham cong( 0: khong cham tuong, 1:cham tuong -> chet, 2:cham tuong -> qua man
{
	int flag = 0;
	if (snake[SIZE_SNAKE - 1].x == gate->g[5].x && snake[SIZE_SNAKE - 1].y == gate->g[5].y) // Ran di qua o truoc cong
	{
		TransitionNewMap(snake, gate, obstacle);
		if (SIZE_SNAKE == 6 + (gate->countGate - 1) * 3)
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
	for (int temp1 = 0; temp1 < 6; temp1++)
	{
		if (snake[SIZE_SNAKE - 1].x == gate->g[temp1].x && snake[SIZE_SNAKE - 1].y == gate->g[temp1].y)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		return 0;


	return 1;
}
void BlinkSnake() //hieu ung nhap nhay con ran
{
	for (int j = 0; j < 5; j++)
	{
		Sleep(200);
		for (int i = 0; i < SIZE_SNAKE; i++)
		{
			GotoXY(snake[i].x, snake[i].y);
			cout << ID[i];
		}
		Sleep(100);
		for (int i = 0; i < SIZE_SNAKE; i++)
		{
			GotoXY(snake[i].x, snake[i].y);
			cout << " ";
		}
	}
}

void DrawScoreAndLevels() // ve ra bang score ban dau
{
	SetColor(7);
	GotoXY(92, 6);
	cout << "LEVELS: 1 " << endl;
	GotoXY(92, 7);
	cout << "SCORE: 0 " << endl;
}


void ScoreAndLevels() //ham su dung bat dau tinh diem va level khi ran an
{
	SCORE += 100;
	if (SCORE % 300 == 0)
		LEVELS++;
	SetColor(7);
	GotoXY(92, 6);
	cout << "LEVELS: " << LEVELS << endl;
	GotoXY(92, 7);
	cout << "SCORE: " << SCORE << endl;
}

void GameGuide()
{
	SetColor(13);
	for (int i = 0; i < 38; i++)
	{
		GotoXY(82 + i, 5);
		cout << char(223);
		GotoXY(82 + i, 11);
		cout << char(223);
		GotoXY(82 + i, 17);
		cout << char(223);
		GotoXY(82 + i, 24);
		cout << char(223);
		GotoXY(82 + i, 20);
		cout << char(220);
		GotoXY(82 + i, 24);
		cout << char(220);
	}
	cout << endl;
	for (int i = 0; i < 20; i++)
	{
		GotoXY(81, 5 + i);
		cout << char(222);
		GotoXY(121, 6 + i);
		cout << char(222);
	}
	cout << endl;
	SetColor(7);
	GotoXY(85, 4);
	cout << "+ + + + THE GAME GUIDE + + + +" << endl;
	GotoXY(84, 12);
	cout << " 'SPACE': Pause/continue game" << endl;
	GotoXY(84, 13);
	cout << " 'ESC'  : Exit game" << endl;
	GotoXY(84, 14);
	cout << " 'P'    : Save game " << endl;
	GotoXY(84, 15);
	cout << "  Use 'W,A,S,D' key to move" << endl;
	GotoXY(86, 18);
	cout << R"( ____  _      ____  _  __ _____ )";
	cout << endl;
	GotoXY(86, 19);
	cout << R"(/ ___\/ \  /|/  _ \/ |/ //  __/ )";
	cout << endl;
	GotoXY(86, 20);
	cout << R"(|    \| |\ ||| / \||   / |  \ )";
	cout << endl;
	GotoXY(86, 21);
	cout << R"(\___ || | \||| |-|||   \ |  /_ )";
	cout << endl;
	GotoXY(86, 22);
	cout << R"(\____/\_/  \|\_/ \|\_|\_\\____\ )";
	cout << endl;


	//cout << R"(
	//	       Press SPACE to pause/continue game
	//		   Press 'ESC' to exit game  
	//		   Press 'P' to save game                                                            
	//	)";
}

/////////////////////////////////////////////////////////////////////////				Header 2: Special Features								/////////////////////////////////////////
void ProcessDead()
{
	STATE = 0;
	GotoXY(3, HEIGH_CONSOLE + 7);
	SetColor(12);
	PlaySound(TEXT("die-long.wav"), NULL, SND_FILENAME | SND_ASYNC);
	printf("DEAD!!! Type Y to play again or anykey to exit");
	SetColor(7);
}

void PauseGame(HANDLE t)
{
	SuspendThread(t);
}

void ExitGame(HANDLE t, GATE*& gate) {
	int key = 0;
	PauseGame(t);
	system("cls");
	int temp = TerminateThread(t, 0);
	GotoXY(34, 4);
	cout << "THANKS FOR PLAYING";
	GotoXY(34, 7);
	cout << "Press M to go back to Main Menu";
	if (!STATE)
	{
		key = _getch();
		if (key >= 'a' && key <= 'z')
			key -= 32;
		if (key == 'M') //StartGame(1, gate);
		{
			MainMenu(gate, obstacle);
		}
		else
		{
			//ExitGame(handle_t1, gate); // int main thi return 0
			exit(0);
		}
	}
}

void SaveGame(GATE* gate, vector<POINT> obstacle)
{
	// khai bao
	system("cls");
	char* filePath = new char[100];
	char* name = new char[50];

	// kiem tra file name	
	strcpy(filePath, "savegame1.txt");

	// doc du lieu

	GotoXY(58, 7);
	cout << "Enter your username:  ";
	cin.getline(name, 50);

	//save game vao file txt
	fstream f;
	f.open(filePath);
	f << name << endl;
	f << SIZE_SNAKE << endl;
	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		f << snake[i].x << ' ' << snake[i].y << ' ';
	}
	f << endl;
	f << SPEED << endl;
	f << LEVELS << endl;
	f << SCORE << endl;
	f << int(MOVING) << endl;
	f << int(CHAR_LOCK) << endl;
	f << FOOD_INDEX << endl;
	for (int i = 0; i <= FOOD_INDEX; i++)
	{
		f << food[i].x << ' ' << food[i].y << endl;
	}

	f << gate->isGate << endl;
	f << gate->countGate << endl;
	for (int i = 0; i < 6; i++)
		f << gate->g[i].x << ' ' << gate->g[i].y << endl;

	int x = 0, y = 0;
	f << obstacle.size() << endl;
	if (obstacle.size() > 0)
	{
		for (int i = 0; i < obstacle.size(); i++)
		{
			f << obstacle[i].x << ' ' << obstacle[i].y << endl;
		}
	}
	f.close();
	if (!f)
		cout << "Can't save your file, please try another options!";
	delete[]filePath;
	delete[]name;
}

/////////////////////////////////////////////////////////////////////////			  Header 3: Snake Components/////////////////////////////////////////
void Eat(GATE*& gate, vector<POINT> obstacle) {

	ScoreAndLevels();
	snake[SIZE_SNAKE] = food[FOOD_INDEX];
	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
	printf(" ");
	if (!gate->isGate)
	{
		if (SCORE % 300 == 0)
		{
			gate->isGate = true;
			gate->countGate++;
			ProcessGate(gate, obstacle);

			if (SPEED == MAX_SPEED)
				SPEED = 1;
			else SPEED++;
		}
		else {
			GenerateFood(obstacle);
			SIZE_SNAKE++;
		}
	}
	PlaySound(TEXT("Chomp.wav"), NULL, SND_FILENAME | SND_ASYNC);
} //khi ran an moi thi do dai ran tang va vi tri moi duoc thay doi de tranh viec vi tri moi xuat hien tai vi tri con ran
bool IsTouchBody()
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
bool IsTouchwall(int x_head_position, int y_head_position, vector<POINT>& obstacle)
{
	if (x_head_position <= 4 || y_head_position <= 4 || x_head_position >= WIDTH_CONSOLE + 4 || y_head_position >= HEIGH_CONSOLE + 4)
		return true;
	for (int i = 0; i < obstacle.size(); i++)
	{
		if (x_head_position == obstacle[i].x && y_head_position == obstacle[i].y)
			return true;
	}
	return false;
}
void MoveRight(GATE*& gate, vector<POINT> obstacle)
{
	if (IsTouchwall(snake[SIZE_SNAKE - 1].x + 1, snake[SIZE_SNAKE - 1].y, obstacle))
	{
		ProcessDead();
		return;
	}
	if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
	{
		Eat(gate, obstacle);
	}
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
	{
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;
	}
	snake[SIZE_SNAKE - 1].x++;
}
void MoveLeft(GATE*& gate, vector<POINT> obstacle)
{
	if (IsTouchwall(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y, obstacle))
	{
		ProcessDead();
		return;
	}
	if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
	{
		Eat(gate, obstacle);
	}
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
	{
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;

	}
	snake[SIZE_SNAKE - 1].x--;
}
void MoveDown(GATE*& gate, vector<POINT> obstacle)
{
	if (IsTouchwall(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y, obstacle))
	{
		ProcessDead();
		return;
	}
	if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y)
	{
		Eat(gate, obstacle);
	}
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
	{
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;

	}
	snake[SIZE_SNAKE - 1].y++;
}
void MoveUp(GATE*& gate, vector<POINT> obstacle)
{
	if (IsTouchwall(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y, obstacle))
	{
		ProcessDead();
		return;
	}
	if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y)
	{
		Eat(gate, obstacle);
	}
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
	{
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;

	}
	snake[SIZE_SNAKE - 1].y--;
}
void ResetData(GATE*& gate, vector<POINT>& obstacle) {
	//Initialize the global values
	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 1; FOOD_INDEX = 0, WIDTH_CONSOLE = 75,
		HEIGH_CONSOLE = 20, SIZE_SNAKE = 6;
	SCORE = 0;
	LEVELS = 1;
	gate->isGate = false;
	for (int i = 0; i < 6; i++)
		gate->g[i] = { 0,0 };
	gate->countGate = 1;
	obstacle.resize(0);
	// Initialize default values for snake
	snake[0] = { 10, 5 }; snake[1] = { 11, 5 }; // khoi tao giao tri cho ran
	GenerateFood(obstacle);
	for (int i = 0; i < 6; i++)
	{
		snake[6 - i - 1].x = 15 - i;
		snake[6 - i - 1].y = 7;
	}
}

void ResetDataLoadGame(GATE*& gate, vector<POINT>& obstacle)
{
	//Initialize the global values

	FILE* fin = fopen("savegame1.txt", "r");
	char* name = new char[50];

	char c = '/0';
	int len = 0;
	/// doc ten ng choi
	while (true)
	{
		c = fgetc(fin);
		if (c == '\n') break;
		name[len] = c;
		len++;
	}
	name[len] = '\0';
	GotoXY(55, 10);

	cout << "Welcome back " << name;
	Sleep(500);

	fscanf_s(fin, "%d", &SIZE_SNAKE);

	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		fscanf_s(fin, "%d %d", &snake[i].x, &snake[i].y);
	}

	fscanf_s(fin, "%d", &SPEED);

	fscanf_s(fin, "%d", &LEVELS);

	fscanf_s(fin, "%d", &SCORE);

	int temp = 0, temp1 = 0;
	fscanf_s(fin, "%d %d", &temp, &temp1);
	MOVING = char(temp);
	CHAR_LOCK = char(temp1);
	fscanf_s(fin, "%d", &FOOD_INDEX);
	for (int i = 0; i <= FOOD_INDEX; i++)
	{
		fscanf_s(fin, "%d %d", &food[i].x, &food[i].y);
	}
	fscanf_s(fin, "%d", &temp);
	if (temp == 1)
	{
		gate->isGate = true;
	}
	else {
		gate->isGate = false;

	}
	fscanf_s(fin, "%d", &gate->countGate);
	for (int i = 0; i < 6; i++) {
		fscanf_s(fin, "%d %d", &gate->g[i].x, &gate->g[i].y);
	}
	int n = 0;
	fscanf_s(fin, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf_s(fin, "%d %d", &temp, &temp1);
		obstacle.push_back({ temp,temp1 });
	}
	SetColor(7);

	WIDTH_CONSOLE = 75;
	HEIGH_CONSOLE = 20;
}



/////////////////////////////////////////////////////////////////////////				Header 5: Play Game								/////////////////////////////////////////
void ThreadFunc(GATE*& gate, vector<POINT>& obstacle) {
	while (true) {
		if (IsTouchBody())
			ProcessDead();
		if (gate->isGate == true)
		{
			if (IsGateTouch(snake, gate, obstacle) == 1)
			{
				ProcessDead();
			}
		}
		if (STATE == 1) {//If my snake is alive
			char* c = new char[2];
			strcpy(c, " ");
			DrawSnakeAndFoodBefore(c, gate);
			switch (MOVING) {
			case 'A':
				MoveLeft(gate, obstacle);
				break;
			case 'D':
				MoveRight(gate, obstacle);
				break;
			case 'W':
				MoveUp(gate, obstacle);
				break;
			case 'S':
				MoveDown(gate, obstacle);
				break;
			}
			strcpy(c, "0");
			DrawSnakeAndFoodAfter(gate);
			Sleep(100 / SPEED);
		}
	}
}
void StartGame(int x, GATE*& gate, vector<POINT>& obstacle) {
	system("cls"); // clear screen
	if (x == 1) ResetData(gate, obstacle); // Intialize original data
	else
	{
		ResetDataLoadGame(gate, obstacle);
	}
	system("cls");
	DrawBoard(4, 4, WIDTH_CONSOLE, HEIGH_CONSOLE, obstacle); // Draw game
	if (gate->isGate)
	{
		for (int i = 0; i < 5; i++)
		{
			GotoXY(gate->g[i].x, gate->g[i].y);
			cout << char(177);
		}
	}
	GameGuide();
	DrawScoreAndLevels();
	STATE = 1;//Start running Thread    
}

void NewGame(int x, GATE*& gate, vector<POINT>& obstacle)
{
	StartGame(x, gate, obstacle);
	std::thread t1(ThreadFunc, std::ref(gate), std::ref(obstacle)); //Create thread for snake
	HANDLE handle_t1 = t1.native_handle(); //Take handle of thread
	int isPauseGame = 0;
	while (true) {
		int temp = 0;
		if (!STATE)
		{
			temp = _getch();
			if (temp >= 'a' && temp <= 'z')
				temp -= 32;
			if (temp == 'Y') StartGame(1, gate, obstacle);
			else
			{
				ExitGame(handle_t1, gate); // int main thi return 0
			}
		}
		else if (STATE) {
			if (_kbhit())
			{
				temp = _getch();
				if (temp >= 'a' && temp <= 'z')
					temp -= 32;
			}
			if (temp == 'P')
			{
				PauseGame(handle_t1);
				SaveGame(gate, obstacle);
				ExitGame(handle_t1, gate);
			}
			else if (temp == ' ' && !isPauseGame) {
				PauseGame(handle_t1);
				SetColor(12);
				GotoXY(4, HEIGH_CONSOLE + 6);
				cout << "YOU ARE PAUSING GAME!! Press SPACE or W,A,D,S to continue playing";
				SetColor(7);
				isPauseGame = 1;
			}
			else if (temp == 27) {
				ExitGame(handle_t1, gate);
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
					GotoXY(4, HEIGH_CONSOLE + 6);
					cout << "                                                                   ";
					isPauseGame = 2;
				}
				if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S'))
				{
					if (isPauseGame)
					{
						GotoXY(4, HEIGH_CONSOLE + 6);
						cout << "                                                                   ";
						isPauseGame = 0;
					}
					ResumeThread(handle_t1); //de day thi bam pause duoc nhung so lan bam "P" phai tuong ung so lan bam chuyen dong ve sau thi moi chuyen dong tiep duoc
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

///////////////////////////////////////////////////////////////////////////////				Header 6: Menu							///////////////////////////////////////////////////////////////////////////////

int LoadingAnimation() {
	system("cls");
	int i = 7;
	int x = 30;
	int y = 20;
	int check = 0;
	GotoXY(0, 0);
	SetColor(12);
	cout << R"(
		 _     _     _      _____  _  _      _____   ____  _      ____  _  __ _____
		/ \ /|/ \ /\/ \  /|/__ __\/ \/ \  /|/  __/  / ___\/ \  /|/  _ \/ |/ //  __/
		| |_||| | ||| |\ ||  / \  | || |\ ||| |  _  |    \| |\ ||| / \||   / |  \
		| | ||| \_/|| | \||  | |  | || | \||| |_//  \___ || | \||| |-|||   \ |  /_
		\_/ \|\____/\_/  \|  \_/  \_/\_/  \|\____\  \____/\_/  \|\_/ \|\_|\_\\____\
	)";
	GotoXY(30, 17);
	SetColor(14);
	cout << "Please wait while the game is loading! ";
	float sum = 1.7;
	while (true)
	{
		SetColor(i);
		GotoXY(93, y);
		cout << int(sum) << "%";
		sum += 1.7;
		GotoXY(x, y);
		cout << static_cast<char>(219);
		if (check == 0) {
			x++;
		}
		if (x == 90) {
			break;
		}
		Sleep(60);
	}
	return 0;
}

void MainMenu(GATE*& gate, vector<POINT>& obstacle) //xay dung menu // ten cu~: main_menu
{
	system("cls");
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
			SetColor(13);
		}
		else {
			SetColor(10);
		}
		cout << R"(
		 _     _     _      _____  _  _      _____   ____  _      ____  _  __ _____
		/ \ /|/ \ /\/ \  /|/__ __\/ \/ \  /|/  __/  / ___\/ \  /|/  _ \/ |/ //  __/
		| |_||| | ||| |\ ||  / \  | || |\ ||| |  _  |    \| |\ ||| / \||   / |  \  
		| | ||| \_/|| | \||  | |  | || | \||| |_//  \___ || | \||| |-|||   \ |  /_ 
		\_/ \|\____/\_/  \|  \_/  \_/\_/  \|\____\  \____/\_/  \|\_/ \|\_|\_\\____\
                                                                           
	)";
		GotoXY(54, 9);
		SetColor(Set[0]);
		cout << "NEW GAME";

		GotoXY(52, 10);
		SetColor(Set[1]);
		cout << "HIGHEST SCORE";

		GotoXY(55, 11);
		SetColor(Set[2]);
		cout << "CONTACT";

		GotoXY(54, 12);
		SetColor(Set[3]);
		cout << "LAST GAME";

		GotoXY(56, 13);
		SetColor(Set[4]);
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
				PlaySound(TEXT("start1.wav"), NULL, SND_FILENAME | SND_ASYNC);
				//LoadingAnimation();
				NewGame(1, gate, obstacle);
				return;
			}
			case 4:
			{
				PlaySound(TEXT("start1.wav"), NULL, SND_FILENAME | SND_ASYNC);
				//LoadingAnimation();
				NewGame(2, gate, obstacle);
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
