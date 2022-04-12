#define _CRT_SECURE_NO_WARNINGS 1
//#include<stdlib.h>

#include <iostream>
#include<windows.h> //Mot header cua Windows, chua cac ham trong windows api
#include<conio.h>
#include<fstream>
#include<string.h>
#include <vector>
#include<thread>
using std::vector;

#define MAX_SIZE_SNAKE 8
#define MAX_SIZE_FOOD 10
#define MAX_SPEED 3
const char ID[33] = {char(16),'2','1','1','2','7','1','2','6','2','1','1','2','7','5','1','8','2','1','1','2','7','6','5','8','2','1','1','2','7','5','5','9'};

struct DATA {
	POINT snake[32]; //snake
	POINT food[10]; // food
	int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is  one direction my snake cannot move to)
	int MOVING;//used to determine the direction my snake moves (At a moment, there are three directions my snake can move)
	int SPEED;// Standing for level, the higher the level, the quicker the speed
	int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
	int FOOD_INDEX = -1; // current food-index
	int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size maybe 32)
	int STATE; // State of snake: dead or alive
	bool gate = false;
	int SCORE;
	int LEVELS = 1;
};

struct GATE
{
	POINT g[6] = { 0 };
	bool isGate = false;
	int countGate = 1;
};
struct HIGHSCORE
{
	char* name = new char[50];
	int score = 0;
};

void GameGuide();
int Contact(vector<POINT>& obstacle);
void GotoXY(int x, int y);
void FixConsoleWindow();
void ShowCur(bool CursorVisibility);
void SetColor(int color);
void TextBackGround(int color);
bool IsValid(DATA *&dataGame,int x, int y, vector<POINT> obstacle);
void GenerateFood(DATA *&dataGame,vector<POINT>& obstacle);
void DrawBoard(DATA *dataGame,int x, int y, int width, int height, vector<POINT> obstacle);
void DrawSnakeAndFoodBefore(DATA *& dataGame,char* str, GATE*& gate);
void DrawSnakeAndFoodAfter(DATA *& dataGame,GATE*& gate);
void DrawNGate(int x, int y);
void DrawEGate(int x, int y);
void DrawSGate(int x, int y);
void DrawWGate(int x, int y);
void DrawAndAssignGate(int x0, int y0, char drt, GATE*& gate);
void ProcessGate(DATA*dataGame,GATE*& gate, vector<POINT> obstacle);
void CreateMap(vector<POINT>& obstacle, int countGate);
void TransitionNewMap(DATA *&dataGame,POINT snake[], GATE*& gate, vector<POINT>& obstacle);
int IsGateTouch(DATA *&dataGame,POINT snake[], GATE*& gate, vector<POINT>& obstacle);
void BlinkSnake(DATA *dataGame);
void DrawScoreAndLevels(DATA*dataGame);
void ScoreAndLevels(DATA *&dataGame);
void ProcessDead(DATA *dataGame);
void PauseGame(HANDLE t);
//void ExitGame(HANDLE t);
void ExitGame(DATA *&dataGame,HANDLE t, GATE*& gate,vector<POINT>&obstacle);
void SaveGame(DATA *dataGame,GATE* gate, vector<POINT>obstacle);
void ConfigHighscore(int SCORE, char* name);
void writeHighScore();
void Eat(DATA *&dataGame,GATE*& gate, vector<POINT> obstacle);
bool IsTouchBody(DATA *dataGame);
bool IsTouchwall(DATA *dataGame,int x_head_position, int y_head_position, vector<POINT>& obstacle);
void MoveRight(DATA *&dataGame,GATE*& gate, vector<POINT> &obstacle);
void MoveLeft(DATA*& dataGame, GATE*& gate, vector<POINT> &obstacle);
void MoveDown(DATA*& dataGame, GATE*& gate, vector<POINT> &obstacle);
void MoveUp(DATA*& dataGame, GATE*& gate, vector<POINT> &obstacle);
void ResetData(DATA*& dataGame, GATE*& gate, vector<POINT>& obstacle);
void ThreadFunc(DATA*& dataGame, GATE*& gate, vector<POINT>& obstacle);
void ResetDataLoadGame(DATA*& dataGame, GATE*& gate, vector<POINT>& obstacle);
void StartGame(DATA*& dataGame, int x, GATE*& gate, vector<POINT>& obstacle);
void NewGame(DATA*& dataGame, int x, GATE*& gate, vector<POINT>& obstacle);
int UpperSnakes();
int LoadingAnimation();
void MainMenu(DATA*& dataGame, GATE*& gate, vector<POINT>& obstacle);
void TriAngle(DATA *&dataGame, GATE*&gate, vector<POINT>&obstacle);
