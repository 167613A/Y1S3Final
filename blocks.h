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

const int partPosOrigin = 4;

const int partLenX[7] = {3, 3, 3, 3, 2, 3, 1};
const int partLenY[7] = {2, 2, 2, 2, 2, 2, 4};

const COLORREF ORANGE = 0x00A8FF;

class Matrix
{
private:
	COLORREF** data;
	int row;
	int col;
	void matrixAllocate(int, int);
	void matrixDeallocate();
public:
	Matrix();
	Matrix(int, int);
	~Matrix();
	COLORREF& at(int, int);
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
	void setBlockPosX(int);
	void setBlockPosY(int);
	void drawBlock(int);
};

class Part
{
protected:
	COLORREF color;
	Matrix shapeOrigin;
	Matrix shapeRotated;
	Matrix shapeCurrent;
	int rtTimes;
	int bottomRow;
	int movesRight;
	int lenX;
	int lenY;
public:
	Part(COLORREF, int, int, int);
	virtual ~Part();
	void partSetColor();
	int getBottomRow();
	virtual void partRotate();
	void partSoftDrop();
	void partHardDrop();
	void partMoveLeft();
	void partMoveRight();
};

class Setting
{
private:
	double difficulty;
	COLORREF bgColor;
	COLORREF partColor[7];
public:
	Setting(double, COLORREF);
	~Setting();
	double getDifficulty();
	void setBgColor(COLORREF);
	void setPartColor(int, COLORREF);
	COLORREF getPartColor(int);
};

//定义游戏类
class Game
{
private:
	int score;
	int timer;
	bool movingPart;
	Setting settings;
	COLORREF playArea[playAreaCol][playAreaRow];
	Part currentPart;
public:
	Game(int, int, double, COLORREF);
	~Game();
	void clearPlayArea();
	int getScore();
	int getTime();
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
	void checkFinishedLine();
};

class PartZ : public Part
{
public:
	PartZ(COLORREF, int, int);
	~PartZ();
	void partRotate() override;
};

class PartS : public Part
{
public:
	PartS(COLORREF, int, int);
	~PartS();
	void partRotate() override;
};

class PartL : public Part
{
public:
	PartL(COLORREF, int, int);
	~PartL();
	void partRotate() override;
};

class PartJ : public Part
{
public:
	PartJ(COLORREF, int, int);
	~PartJ();
	void partRotate() override;
};

class PartO : public Part
{
public:
	PartO(COLORREF, int, int);
	~PartO();
	void partRotate() override;
};

class PartT : public Part
{
public:
	PartT(COLORREF, int, int);
	~PartT();
	void partRotate() override;
};

class PartI : public Part
{
public:
	PartI(COLORREF, int, int);
	~PartI();
	void partRotate() override;
};

#endif
