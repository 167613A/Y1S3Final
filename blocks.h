#ifndef BLOCKS_H
#define BLOCKS_H
#include <easyx/easyx.h>
#include <easyx/graphics.h>

const int sideLength = 3;
const int playAreaCol = 10;
const int playAreaRow = 16;
const int resolutionRow = 540;
const int resolutionCol = 960;
const int resolutionRatio = resolutionRow / 64;
const COLORREF ORANGE = 0x00A8FF;

class Matrix
{
private:
	int** data;
	int row;
	int col;
	void matrixAllocate(int, int);
	void matrixDeallocate();
public:
	Matrix(int, int);
	~Matrix();
	int& getData(int, int);
	int getRow();
	int getCol();
	Matrix matrixRotate() const;
	void matrixPrint() const;
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
	void drawBlock(int);
};

class Parts
{
protected:
	COLORREF color;
	Matrix cur;
	Matrix ori;
	Matrix rot;
	int rtTimes;
	int bottomRow;
public:
	Parts(COLORREF, int);
	virtual ~Parts();
	void partSetColor();
	int getBottomRow();
	virtual void partRotate();
	void matrixPartRotate(int**, int**, int**, int, int);
	void partDrop();
	void partMoveLeft();
	void partMoveRight();
	void partBottom();
};

//定义游戏类
class Game
{
private:
	int score;
	int time;
	bool movingPart;
	double difficulty;
	int playArea[playAreaCol][playAreaRow];
	Parts currentPart;
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

class PartZ : public Parts
{
public:
	PartZ(COLORREF);
	~PartZ();
	void partRotate() override;
};

class PartS : public Parts
{
public:
	PartS(COLORREF);
	~PartS();
	void partRotate() override;
};

class PartL : public Parts
{
public:
	PartL(COLORREF);
	~PartL();
	void partRotate() override;
};

class PartJ : public Parts
{
public:
	PartJ(COLORREF);
	~PartJ();
	void partRotate() override;
};

class PartO : public Parts
{
public:
	PartO(COLORREF);
	~PartO();
	void partRotate() override;
};

class PartT : public Parts
{
public:
	PartT(COLORREF);
	~PartT();
	void partRotate() override;
};

class PartI : public Parts
{
public:
	PartI(COLORREF);
	~PartI();
	void partRotate() override;
};

#endif
