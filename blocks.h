#ifndef BLOCKS_H
#define BLOCKS_H
#include <easyx/easyx.h>
#include <easyx/graphics.h>

const int sideLength = 1;
const int playAreaRow = 10;
const int playAreaCol = 15;
const int resolutionRow = 540;
const int resolutionCol = 960;
const int resolutionRatio = resolutionRow / 64;
int** matrixRotate(const int** mat, int r, int c);
void freeMatrixMemory(int** mat, int r);

//定义游戏类
class Game
{
private:
	int score;
	int time;
	bool movingPart;
	double difficulty;
	int playArea[playAreaRow][playAreaCol];
public:
	Game(int, int, double);
	~Game();
	void clearPlayArea();
	int getScore();
	int getTime();
	double getDifficulty();
	void newPart();
	void deleteLine();
	void gameInit();
	void gameDrawHomeUI();
	void gameDrawSettingUI();
	void gameDrawPlayUI();
	void gameStart();
	void gameRestart();
	void gameQuit();
	void gameSetting();
	void gameClose();
	void playDraw();
};

//定义组成图形的方块类
class Block
{
private:
	int posX;
	int posY;
	COLORREF color;
public:
	Block(int, int, COLORREF);
	~Block();
	int getBlockPosX();
	int getBlockPosY();
};

class Parts
{
protected:
	COLORREF color;
public:
	Parts(COLORREF);
	virtual void partRotate();
};

class PartZ : public Parts
{
public:
	void partRotate();
};

class PartS : public Parts
{
public:
	void partRotate();
};

class PartL : public Parts
{
public:
	void partRotate();
};

class PartJ : public Parts
{
public:
	void partRotate();
};

class PartO : public Parts
{
public:
	void partRotate();
};

class PartT : public Parts
{
public:
	void partRotate();
};

class PartI : public Parts
{
public:
	void partRotate();
};

#endif
