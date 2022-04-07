#include<iostream>
#include"projectPrototype.h"
using namespace std;
int main()
{
	DATA *dataGame = new DATA();
	vector<POINT> obstacle;
	obstacle.resize(0);
	GATE* gate = new GATE();
	ShowCur(0);
	FixConsoleWindow();
	MainMenu(dataGame,gate, obstacle);
	delete gate;
	return 0;
}


