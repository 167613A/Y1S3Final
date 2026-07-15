#include "blocks.h"
#include <iostream>
#include <algorithm>
using namespace std;

void Matrix::matrixAllocate(int r, int c)
{
	data = new int*[r];
	for(int i = 0; i < r; i++)
	{
		data[i] = new int[c];
		for(int j = 0; j < c; j++)
		{
			data[i][j] = 0;
		}
	}
}

void Matrix::matrixDeallocate()
{
	for(int i = 0; i < row; i++)
	{
		delete[] data[i];
	}
	delete[] data;
	data = nullptr;
}

Matrix::Matrix() {}
Matrix::Matrix(int r, int c) : row(r), col(c)
{
	matrixAllocate(r, c);
}
Matrix::~Matrix()
{
	matrixDeallocate();
}

int Block::getBlockPosX() {return posX;}
int Block::getBlockPosY() {return posY;}

Parts::Parts(COLORREF clr, int t = 0) : color(clr), rtTimes(t)
{
	bottomRow = 0;
}
Parts::~Parts() {}
int Parts::getBottomRow() {return bottomRow;}


void Parts::partRotate()
{
	switch(rtTimes % 2) 
	{
	case 0:
		shapeRotated = shapeOrigin.matrixRotate();
		break;
	case 1:
		shapeOrigin = shapeRotated.matrixRotate();
		break;
	default:
		break;
	}
}

void Parts::partDrop()
{
	
}


Game::Game(int s, int t, double d) : score(s), timer(t), difficulty(d), currentPart(Parts(WHITE, 0))
{
	movingPart = false;
}

Game::~Game() {}
int Game::getScore() {return score;}
int Game::getTime() {return timer;}
double Game::getDifficulty() {return difficulty;}

void Game::clearPlayArea()
{
	for(int i = 0; i < playAreaCol; i++)
	{
		for(int j = 0; j < playAreaRow; j++)
		{
			playArea[i][j] = 0;
		}
	}
}

void Game::gameInit()
{
	clearPlayArea();
	initgraph(resolutionRow, resolutionCol);
	setaspectratio(resolutionRatio, resolutionRatio);
}

void Game::gameDrawHomeUI()
{
	;
}

void Game::newPart()
{
	switch(rand() % 7) 
	{
	case 0:
		currentPart = PartZ(CYAN);
		break;
	case 1:
		currentPart = PartS(MAGENTA);
		break;
	case 2:
		currentPart = PartL(RED);
		break;
	case 3:
		currentPart = PartJ(ORANGE);
		break;
	case 4:
		currentPart = PartO(YELLOW);
		break;
	case 5:
		currentPart = PartT(GREEN);
		break;
	case 6:
		currentPart = PartI(BLUE);
		break;
	default:
		break;
	}
}

PartZ::PartZ(COLORREF clr) : Parts(clr, 0)
{
	shapeOrigin = Matrix(2, 3);
	shapeRotated = Matrix(3, 2);
}
PartZ::~PartZ()
{
	shapeOrigin.~Matrix();
	shapeRotated.~Matrix();
}

PartS::PartS(COLORREF clr) : Parts(clr, 0)
{
	shapeOrigin = Matrix(2, 3);
	shapeRotated = Matrix(3, 2);
}
PartS::~PartS()
{
	shapeOrigin.~Matrix();
	shapeRotated.~Matrix();
}

PartL::PartL(COLORREF clr) : Parts(clr, 0)
{
	shapeOrigin = Matrix(2, 3);
	shapeRotated = Matrix(3, 2);
}
PartL::~PartL()
{
	shapeOrigin.~Matrix();
	shapeRotated.~Matrix();
}

PartJ::PartJ(COLORREF clr) : Parts(clr, 0)
{
	shapeOrigin = Matrix(2, 3);
	shapeRotated = Matrix(3, 2);
}

PartO::PartO(COLORREF clr) : Parts(clr, 0)
{
	shapeOrigin = Matrix(2, 2);
	shapeRotated = Matrix(2, 2);
}
PartO::~PartO()
{
	shapeOrigin.~Matrix();
	shapeRotated.~Matrix();
}

PartT::PartT(COLORREF clr) : Parts(clr, 0)
{
	shapeOrigin = Matrix(2, 3);
	shapeRotated = Matrix(3, 2);
}
PartT::~PartT()
{
	shapeOrigin.~Matrix();
	shapeRotated.~Matrix();
}

PartI::PartI(COLORREF clr) : Parts(clr, 0)
{
	shapeOrigin = Matrix(4, 1);
	shapeRotated = Matrix(1, 4);
}
PartI::~PartI()
{
	shapeOrigin.~Matrix();
	shapeRotated.~Matrix();
}
