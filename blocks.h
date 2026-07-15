#ifndef BLOCKS_H
#define BLOCKS_H
#include <easyx/easyx.h>
#include <easyx/graphics.h>

const int sideLength = 3;

const int playAreaCol = 10;
const int playAreaRow = 16;
const int resolutionRow = 540;
const int resolutionCol = 960;
const int resolutionRatio = resolutionCol / 64;

const int partLinePosOrigin = 5;

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
	Matrix();
	Matrix(int, int);
	~Matrix();
	int& at(int, int);
	int getRow();
	int getCol();
	void setRow(int);
	void setCol(int);
	Matrix matrixRotate() const;
	void matrixPrint() const;
	Matrix& operator=(const Matrix& mat);
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
	Matrix shapeOrigin;
	Matrix shapeRotated;
	Matrix shapeCurrent;
	int rtTimes;
	int bottomRow;
	int movesRight;
public:
	Parts(COLORREF, int);
	virtual ~Parts();
	void partSetColor();
	int getBottomRow();
	virtual void partRotate();
	void partSoftDrop();
	void partHardDrop();
	void partMoveLeft();
	void partMoveRight();
};

//定义游戏类
class Game
{
private:
	int score;
	int timer;
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
	void copyCurrentPart();
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
