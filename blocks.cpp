#include "blocks.h"
#include <iostream>
#include <algorithm>
using namespace std;

void Matrix::matrixAllocate(int r, int c)
{
	data = new int*[r];
	row = r;
	col = c;
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

int Block::getBlockPosX() {return posX;}
int Block::getBlockPosY() {return posY;}

Parts::Parts(COLORREF clr, int t) : color(clr), rtTimes(t)
{
	bottomRow = 0;
}
Parts::~Parts() {}
int Parts::getBottomRow() {return bottomRow;}

void Parts::matrixPartRotate(int** cur, int** ori, int** rot, int row, int col)
{
	switch(rtTimes % 2) 
	{
	case 0:
		rot = matrixRotate(ori, row, col);
		cur = rot;
		break;
	case 1:
		ori = matrixRotate(rot, col, row);
		cur = ori;
		break;
	default:
		break;
	}
}
void Parts::partRotate() {}

void Parts::partDrop()
{
	
}


Game::Game(int s, int t, double d) : score(s), time(t), difficulty(d), currentPart(Parts(WHITE, 0))
{
	movingPart = false;
}

Game::~Game() {}
int Game::getScore() {return score;}
int Game::getTime() {return time;}
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
	matrixNewMemory(ori, 2, 3);
	matrixNewMemory(rot, 3, 2);
}
PartZ::~PartZ()
{
	freeMatrixMemory(ori, 2);
	freeMatrixMemory(rot, 3);
}

PartS::PartS(COLORREF clr) : Parts(clr, 0)
{
	matrixNewMemory(ori, 2, 3);
	matrixNewMemory(rot, 3, 2);
}
PartS::~PartS()
{
	freeMatrixMemory(ori, 2);
	freeMatrixMemory(rot, 3);
}

PartL::PartL(COLORREF clr) : Parts(clr, 0)
{
	matrixNewMemory(ori, 2, 3);
	matrixNewMemory(rot, 3, 2);
}
PartL::~PartL()
{
	freeMatrixMemory(ori, 2);
	freeMatrixMemory(rot, 3);
}

PartJ::PartJ(COLORREF clr) : Parts(clr, 0)
{
	matrixNewMemory(ori, 2, 3);
	matrixNewMemory(rot, 3, 2);
}
PartJ::~PartJ()
{
	freeMatrixMemory(ori, 2);
	freeMatrixMemory(rot, 3);
}

PartO::PartO(COLORREF clr) : Parts(clr, 0)
{
	matrixNewMemory(ori, 2, 2);
}
PartO::~PartO()
{
	freeMatrixMemory(ori, 2);
}

PartT::PartT(COLORREF clr) : Parts(clr, 0)
{
	matrixNewMemory(ori, 2, 3);
	matrixNewMemory(rot, 3, 2);
}
PartT::~PartT()
{
	freeMatrixMemory(ori, 2);
	freeMatrixMemory(rot, 3);
}

PartI::PartI(COLORREF clr) : Parts(clr, 0)
{
	matrixNewMemory(ori, 4, 1);
	matrixNewMemory(rot, 1, 4);
}
PartI::~PartI()
{
	freeMatrixMemory(ori, 4);
	freeMatrixMemory(rot, 1);
}

void PartZ::partRotate()
{
	matrixPartRotate(cur, ori, rot, 2, 3);
}
void PartS::partRotate()
{
	matrixPartRotate(cur, ori, rot, 2, 3);
}
void PartL::partRotate()
{
	matrixPartRotate(cur, ori, rot, 2, 3);
}
void PartJ::partRotate()
{
	matrixPartRotate(cur, ori, rot, 2, 3);
}
void PartO::partRotate() {}
void PartT::partRotate()
{
	matrixPartRotate(cur, ori, rot, 2, 3);
}
void PartI::partRotate()
{
	matrixPartRotate(cur, ori, rot, 4, 1);
}
