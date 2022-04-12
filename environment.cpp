#include"projectPrototype.h"
using namespace std;

void DrawScoreAndLevels(DATA* dataGame)// ve ra bang score ban dau
{
	SetColor(7);
	GotoXY(92, 6);
	cout << "LEVELS: " << dataGame->level << endl;
	GotoXY(92, 7);
	cout << "SCORE: " << dataGame->SCORE << endl;
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
	GotoXY(dataGame->snake[dataGame->SIZE_SNAKE-1].x, dataGame->snake[dataGame->SIZE_SNAKE - 1].y);
	SetColor(3);
	switch (dataGame->MOVING)
	{
	case 'W':
	{
		cout << char(30);
		break;
	}
	case 'S':
	{
		cout << char(31);
		break;
	}
	case 'A':
	{
		cout << char(17);
		break;
	}
	case 'D':
	{
		cout << char(16);
		break;
	}
	}
	SetColor(7);
	for (int i = dataGame->SIZE_SNAKE - 2; i >= 0; i--) {
		GotoXY(dataGame->snake[i].x, dataGame->snake[i].y);
		cout << ID[dataGame->SIZE_SNAKE - i - 1];
	}
	GotoXY(dataGame->snake[dataGame->SIZE_SNAKE - 1].x, dataGame->snake[dataGame->SIZE_SNAKE - 1].y);
}
void TriAngle(DATA*& dataGame, GATE*& gate, vector<POINT>& obstacle)
{
	int i = 0;
	int count = 0;
	while (count!=11)
	{
		count++;
		system("cls");
		SetColor(i);
		GotoXY(0, 0);
		cout << R"(
                $$\     $$\  $$$$$$\  $$\   $$\       $$\      $$\  $$$$$$\  $$\   $$\ 
                \$$\   $$  |$$  __$$\ $$ |  $$ |      $$ | $\  $$ |$$  __$$\ $$$\  $$ |
                 \$$\ $$  / $$ /  $$ |$$ |  $$ |      $$ |$$$\ $$ |$$ /  $$ |$$$$\ $$ |
                  \$$$$  /  $$ |  $$ |$$ |  $$ |      $$ $$ $$\$$ |$$ |  $$ |$$ $$\$$ |
                   \$$  /   $$ |  $$ |$$ |  $$ |      $$$$  _$$$$ |$$ |  $$ |$$ \$$$$ |
                    $$ |    $$ |  $$ |$$ |  $$ |      $$$  / \$$$ |$$ |  $$ |$$ |\$$$ |
                    $$ |     $$$$$$  |\$$$$$$  |      $$  /   \$$ | $$$$$$  |$$ | \$$ |
                    \__|     \______/  \______/       \__/     \__| \______/ \__|  \__|
    )";
		
		i = (i + 1) % 9;
		SetColor(i);
		GotoXY(0, 11);
		cout << R"(

         /$$$$$$$   /$$$$$$  /$$   /$$       /$$        /$$$$$$        /$$   /$$ /$$   /$$  /$$$$$$  /$$$$$$$$
        | $$__  $$ /$$__  $$| $$$ | $$      | $$       /$$__  $$      | $$$ | $$| $$  | $$ /$$__  $$|__  $$__/
        | $$  \ $$| $$  \ $$| $$$$| $$      | $$      | $$  \ $$      | $$$$| $$| $$  | $$| $$  \ $$   | $$   
        | $$$$$$$ | $$$$$$$$| $$ $$ $$      | $$      | $$$$$$$$      | $$ $$ $$| $$$$$$$$| $$$$$$$$   | $$   
        | $$__  $$| $$__  $$| $$  $$$$      | $$      | $$__  $$      | $$  $$$$| $$__  $$| $$__  $$   | $$   
        | $$  \ $$| $$  | $$| $$\  $$$      | $$      | $$  | $$      | $$\  $$$| $$  | $$| $$  | $$   | $$   
        | $$$$$$$/| $$  | $$| $$ \  $$      | $$$$$$$$| $$  | $$      | $$ \  $$| $$  | $$| $$  | $$   | $$   
        |_______/ |__/  |__/|__/  \__/      |________/|__/  |__/      |__/  \__/|__/  |__/|__/  |__/   |__/   
                                                                                                                                                                     
    )";
		if (count < 10) Sleep(1000);
	}
	SetColor(7);
	GotoXY(38, 22);
	cout << "THANKS FOR PLAYING" << endl;
	GotoXY(33, 23);
	cout << "Press M to go back to Main Menu or ESC to exit game";
	int key = 0;
	key = _getch();
	if (key >= 'a' && key <= 'z')
		key -= 32;
	if (key == 'M') //StartGame(1, gate);
	{
		MainMenu(dataGame, gate, obstacle);
		return;
	}
	else
	{
		//ExitGame(handle_t1, gate); // int main thi return 0
		exit(0);
	}
}
