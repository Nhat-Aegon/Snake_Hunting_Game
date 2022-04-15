#include"projectPrototype.h"
using namespace std;

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

	// print the current screen buffer dimensions
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
}
void FixConsoleWindow() { // ham vo hieu khoa viec user thay doi kich thuoc cua so console
	noScrollbar();
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

bool IsValid(DATA*& dataGame, int x, int y, vector<POINT> obstacle) {

	for (int i = 0; i < dataGame->SIZE_SNAKE; i++) {

		if (dataGame->snake[i].x == x && dataGame->snake[i].y == y) {

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
bool IsTouchBody(DATA* dataGame)
{
	for (int i = 0; i < dataGame->SIZE_SNAKE - 1; i++)
	{ // so luong: vd la 4 dot ran
		if (dataGame->snake[dataGame->SIZE_SNAKE - 1].x == dataGame->snake[i].x && dataGame->snake[dataGame->SIZE_SNAKE - 1].y == dataGame->snake[i].y)
		{
			return true;
		}
	}
	return false;
}
bool IsTouchwall(DATA* dataGame, int x_head_position, int y_head_position, vector<POINT>& obstacle)
{
	if (x_head_position <= 4 || y_head_position <= 4 || x_head_position >= dataGame->WIDTH_CONSOLE + 5 || y_head_position >= dataGame->HEIGH_CONSOLE + 4)
		return true;
	for (int i = 0; i < obstacle.size(); i++)
	{
		if (x_head_position == obstacle[i].x && y_head_position == obstacle[i].y)
			return true;
	}
	return false;
}
