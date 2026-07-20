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

/*----------------------------------------*/

Block::Block(int x, int y, COLORREF clr) : posX(x), posY(y), color(clr) {}
Block::~Block() {}
int Block::getBlockPosX() {return posX;}
int Block::getBlockPosY() {return posY;}
void Block::setBlockPosX(int x) {posX = x;}
void Block::setBlockPosY(int y) {posY = y;}
void Block::drawBlock(int sl, COLORREF clr)
{
	setfillcolor(clr);
	fillrectangle(posX, posY, posX + sl, posY + sl);
	loadimage(NULL, _T("blocks.jpg"), sl, sl, false);
}

/*----------------------------------------*/

Part::Part()
{
	color = WHITE;
	rtTimes = 0;
	bottomRow = 0;
	movesRight = 0;
	lenX = 0;
	lenY = 0;
}

Part::Part(COLORREF clr, int t, int x, int y) : color(clr), rtTimes(t), lenX(x), lenY(y)
{
	bottomRow = 0;
}

Part::~Part() {}
int Part::getBottomRow() {return bottomRow;}
int Part::getMovesRight() {return movesRight;}
void Part::setPartColor(COLORREF clr) {color = clr;}
void Part::setPartLenX(int x) {lenX = x;}
void Part::setPartLenY(int y) {lenY = y;}
void Part::setOriginShape(int part, COLORREF clr)
{
	color = clr;
	shapeOrigin = Matrix(partLenY[part], partLenX[part]);
	shapeRotated = Matrix(partLenX[part], partLenY[part]);
	for(int i = 0; i < 4; i++)
	{
		shapeOrigin.at(partOriX[part][i], partOriY[part][i]) = clr;
	}
	shapeCurrent = shapeOrigin;
}

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

Part& Part::operator=(const Part& pt)
{
	if(this == &pt)
	{
		return *this;
	}
	
	color = pt.color;
	shapeOrigin = pt.shapeOrigin;
	shapeRotated = pt.shapeRotated;
	shapeCurrent = shapeOrigin;
	rtTimes = 0;
	bottomRow = 0;
	movesRight = 0;
	lenX = pt.lenX;
	lenY = pt.lenY;
	return *this;
}

/*----------------------------------------*/

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

Setting::Setting(const Setting& sets)
{
	difficulty = sets.difficulty;
	bgColor = sets.bgColor;
	for(int i = 0; i < 7; i++)
	{
		partColor[i] = sets.partColor[i];
	}
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
COLORREF Setting::getBgColor() {return bgColor;}
COLORREF Setting::getPartColor(int part) {return partColor[part];}

/*----------------------------------------*/

Play::Play(const Setting& sets, int s, int l, int t, bool mp, bool hp) : settings(Setting(sets)), score(s), lines(l), timer(t), movingPart(mp), isHoldingPart(hp) {clearPlayArea();}
int Play::getScore() {return score;}
int Play::getTime() {return timer;}
void Play::clearPlayArea()
{
	for(int i = 0; i < playAreaX; i++)
	{
		for(int j = 0; j < playAreaY; j++)
		{
			playArea[i][j] = settings.getBgColor();
		}
	}
}

void Play::newPart()
{
	int part = rand() % 7;
	currentPart.setOriginShape(part, settings.getPartColor(part));
	movingPart = true;
}

void Play::playDraw()
{
	COLORREF currentColor;
	Block tempBlock(0, 0, WHITE);
	for(int x = 0; x < playAreaY; x++)
	{
		for(int y = 0; y < playAreaX; y++)
		{
			currentColor = playArea[y][x];
			tempBlock.setBlockPosX(x);
			tempBlock.drawBlock(sideLength, currentColor);
			tempBlock.~Block();
		}
	}
}

void Play::copyCurrentPart()
{
	int startCol = partPosOrigin + currentPart.getMovesRight();
	for(int i = startCol; i < startCol + (rtTimes % 2 ? ); i++)
	{
		
	};
}

void Play::holdCurrentPart()
{
	if(isHoldingPart)
	{
		Part tempPart;
		tempPart = holdPart;
		holdPart = currentPart;
		currentPart = tempPart;
	}
	else
	{
		isHoldingPart = true;
		holdPart = currentPart;
		movingPart = false;
	}
}

/*----------------------------------------*/

Game::Game(double d, COLORREF bgColor) : settings(Setting(d, bgColor)), gamePlay(Play(settings, 0, 0, 0, false, false)) {}
Game::~Game() {}
void Game::gameInit()
{
	initgraph(resolutionRow, resolutionCol);
}

void Game::gameDrawHomeUI()
{
	;
}
