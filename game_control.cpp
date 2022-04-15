#include"projectPrototype.h"
using namespace std;

void ProcessDead(DATA* dataGame)
{
	PlaySound(TEXT("die-long.wav"), NULL, SND_FILENAME | SND_ASYNC);
	BlinkSnake(dataGame);
	dataGame->STATE = 0;
	GotoXY(3, dataGame->HEIGH_CONSOLE + 7);
	SetColor(12);
	printf("DEAD!!! Type Y to play again or anykey to exit");
	SetColor(7);
}

void PauseGame(HANDLE t)
{
	SuspendThread(t);
}

void ExitGame(DATA*& dataGame, HANDLE t, GATE*& gate, vector<POINT>& obstacle) {
	int key = 0;
	PauseGame(t);
	system("cls");
	GotoXY(0, 0);
	SetColor(11);
	cout << R"(

  _______ _    _          _   _ _  __ _____   ______ ____  _____    _____  _           __     _______ _   _  _____ 
 |__   __| |  | |   /\   | \ | | |/ // ____| |  ____/ __ \|  __ \  |  __ \| |        /\\ \   / /_   _| \ | |/ ____|
    | |  | |__| |  /  \  |  \| | ' /| (___   | |__ | |  | | |__) | | |__) | |       /  \\ \_/ /  | | |  \| | |  __ 
    | |  |  __  | / /\ \ | . ` |  <  \___ \  |  __|| |  | |  _  /  |  ___/| |      / /\ \\   /   | | | . ` | | |_ |
    | |  | |  | |/ ____ \| |\  | . \ ____) | | |   | |__| | | \ \  | |    | |____ / ____ \| |   _| |_| |\  | |__| |
    |_|  |_|  |_/_/    \_\_| \_|_|\_\_____/  |_|    \____/|_|  \_\ |_|    |______/_/    \_\_|  |_____|_| \_|\_____|
                                                                                                                   
)";
	GotoXY(34, 15);
	SetColor(10);
	cout << "Press M to go back to Main Menu";
	GotoXY(38, 17);
	SetColor(10);
	cout << "Press Esc to exit";
	key = _getch();
	if (key >= 'a' && key <= 'z')
		key -= 32;
	if (key == 'M') //StartGame(1, gate);
	{
		MainMenu(dataGame, gate, obstacle);
	}
	if (key == 27)
	{
		exit(0);
	}
	else
	{
		//ExitGame(handle_t1, gate); // int main thi return 0
		int temp = TerminateThread(t, 0);
		exit(0);
	}
}

void ResetData(DATA*& dataGame, GATE*& gate, vector<POINT>& obstacle) {
	//Initialize the global values
	dataGame->CHAR_LOCK = 'A', dataGame->MOVING = 'D', dataGame->SPEED = 1; dataGame->FOOD_INDEX = 0, dataGame->WIDTH_CONSOLE = 75,
		dataGame->HEIGH_CONSOLE = 20, dataGame->SIZE_SNAKE = 6;
	dataGame->SCORE = 0;
	dataGame->LEVELS = 1;
	gate->isGate = false;
	for (int i = 0; i < 6; i++)
		gate->g[i] = { 0,0 };
	gate->countGate = 1;
	obstacle.resize(0);
	// Initialize default values for snake
	dataGame->snake[0] = { 10, 5 }; dataGame->snake[1] = { 11, 5 }; // khoi tao giao tri cho ran
	GenerateFood(dataGame, obstacle);
	for (int i = 0; i < dataGame->SIZE_SNAKE; i++)
	{
		dataGame->snake[dataGame->SIZE_SNAKE - i - 1].x = 15 - i;
		dataGame->snake[dataGame->SIZE_SNAKE - i - 1].y = 7;
	}
}
void ThreadFunc(DATA*& dataGame, GATE*& gate, vector<POINT>& obstacle) {
	while (true) {
		if (dataGame->STATE == 1) {//If my snake is alive
			char* c = new char[2];
			strcpy(c, " ");
			DrawSnakeAndFoodBefore(dataGame, c, gate);
			switch (dataGame->MOVING) {
			case 'A':
				MoveLeft(dataGame, gate, obstacle);
				break;
			case 'D':
				MoveRight(dataGame, gate, obstacle);
				break;
			case 'W':
				MoveUp(dataGame, gate, obstacle);
				break;
			case 'S':
				MoveDown(dataGame, gate, obstacle);
				break;
			}
			strcpy(c, "0");
			DrawSnakeAndFoodAfter(dataGame, gate);
			Sleep(200 / dataGame->SPEED);
		}
	}
}
void StartGame(DATA*& dataGame, int x, GATE*& gate, vector<POINT>& obstacle) {
	system("cls"); // clear screen
	if (x == 1) ResetData(dataGame, gate, obstacle); // Intialize original data
	else
	{
		char* fname = getFile();
		system("cls");
		ResetDataLoadGame(fname, dataGame, gate, obstacle);
		PlaySound(TEXT("start1.wav"), NULL, SND_FILENAME | SND_ASYNC);
		LoadingAnimation();
	}
	system("cls");
	DrawBoard(dataGame, 4, 4, dataGame->WIDTH_CONSOLE, dataGame->HEIGH_CONSOLE, obstacle); // Draw game
	if (gate->isGate)
	{
		for (int i = 0; i < 5; i++)
		{
			GotoXY(gate->g[i].x, gate->g[i].y);
			cout << char(177);
		}
	}
	UpperSnakes();
	GameGuide();
	DrawScoreAndLevels(dataGame);
	dataGame->STATE = 1;//Start running Thread    
}

