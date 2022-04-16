#include"projectPrototype.h"
using namespace std;

char* getFile()
{
	cout << R"(
                  _,.---._     ,---.                        _,---.   ,---.             ___      ,----.  
        _.-.    ,-.' , -  `. .--.'  \      _,..---._    _.='.'-,  \.--.'  \     .-._ .'=.'\  ,-.--` , \ 
      .-,.'|   /==/_,  ,  - \\==\-/\ \   /==/,   -  \  /==.'-     /\==\-/\ \   /==/ \|==|  ||==|-  _.-` 
     |==|, |  |==|   .=.     /==/-|_\ |  |==|   _   _\/==/ -   .-' /==/-|_\ |  |==|,|  / - ||==|   `.-. 
     |==|- |  |==|_ : ;=:  - \==\,   - \ |==|  .=.   ||==|_   /_,-.\==\,   - \ |==|  \/  , /==/_ ,    / 
     |==|, |  |==| , '='     /==/ -   ,| |==|,|   | -||==|  , \_.' )==/ -   ,| |==|- ,   _ |==|    .-'  
     |==|- `-._\==\ -    ,_ /==/-  /\ - \|==|  '='   /\==\-  ,    (==/-  /\ - \|==| _ /\   |==|_  ,`-._ 
     /==/ - , ,/'.='. -   .'\==\ _.\=\.-'|==|-,   _`/  /==/ _  ,  |==\ _.\=\.-'/==/  / / , /==/ ,     / 
     `--`-----'   `--`--''   `--`        `-.`.____.'   `--`------' `--`        `--`./  `--``--`-----`` 
	)";
	SetColor(2);
	for (int i = 0; i < 50; i++)
	{
		GotoXY(i + 38, 10);
		if (i % 2 == 0)
			cout << char(45);
	}
	for (int i = 0; i < 50; i++)
	{
		GotoXY(i + 38, 24);
		if (i % 2 == 0)
			cout << char(45);
	}
	ShowCur(0);
	char** list = NULL;
	list = new char* [10];
	int Set[] = { 12,7,7,7,7,7,7,7,7,7 }; // DEFAULT COLORS
	int counter = 1;
	char key;
	int flag = 0;
	for (int i = 0; i < 10; i++)
	{
		list[i] = new char[50];
	}
	FILE* fin = fopen("SaveLists.txt", "r");
	for (int i = 0; i < 10; i++)
	{
		if (i && strcmp(list[i - 1], "[NONE]") == 0)
		{
			strcpy(list[i], "[NONE]");
		}
		else
		{
			fgets(list[i], 50, fin);
			if (strcmp(list[i], "end") == 0)
			{
				strcpy(list[i], "[NONE]");
			}
			if (list[i][strlen(list[i]) - 1] == '\n')
			{
				list[i][strlen(list[i]) - 1] = '\0';
			}
		}
	}
	fclose(fin);
	//cout << 1 << endl;
	while (true)
	{
		for (int i = 0; i < 10; i++)
		{
			SetColor(Set[i]);
			GotoXY(54, 12 + i);
			cout << list[i];
		}
		key = _getch();

		if ((key == 'W' || key == 'w'))
		{
			counter--;
			if (counter == 0)
				counter = 10;
		}
		if ((key == 'S' || key == 's'))
		{
			counter++;
			if (counter > 10)
				counter = 1;

		}
		if (key == '\r')
		{
			if (strcmp(list[counter - 1], "[NONE]") != 0)
				return *(list + (counter - 1));
		}

		for (int i = 0; i < 10; i++)
		{
			Set[i] = 7;
		}

		if (counter != 0)
		{
			Set[counter - 1] = 12;
		}
	}
}
void ResetDataLoadGame(char* fname, DATA*& dataGame, GATE*& gate, vector<POINT>& obstacle)
{
	//Initialize the global values

	FILE* fin = fopen(fname, "r");
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
	name[len - 4] = '\0';
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
	obstacle.resize(0);
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
	char** savenames = new char* [10];
	for (int i = 0; i < 10; i++)
	{
		savenames[i] = new char[50];
		strcpy(savenames[i], "NONE\n");
	}
	char* name = new char[50];
	char* temp = new char[50];
	bool flag;
	char* spc = new char[30];
	strcpy(spc, "*:<>?/\|~”#%&*:<>?/\{|}");
	// doc du lieu

	GotoXY(30, 9);
	cout << "Enter your username (at least: 1 character and at most: 50 characters):  ";
	GotoXY(40, 10);
	cout << "<<";
	GotoXY(91, 10);
	cout << ">>";
	GotoXY(42, 10);
	ShowCur(1);
	cin.getline(name, 50);
	do
	{
		ShowCur(0);
		flag = false;
		for (int i = 0; i < strlen(name); i++)
			for (int j = 0; j < strlen(spc); j++)
				if (name[i] == spc[j])
					flag = true;
		if (flag == true)
		{
			system("cls");
			GotoXY(30, 9);
			cout << "Your username is invalid. Please rename again ";
			Sleep(1000);
			cout << "                                               ";
			GotoXY(30, 9);
			cout << "Enter your username (at least: 1 character and at most: 50 characters):  ";
			GotoXY(40, 10);
			cout << "<<";
			GotoXY(91, 10);
			cout << ">>";
			GotoXY(42, 10);
			ShowCur(1);
			cin.getline(name, 50);
		}
	} while (flag == true);
	strcat(name, ".txt");
	strcpy(temp, name);
	strcat(temp, "\n");
	ShowCur(0);
	//save game vao file txt
	FILE* fin = fopen("SaveLists.txt", "r+");
	for (int i = 0; i < 10; i++)
	{
		fgets(savenames[i], 50, fin);
		if (strcmp(savenames[i], "NONE") == 0)
			break;
	}
	fclose(fin);
	//kiem tra ten file
	for (int i = 0; i < 10; i++)
		if (strcmp(name, savenames[i]) == 0)
			flag = true;
	if (flag == false)
	{
		for (int i = 9; i > 0; i--)
		{
			savenames[i] = NULL;
			savenames[i] = savenames[i - 1];
		}
		savenames[0] = NULL;
		savenames[0] = temp;
	}
	fin = fopen("SaveLists.txt", "w+");
	for (int i = 0; i < 10; i++)
		fputs(savenames[i], fin);
	fclose(fin);
	//name[strlen(name) - 4] = '\0';
	ofstream f;
	f.open(name, fstream::app);
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
	delete[]savenames;
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
	GotoXY(0, 0);
	SetColor(11);
	//cout << "LeaderBoard";
	cout << R"(
			.____                      .___          __________                       .___
			|    |    ____ _____     __| _/__________\______   \ _________ _______  __| _/
			|    |  _/ __ \\__  \   / __ |/ __ \_  __ \    |  _//  _ \__  \\_  __ \/ __ | 
			|    |__\  ___/ / __ \_/ /_/ \  ___/|  | \/    |   (  <_> ) __ \|  | \/ /_/ | 
			|_______ \___  >____  /\____ |\___  >__|  |______  /\____(____  /__|  \____ | 
			        \/   \/     \/      \/    \/             \/           \/           \/ 
)";
	SetColor(69);
	for (int i = 50; i <= 70; i++)
		for (int j = 10; j <= 29; j++)
		{
			GotoXY(i, j);
			cout << char(177);
		}
	GotoXY(50, 10);
	SetColor(6);
	cout << R"(
 
							  _/  |  
							 / $$ |  
							 $$$$ |  
							   $$ |  
							   $$ |  
							  _$$ |_ 
							 / $$   |
							 $$$$$$/ 
	)";
	SetColor(69);
	for (int i = 12; i <= 32; i++)
		for (int j = 15; j <= 29; j++)
		{
			GotoXY(i, j);
			cout << char(177);
		}
	GotoXY(35, 18);
	SetColor(6);
	cout << R"(
		   ______  
		  /      \ 
		 /$$$$$$  |
		 $$____$$ |
		  /    $$/ 
		 /$$$$$$/  
		 $$ |_____ 
		$$        |
		 $$$$$$$$/ 
	)";
	SetColor(69);
	for (int i = 85; i <= 105; i++)
		for (int j = 18; j <= 29; j++)
		{
			GotoXY(i, j);
			cout << char(177);
		}
	SetColor(6);
	GotoXY(83, 19);
	cout << R"(
											   ______  
											  /      \ 
											 /$$$$$$  |
											 $$ ___$$ |
											   /   $$< 
											  _$$$$$  |
											 /  \__$$ |
											 $$    $$/ 
											  $$$$$$/  
	)";
	SetColor(7);

	GotoXY(57, 8);
	cout << highscore[0].name;//1
	GotoXY(59, 9);
	cout << highscore[0].score;
	GotoXY(19, 13);
	cout << highscore[1].name;//2
	GotoXY(20, 14);
	cout << highscore[1].score;
	GotoXY(92, 16);
	cout << highscore[2].name;//3
	GotoXY(93, 17);
	cout << highscore[2].score;
	std::getchar();
}

