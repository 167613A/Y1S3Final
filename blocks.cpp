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

int& Matrix::at(int r, int c) {return data[r][c];}
int Matrix::getRow() {return row;}
int Matrix::getCol() {return col;}
void Matrix::setRow(int r) {row = r;}
void Matrix::setCol(int c) {col = c;}

Matrix Matrix::matrixRotate() const
{
	Matrix res(col, row);
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			res.data[j][row - 1 - i] = data[i][j];
		}
	}
	return res;
}

void Matrix::matrixPrint() const
{
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			cout << data[i][j] << ' ';
		}
		cout << endl;
	}
}

Matrix& Matrix::operator=(const Matrix& mat)
{
	if(this == &mat)
	{
		return *this;
	}
	
	matrixDeallocate();
	row = mat.row;
	col = mat.col;
	matrixAllocate(mat.row, mat.col);
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			data[i][j] = mat.data[i][j];
		}
	}
	return *this;
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
		shapeCurrent = shapeRotated;
		break;
	case 1:
		shapeOrigin = shapeRotated.matrixRotate();
		shapeCurrent = shapeOrigin;
		break;
	default:
		break;
	}
}

void Parts::partSoftDrop()
{
	;
}

void Parts::partHardDrop()
{
	;
}

void Parts::partMoveLeft()
{
	if(partLinePosOrigin)
	{
		;
	}
}

void Parts::partMoveRight() {movesRight++;}

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
	switch(rand() % 8) 
	{
	case 1:
		currentPart = PartZ(CYAN);
		movingPart = true;
		break;
	case 2:
		currentPart = PartS(MAGENTA);
		movingPart = true;
		break;
	case 3:
		currentPart = PartL(RED);
		movingPart = true;
		break;
	case 4:
		currentPart = PartJ(ORANGE);
		movingPart = true;
		break;
	case 5:
		currentPart = PartO(YELLOW);
		movingPart = true;
		break;
	case 6:
		currentPart = PartT(GREEN);
		movingPart = true;
		break;
	case 7:
		currentPart = PartI(BLUE);
		movingPart = true;
		break;
	default:
		movingPart = false;
		break;
	}
}



PartZ::PartZ(COLORREF clr) : Parts(clr, 0)
{
	shapeOrigin = Matrix(2, 3);
	shapeRotated = Matrix(3, 2);
	shapeOrigin.at(0, 0) = 1;
	shapeOrigin.at(0, 1) = 1;
	shapeOrigin.at(1, 1) = 1;
	shapeOrigin.at(1, 2) = 1;
	shapeCurrent = shapeOrigin;
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
	shapeOrigin.at(0, 1) = 2;
	shapeOrigin.at(0, 2) = 2;
	shapeOrigin.at(1, 0) = 2;
	shapeOrigin.at(1, 1) = 2;
	shapeCurrent = shapeOrigin;
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
	shapeOrigin.at(0, 2) = 3;
	shapeOrigin.at(1, 0) = 3;
	shapeOrigin.at(1, 1) = 3;
	shapeOrigin.at(1, 2) = 3;
	shapeCurrent = shapeOrigin;
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
	shapeOrigin.at(0, 0) = 4;
	shapeOrigin.at(1, 0) = 4;
	shapeOrigin.at(1, 1) = 4;
	shapeOrigin.at(1, 2) = 4;
	shapeCurrent = shapeOrigin;
}
PartJ::~PartJ()
{
	shapeOrigin.~Matrix();
	shapeRotated.~Matrix();
}

PartO::PartO(COLORREF clr) : Parts(clr, 0)
{
	shapeOrigin = Matrix(2, 2);
	shapeRotated = Matrix(2, 2);
	shapeOrigin.at(0, 0) = 5;
	shapeOrigin.at(0, 1) = 5;
	shapeOrigin.at(1, 0) = 5;
	shapeOrigin.at(1, 1) = 5;
	shapeCurrent = shapeOrigin;
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
	shapeOrigin.at(0, 1) = 6;
	shapeOrigin.at(1, 0) = 6;
	shapeOrigin.at(1, 1) = 6;
	shapeOrigin.at(1, 2) = 6;
	shapeCurrent = shapeOrigin;
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
	shapeOrigin.at(0, 0) = 7;
	shapeOrigin.at(1, 0) = 7;
	shapeOrigin.at(2, 0) = 7;
	shapeOrigin.at(3, 0) = 7;
	shapeCurrent = shapeOrigin;
}
PartI::~PartI()
{
	shapeOrigin.~Matrix();
	shapeRotated.~Matrix();
}
