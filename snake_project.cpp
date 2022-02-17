#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<Windows.h> //Mot header cua Windows, chua cac ham trong windows api
#include<thread>
#include<conio.h>
#include<stdlib.h>
using namespace std;
#define MAX_SIZE_SNAKE 20
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

void DrawSnakeAndFoodBefore(char* str) {
	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);	//di chuyển tới vị trí x,y(food_index)
	if (str == " ")
		cout << str;

	for (int i = 0; i < SIZE_SNAKE; i++) {	//chạy vòng lặp để vẽ rắn
		GotoXY(snake[i].x, snake[i].y);	//di chuyển tới vị trí vòng lặp của rắn
		cout << ' ';
	}
}
void DrawSnakeAndFoodAfter() {
	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);	//di chuyển tới vị trí x,y(food_index)
	cout << ID[SIZE_SNAKE];

	for (int i = 0; i < SIZE_SNAKE; i++) {	//chạy vòng lặp để vẽ rắn
		GotoXY(snake[i].x, snake[i].y);	//di chuyển tới vị trí vòng lặp của rắn
		cout << ID[i];
	}
}

bool IsValid(int x, int y){

	for (int i = 0; i < SIZE_SNAKE; i++) {

		if (snake[i].x == x && snake[i].y == y) {

			return false;

		}
	}
	return true;
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

	if (FOOD_INDEX == MAX_SIZE_FOOD - 1)

	{

		FOOD_INDEX = 0;
		SIZE_SNAKE = 6;

		if (SPEED == MAX_SPEED) SPEED = 1;

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
	STATE = 0;												// Thay đổi trạng thái của rắn từ 1 sang 0 (sống sang chết), ngăn vòng lập vẽ rắn
	GotoXY(0, HEIGH_CONSOLE + 2);							// Đi đến vị trí x = 0; y = (độ cao của console + 2) 
	printf("Dead, type y to continue or anykey to exit");	/* In ra dong chữ cho người chơi chọn : y để chơi tiếp và phím khác để thoát, lấy dữ liệu
															cho cấu trúc rẽ nhánh StartGame hoặc ExitGame*/
}

void MoveRight()											/* Hàm di chuyển sang phải */
{
	if (snake[SIZE_SNAKE - 1].x + 1 == WIDTH_CONSOLE)		// Toạ độ x của đầu rắn bằng biên phải console => va chạm tường
	{
		ProcessDead();										// => Rắn bị chết, gọi hàm ProcessDead
	}
	else
	{
		if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) // Toạ độ đầu rắn trùng với toạ độ đồ ăn
		{
			Eat();											// => Ăn, gọi hàm Eat
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;					// Di chuyển các phần tử của rắn theo trục x 
			snake[i].y = snake[i + 1].y;					// Di chuyển các phần tử của rắn theo trục y
															// => Phần tử đứng sau lấy toạ độ của phần tử đứng trước => Xoá phần tử cuối)
		}
		snake[SIZE_SNAKE - 1].x++;							// Di chuyển đầu rắn sang phải 1 đơn vị
	}
}
void MoveLeft()												/* Hàm di chuyển sang trái */
{
	if (snake[SIZE_SNAKE - 1].x - 1 == 0)					// Toạ độ x của đầu rắn bằng biên trái của console => va chạm
	{
		ProcessDead();										// => Rắn bị chết, gọi hàm ProcessDead
	}
	else {
		if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) // Toạ độ đầu rắn trùng với toạ độ đồ ăn
		{
			Eat();											// => Ăn, gọi hàm Eat
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;					// Di chuyển các phần tử của rắn theo trục x
			snake[i].y = snake[i + 1].y;					// Di chuyển các phần tử của rắn theo trục y
															// => Phần tử đứng sau lấy toạ độ của phần tử đứng trước => Xoá phần tử cuối)
		}
		snake[SIZE_SNAKE - 1].x--;							// Di chuyển đầu rắn sang trái 1 đơn vị
	}
}
void MoveDown()												/* Hàm di chuyển xuóng dưới */
{
	if (snake[SIZE_SNAKE - 1].y + 1 == HEIGH_CONSOLE)		// Toạ độ y của đầu rắn bằng biên dưới console => va chạm
	{
		ProcessDead();										// => Rắn bị chết, gọi hàm ProcessDead
	}
	else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y) // Toạ độ đầu rắn trùng với toạ độ đồ ăn
		{
			Eat();											// => Ăn, gọi hàm Eat
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;					// Di chuyển các phần tử của rắn theo trục x
			snake[i].y = snake[i + 1].y;					// Di chuyển các phần tử của rắn theo trục y
															// => Phần tử đứng sau lấy toạ độ của phần tử đứng trước => Xoá phần tử cuối)
		}
		snake[SIZE_SNAKE - 1].y++;							// Di chuyển đầu rắn xuống dưới 1 đơn vị
	}
}
void MoveUp()												/* Hàm di chuyển lên trên */
{
	if (snake[SIZE_SNAKE - 1].y - 1 == 0)					// Toạ độ y của đầu rắn bằng biên trên console => va chạm
	{
		ProcessDead();										// => Rắn bị chết, gọi hàm ProcessDead
	}
	else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y)	// Toạ độ đầu rắn trùng với toạ độ đồ ăn
		{
			Eat();											// => Ăn, gọi hàm Eat
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;					// Di chuyển các phần tử của rắn theo trục x 
			snake[i].y = snake[i + 1].y;					// Di chuyển các phần tử của rắn theo trục y 
															// => Phần tử đứng sau lấy toạ độ của phần tử đứng trước => Xoá phần tử cuối)
		}
		snake[SIZE_SNAKE - 1].y--;							// Di chuyển đầu rắn lên trên 1 đơn vị
	}
}

