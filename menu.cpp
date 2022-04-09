﻿#include"projectPrototype.h"
using namespace std;

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
int Contact(vector<POINT>& obstacle) {
	system("cls");
	const int BorX = 20;
	const int BorY = 2;
	const int Wide = 50;
	const int Height = 17;
	const int X = BorX + 2 + 2 + 1 + 1;
	const int Y = Height + BorY;

	int i = 1;
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	for (int i = Y; i > -Y; i--)
	{
		GotoXY(0, 0);
		cout << R"(
	   Y
	  (")
	   \\
	    \\
	     ))
	    //
	   //
	  ((
	   \\
	    \\
	     \\
	      ))
	     //
	    //
	   //
	  ((
	   \\
	    \\
	     V
)";

		GotoXY(0, 0);
		cout << R"(
												     Y
												    (")
												    //
												   //
												  ((
												   \\
												    \\
												     ))
												    //
												   // 
												  //
												 ((
												  \\
												   \\
												    \\
												     ))
												    //
												   //
												   V
)";



		int j = 0;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X + 10, i + (j));
			cout << u8"        DO AN KI THUAT LAP TRINH                             ";

		}; j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                             ";
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X + 10, i + (j));
			if (i + j <= Y)
				cout << u8"             HUNTING SNAKE                                   ";

		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                             ";
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                             ";
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"              Truong Dai hoc Khoa hoc Tu nhien               ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                              ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                          21CLC01                             ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                              ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                              ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                   Giang vien huong dan                       ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y) cout << u8"                                             ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                     Truong Toan Thinh                  ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                          Nhom 4                        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y) cout << u8"                                            ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                        Thanh vien:                     ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                       Bui Minh Nhat                    ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                     Tran Ha Minh Nhat                  ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                      Tran Dinh Trung                   ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                    Nguyen Vu Minh Khoi                 ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"			                  __        ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"			      _______    /*_>-<     ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"			  ___/ _____ \__/ /         ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"			 <____/     \____/          ";
			;
		}j++;
		if (i + j > BorY && i + j < Y)
		{
			GotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                                        ";
			;
		}j++;
		Sleep(500);
	}



	SetConsoleOutputCP(old_cp);

	return 0;
}
void MainMenu(DATA*& dataGame, GATE*& gate, vector<POINT>& obstacle) //xay dung menu 
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
		GotoXY(10, 13);
		if (i) {
			SetColor(13);
		}
		else {
			SetColor(10);
		}
		UINT old_cp = GetConsoleOutputCP();
		SetConsoleOutputCP(CP_UTF8);
		GotoXY(10, 13);
		cout << u8"          ██████████          ";
		GotoXY(10, 14);
		cout << u8"        ██░░░░░░░░░░██        ";
		GotoXY(10, 15);
		cout << u8"       ██░░░░░░░░░░░░██       ";
		GotoXY(10, 16);
		cout << u8"      ██░░██░░░░░░██░░██      ";
		GotoXY(10, 17);
		cout << u8"     ██░░██░░░░░░██░░▒▒██     ";
		GotoXY(10, 18);
		cout << u8"     ██░░░░░░░░░░░░░░▒▒██     ";
		GotoXY(10, 19);
		cout << u8"       ██▒▒▒▒▒▒▒▒▒▒▒▒██       ";
		GotoXY(10, 20);
		cout << u8"        ██████████████        ";
		GotoXY(10, 21);
		cout << u8"    ████░░░░██░░░░▒▒████      ";
		GotoXY(10, 22);
		cout << u8"  ██░░░░░░██░░░░░░▒▒██▒▒██    ";
		GotoXY(10, 23);
		cout << u8"██░░░░██▒▒▒▒▒▒▒▒▒▒██░░▒▒▒▒██  ";
		GotoXY(10, 24);
		cout << u8"██▒▒░░░░██████████░░░░▒▒██▒▒██";
		GotoXY(10, 25);
		cout << u8"██▒▒░░░░░░░░░░░░░░░░░░▒▒██▒▒██";
		GotoXY(10, 26);
		cout << u8"  ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████▒▒██";
		GotoXY(10, 27);
		cout << u8"    ██████████████████    ██  ";

		SetConsoleOutputCP(old_cp);

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
				LoadingAnimation();
				NewGame(dataGame, 1, gate, obstacle);
				return;
			}
			case 2:
			{
				writeHighScore();
				MainMenu(dataGame, gate, obstacle);
				return;
			}
			case 3:
			{

				int temp = Contact(obstacle);
				MainMenu(dataGame,gate, obstacle);
				return;
			}
			case 4:
			{
				PlaySound(TEXT("start1.wav"), NULL, SND_FILENAME | SND_ASYNC);
				LoadingAnimation();
				NewGame(dataGame, 2, gate, obstacle);
				return;
			}
			return;
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

