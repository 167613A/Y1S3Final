#include "blocks.h"
#include <iostream>
#include <algorithm>
using namespace std;

void Matrix::matrixAllocate(int r, int c)
{
	data = new COLORREF*[r];
	for(int i = 0; i < r; i++)
	{
		data[i] = new COLORREF[c];
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

COLORREF& Matrix::at(int r, int c) {return data[r][c];}
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

Block::Block(int x, int y, COLORREF clr) : posX(x), posY(y), color(clr) {}
Block::~Block() {}
int Block::getBlockPosX() {return posX;}
int Block::getBlockPosY() {return posY;}
void Block::setBlockPosX(int x) {posX = x;}
void Block::setBlockPosY(int y) {posY = y;}
void Block::drawBlock(int sl)
{
	setfillcolor(color);
	fillrectangle(posX, posY, posX + sl, posY + sl);
	loadimage(NULL, _T("blocks.jpg"), sl, sl, false);
}

Part::Part(COLORREF clr, int t, int x, int y) : color(clr), rtTimes(t), lenX(x), lenY(y)
{
	bottomRow = 0;
}
Part::~Part() {}
int Part::getBottomRow() {return bottomRow;}


void Part::partRotate()
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

void Part::partSoftDrop()
{
	;
}

void Part::partHardDrop()
{
	;
}

void Part::partMoveLeft()
{
	if(partPosOrigin + movesRight > 0)
	{
		movesRight--;
	}
}

void Part::partMoveRight()
{
	if(partPosOrigin + movesRight < 9)
	{
		movesRight++;
	}
}

Setting::Setting(double d, COLORREF bgclr) : difficulty(d), bgColor(bgclr)
{
	partColor[0] = CYAN;
	partColor[1] = MAGENTA;
	partColor[2] = RED;
	partColor[3] = ORANGE;
	partColor[4] = YELLOW;
	partColor[5] = GREEN;
	partColor[6] = BLUE;
}
Setting::~Setting() {}
double Setting::getDifficulty() {return difficulty;}
void Setting::setBgColor(COLORREF clr) {bgColor = clr;}
void Setting::setPartColor(int part, COLORREF clr)
{
	if(0 <= part && part <= 6)
	{
		partColor[part] = clr;
		return;
	}
		cout << "[Setting::setPartColor]Illegal part!" << endl;
}
COLORREF Setting::getPartColor(int part) {return partColor[part];}


Game::Game(int s, int t, double d, COLORREF bgColor) : score(s), timer(t), settings(Setting(d, bgColor)), currentPart(Part(WHITE, 0, 0, 0))
{
	movingPart = false;
}

Game::~Game() {}
int Game::getScore() {return score;}
int Game::getTime() {return timer;}

void Game::clearPlayArea()
{
	for(int i = 0; i < playAreaCol; i++)
	{
		for(int j = 0; j < playAreaRow; j++)
		{
			playArea[i][j] = getbkcolor();
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
		currentPart = PartZ(settings.getPartColor(0), 3, 2);
		movingPart = true;
		break;
	case 2:
		currentPart = PartS(MAGENTA, 3, 2);
		movingPart = true;
		break;
	case 3:
		currentPart = PartL(RED, 3, 2);
		movingPart = true;
		break;
	case 4:
		currentPart = PartJ(ORANGE, 3, 2);
		movingPart = true;
		break;
	case 5:
		currentPart = PartO(YELLOW, 2, 2);
		movingPart = true;
		break;
	case 6:
		currentPart = PartT(GREEN, 3, 2);
		movingPart = true;
		break;
	case 7:
		currentPart = PartI(BLUE, 1, 4);
		movingPart = true;
		break;
	default:
		movingPart = false;
		break;
	}
}

void Game::playDraw()
{
	COLORREF currentColor;
	Block tempBlock(0, 0, WHITE);
	for(int x = 0; x < playAreaRow; x++)
	{
		for(int y = 0; y < playAreaCol; y++)
		{
			currentColor = playArea[y][x];
			tempBlock.setBlockPosX(x);
			tempBlock.drawBlock(sideLength);
			tempBlock.~Block();
		}
	}
}

PartZ::PartZ(COLORREF clr, int x, int y) : Part(clr, 0, x, y)
{
	shapeOrigin = Matrix(y, x);
	shapeRotated = Matrix(x, y);
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

PartS::PartS(COLORREF clr, int x, int y) : Part(clr, 0, x, y)
{
	shapeOrigin = Matrix(y, x);
	shapeRotated = Matrix(x, y);
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

PartL::PartL(COLORREF clr, int x, int y) : Part(clr, 0, x, y)
{
	shapeOrigin = Matrix(y, x);
	shapeRotated = Matrix(x, y);
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

PartJ::PartJ(COLORREF clr, int x, int y) : Part(clr, 0, x, y)
{
	shapeOrigin = Matrix(y, x);
	shapeRotated = Matrix(x, y);
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

PartO::PartO(COLORREF clr, int x, int y) : Part(clr, 0, x, y)
{
	shapeOrigin = Matrix(y, x);
	shapeRotated = Matrix(x, y);
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

PartT::PartT(COLORREF clr, int x, int y) : Part(clr, 0, x, y)
{
	shapeOrigin = Matrix(y, x);
	shapeRotated = Matrix(x, y);
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

PartI::PartI(COLORREF clr, int x, int y) : Part(clr, 0, x, y)
{
	shapeOrigin = Matrix(y, x);
	shapeRotated = Matrix(x, y);
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