void ThreadFunc() {
    while (true) {
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
  // dau ran nam o vi tri snake[5]
   GenerateFood();
   for (int i = 0; i < 6; i++)
   {
       snake[6-i-1].x = 15 - i;
       snake[6-i-1].y = 5;
   }
}
void StartGame() {
    system("cls"); // clear screen
    ResetData(); // Intialize original data
    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE); // Draw game
	
    STATE = 1;//Start running Thread    
}

//int main()
//{
//    FixConsoleWindow();
//    StartGame();
//	thread t1(ThreadFunc); //Create thread for snake
//		HANDLE handle_t1 = t1.native_handle(); //Take handle of thread
//		while (true) {
//			int temp = 0;
//			if (_kbhit())
//			{
//				temp = _getch();
//				if (temp >= 'a' && temp <= 'z')
//					temp -= 32;
//			}
//			if (STATE == 1) {
//				if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp =='W' || temp == 'S'))
//				{
//					if (temp == 'D') CHAR_LOCK = 'A';
//					else if (temp == 'W') CHAR_LOCK = 'S';
//					else if (temp == 'S') CHAR_LOCK = 'W';
//					else CHAR_LOCK = 'D';
//					MOVING = temp;
//				}
//			}
//			else break;
//		}
//}
void ExitGame(HANDLE t) {
	system("cls");
	TerminateThread(t, 0);
}
//Function pause game
void PauseGame(HANDLE t) {
	SuspendThread(t);
}
void main()
{
	FixConsoleWindow();
	StartGame();
	thread t1(ThreadFunc); //Create thread for snake
	HANDLE handle_t1 = t1.native_handle(); //Take handle of thread
	while (true) {
		int temp = 0;
		if (_kbhit())
		{
			temp = _getch();
			if (temp >= 'a' && temp <= 'z')
				temp -= 32;
		}
		if (STATE == 1) {
			if (temp == 'P') {
				PauseGame(handle_t1);
			}
			else if (temp == 27) {
				ExitGame(handle_t1);
				return; // int main**
			}
			else {
				//ResumeThread(handle_t1); //neu de day thi khong the bam pause duoc
				if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S'))
				{
					ResumeThread(handle_t1); //de day thi bam pause duoc nhung so lan bam "P" phai tuong ung so lan bam chuyen dong ve sau thi moi chuyen dong tiep duoc
					if (temp == 'D') CHAR_LOCK = 'A';
					else if (temp == 'W') CHAR_LOCK = 'S';
					else if (temp == 'S') CHAR_LOCK = 'W';
					else CHAR_LOCK = 'D';
					MOVING = temp;
				}
			}
		}
		else {
			if (temp == 'Y') StartGame();
			else
			{
				return; // int main thi return 0
			}
		}
	}
}