void NewGame(DATA*& dataGame, int x, GATE*& gate, vector<POINT>& obstacle)
{
	StartGame(dataGame, x, gate, obstacle);
	//std:thread r([=]() {ThreadFunc(gate, obstacle); return 1; });
	std::thread t1(ThreadFunc, std::ref(dataGame), std::ref(gate), std::ref(obstacle)); //Create thread for snake
	HANDLE handle_t1 = t1.native_handle(); //Take handle of thread
	int isPauseGame = 0;
	while (true) {
		int temp = 0;
		if (!dataGame->STATE)
		{
			temp = _getch();
			if (temp >= 'a' && temp <= 'z')
				temp -= 32;
			if (temp == 'Y') StartGame(dataGame, 1, gate, obstacle);
			else
			{
				ExitGame(dataGame, handle_t1, gate, obstacle); // int main thi return 0
			}
		}
		else if (dataGame->STATE) {
			if (_kbhit())
			{
				temp = _getch();
				if (temp >= 'a' && temp <= 'z')
					temp -= 32;
			}
			if (temp == 'L')
			{
				PauseGame(handle_t1);
				SaveGame(dataGame, gate, obstacle);
				ExitGame(dataGame, handle_t1, gate, obstacle);
			}
			else if (temp == ' ' && !isPauseGame) {
				PauseGame(handle_t1);
				SetColor(12);
				GotoXY(4, dataGame->HEIGH_CONSOLE + 6);
				cout << "YOU ARE PAUSING GAME!! Press SPACE or W,A,D,S to continue playing";
				SetColor(7);
				isPauseGame = 1;
			}
			else if (temp == 27) {
				ExitGame(dataGame, handle_t1, gate, obstacle);
				return; // int main**
			}
			else {
				//ResumeThread(handle_t1); //neu de day thi khong the bam pause duoc
				if (temp == ' ' && isPauseGame)
				{
					switch (dataGame->CHAR_LOCK)
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
					GotoXY(4, dataGame->HEIGH_CONSOLE + 6);
					cout << "                                                                   ";
					isPauseGame = 2;
				}
				if ((temp != dataGame->CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S'))
				{
					if (isPauseGame)
					{
						GotoXY(4, dataGame->HEIGH_CONSOLE + 6);
						cout << "                                                                   ";
						isPauseGame = 0;
					}
					ResumeThread(handle_t1); //de day thi bam pause duoc nhung so lan bam "P" phai tuong ung so lan bam chuyen dong ve sau thi moi chuyen dong tiep duoc
					if (temp == 'D') dataGame->CHAR_LOCK = 'A';
					else if (temp == 'W') dataGame->CHAR_LOCK = 'S';
					else if (temp == 'S') dataGame->CHAR_LOCK = 'W';
					else dataGame->CHAR_LOCK = 'D';
					dataGame->MOVING = temp;
				}
			}
		}
	}
}
