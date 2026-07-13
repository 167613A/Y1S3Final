#ifndef BLOCKS_H
#define BLOCKS_H
#include <easyx/easyx.h>
#include <easyx/graphics.h>
#define SIDE_LENGTH = 20;

//定义游戏类
class Game
{
private:
	int score;
	int time;
	static bool movingPart;
	static double difficulty;
public:
	Game(int, int, double);
	~Game();
	void newPart();
	void deleteLine();
	int getScore();
	int getTime();
	double getDifficulty();
};

bool Game::movingPart = false;

//定义组成图形的方块类
class Block
{
protected:
	int posX;
	int posY;
	COLORREF color;
public:
	Block(int, int, COLORREF);
	~Block();
	int getBlockPosX();
	int getBlockPosY();
};

class Part
{
protected:
	Block baseBlock;
public:
	Part(int, int, COLORREF);
	~Part();
	virtual void partRotate();
	void partMoveLeft();
	void partMoveRight();
	void partMoveDown();
	void partMoveBottom();
};

class PartZ : public Part
{
public:
	void partRotate();
};

class PartS : public Part
{
public:
	void partRotate();
};

class PartL : public Part
{
public:
	void partRotate();
};

class PartJ : public Part
{
public:
	void partRotate();
};

class PartO : public Part
{
public:
	void partRotate();
};

class PartT : public Part
{
public:
	void partRotate();
};

class PartI : public Part
{
public:
	void partRotate();
};

#endif
