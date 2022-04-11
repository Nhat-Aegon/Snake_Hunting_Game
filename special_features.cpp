#include"projectPrototype.h"
using namespace std;

void ResetDataLoadGame(DATA*& dataGame, GATE*& gate, vector<POINT>& obstacle)
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

	fscanf_s(fin, "%d", &dataGame->SIZE_SNAKE);

	for (int i = 0; i < dataGame->SIZE_SNAKE; i++)
	{
		fscanf_s(fin, "%d %d", &dataGame->snake[i].x, &dataGame->snake[i].y);
	}

	fscanf_s(fin, "%d", &dataGame->SPEED);

	fscanf_s(fin, "%d", &dataGame->LEVELS);

	fscanf_s(fin, "%d", &dataGame->SCORE);

	int temp = 0, temp1 = 0;
	fscanf_s(fin, "%d %d", &temp, &temp1);
	dataGame->MOVING = char(temp);
	dataGame->CHAR_LOCK = char(temp1);
	fscanf_s(fin, "%d", &dataGame->FOOD_INDEX);
	for (int i = 0; i <= dataGame->FOOD_INDEX; i++)
	{
		fscanf_s(fin, "%d %d", &dataGame->food[i].x, &dataGame->food[i].y);
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

	dataGame->WIDTH_CONSOLE = 75;
	dataGame->HEIGH_CONSOLE = 20;
}
void SaveGame(DATA* dataGame, GATE* gate, vector<POINT>obstacle)
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
	f << dataGame->SIZE_SNAKE << endl;
	for (int i = 0; i < dataGame->SIZE_SNAKE; i++)
	{
		f << dataGame->snake[i].x << ' ' << dataGame->snake[i].y << ' ';
	}
	f << endl;
	f << dataGame->SPEED << endl;
	f << dataGame->LEVELS << endl;
	f << dataGame->SCORE << endl;
	f << int(dataGame->MOVING) << endl;
	f << int(dataGame->CHAR_LOCK) << endl;
	f << dataGame->FOOD_INDEX << endl;
	for (int i = 0; i <= dataGame->FOOD_INDEX; i++)
	{
		f << dataGame->food[i].x << ' ' << dataGame->food[i].y << endl;
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
	ConfigHighscore(dataGame->SCORE, name);
	f.close();
	if (!f)
		cout << "Can't save your file, please try another options!";
	delete[]filePath;
	delete[]name;
}
void ScoreAndLevels(DATA*& dataGame) //ham su dung bat dau tinh diem va level khi ran an
{
	dataGame->SCORE += 100;
	if (dataGame->SCORE % 300 == 0)
		dataGame->LEVELS++;
	SetColor(7);
	GotoXY(92, 6);
	cout << "LEVELS: " << dataGame->LEVELS << endl;
	GotoXY(92, 7);
	cout << "SCORE: " << dataGame->SCORE << endl;
}
void BlinkSnake(DATA* dataGame) //hieu ung nhap nhay con ran
{
	for (int j = 0; j < 5; j++)
	{
		Sleep(200);
		for (int i = 0; i < dataGame->SIZE_SNAKE; i++)
		{
			GotoXY(dataGame->snake[i].x, dataGame->snake[i].y);
			cout << ID[i];
		}
		Sleep(100);
		for (int i = 0; i < dataGame->SIZE_SNAKE; i++)
		{
			GotoXY(dataGame->snake[i].x, dataGame->snake[i].y);
			cout << " ";
		}
	}
}
void ConfigHighscore(int SCORE, char* name)
{

	HIGHSCORE* highscore = new HIGHSCORE[3];
	FILE* fin = fopen("savehighscore.txt", "r+");
	for (int i = 0; i < 3; i++)
	{
		fgets((highscore + i)->name, 50, fin);
		fscanf_s(fin, "%d\n", &(highscore + i)->score);
	}
	fclose(fin);

	for (int i = 0; i < 3; i++)
		if (SCORE > (highscore + i)->score)
		{

			if (i == 0)
			{
				(highscore + 2)->name = (highscore + 1)->name;
				(highscore + 2)->score = (highscore + 1)->score;
				(highscore + 1)->name = (highscore)->name;
				(highscore + 1)->score = (highscore)->score;
			}
			if (i == 1)
			{
				(highscore + 2)->name = (highscore + 1)->name;
				(highscore + 2)->score = (highscore + 1)->score;
			}
			(highscore + i)->name = name;
			(highscore + i)->score = SCORE;
			break;
		}
	fin = fopen("savehighscore.txt", "w+");
	for (int i = 0; i < 3; i++)
	{
		fputs((highscore + i)->name, fin);
		if ((highscore + i)->name[strlen((highscore + i)->name) - 1] != '\n')
			fprintf(fin, "\n");
		fprintf(fin, "%d\n", (highscore + i)->score);
	}
	fclose(fin);
	delete[]highscore;
}

void writeHighScore()
{
	system("cls");
	int n;
	HIGHSCORE* highscore = new HIGHSCORE[3];
	FILE* fin = fopen("savehighscore.txt", "r+");
	for (int i = 0; i < 3; i++)
	{
		fgets((highscore + i)->name, 50, fin);
		fscanf_s(fin, "%d\n", &(highscore + i)->score);
	}
	fclose(fin);
	GotoXY(52, 1);
	SetColor(60);

	cout << "* Leaderboard *";
	
	SetColor(69);

	for (int i = 50; i <= 70; i++)
		for (int j = 10; j <= 29; j++)
		{
			GotoXY(i, j);
			cout << char(177);
		}
	for (int i = 15; i <= 35; i++)
		for (int j = 15; j <= 29; j++)
		{
			GotoXY(i, j);
			cout << char(177);
		}
	for (int i = 85; i <= 105; i++)
		for (int j = 20; j <= 29; j++)
		{
			GotoXY(i, j);
			cout << char(177);
		}
	SetColor(7);

	GotoXY(56, 8);
	cout << highscore[0].name;
	GotoXY(56, 9);
	cout << highscore[0].score;
	GotoXY(21, 13);
	cout << highscore[1].name;
	GotoXY(21, 14);
	cout << highscore[1].score;
	GotoXY(92, 18);
	cout << highscore[2].name;
	GotoXY(92, 19);
	cout << highscore[2].score;
	std::getchar();
}
