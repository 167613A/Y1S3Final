#include "blocks.h"
#include <iostream>
#include <algorithm>
using namespace std;

//分配内存到矩阵
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

//释放矩阵占用内存
void Matrix::matrixDeallocate()
{
	for(int i = 0; i < row; i++)
	{
		delete[] data[i];
	}
	delete[] data;
	data = nullptr;
}

//构造函数与析构函数
Matrix::Matrix() {}
Matrix::Matrix(int r, int c) : row(r), col(c)
{
	matrixAllocate(r, c);
}
Matrix::~Matrix()
{
	matrixDeallocate();
}

//外部通过行列位置获取数据地址，可做左值和右值
COLORREF& Matrix::at(int r, int c) {return data[r][c];}

//外部获取与设置内部变量
int Matrix::getRow() const {return row;}
int Matrix::getCol() const {return col;}
void Matrix::setRow(int r) {row = r;}
void Matrix::setCol(int c) {col = c;}

//旋转矩阵
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

//打印矩阵：用于调试
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

//重载运算符=：用于复制矩阵
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

//构造函数与析构函数
Block::Block(int x, int y, COLORREF clr) : posX(x), posY(y), color(clr) {}
Block::~Block() {}

//外部获取内部变量
int Block::getBlockPosX() const {return posX;}
int Block::getBlockPosY() const {return posY;}
void Block::setBlockPosX(int x) {posX = x;}
void Block::setBlockPosY(int y) {posY = y;}

//绘制方块，需提供方块边长与颜色
void Block::drawBlock(int sl, COLORREF clr) const
{
	setfillcolor(clr);
	fillrectangle(posX, posY, posX + sl, posY + sl);
	loadimage(NULL, _T("blocks.jpg"), sl, sl, false);
}

/*----------------------------------------*/

//构造函数与析构函数
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

//外部获取内部变量
int Part::getBottomRow() const {return bottomRow;}
int Part::getMovesRight() const {return movesRight;}
//获取当前部件长宽数据
int Part::getLenX() const {return rtTimes % 2 ? lenX : lenY;}
int Part::getLenY() const {return rtTimes % 2 ? lenY : lenX;}
COLORREF Part::getData(int a, int b) {return shapeCurrent.at(a, b);}

//外部设置内部变量
void Part::setPartColor(COLORREF clr) {color = clr;}
void Part::setPartLenX(int x) {lenX = x;}
void Part::setPartLenY(int y) {lenY = y;}

//部件预设初始化
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

//部件旋转(Up, W, LCTRL)
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

//部件操纵模块，返回是否成功的布尔值
//部件下降(Down, S)
bool Part::partSoftDrop()
{
	return false;
}

//部件硬着陆(RCTRL, Space, E)
bool Part::partHardDrop()
{
	return false;
}

//部件左移(Left, A)
bool Part::partMoveLeft()
{
	if(partPosOrigin + movesRight > 0)
	{
		movesRight--;
		return true;
	}
	return false;
}

//部件右移(Right, D)
bool Part::partMoveRight()
{
	if(partPosOrigin + movesRight < 9)
	{
		movesRight++;
		return true;
	}
	return false;
}

//重载运算符=：用于复制部件
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

//构造函数与析构函数，外部获取当前难度
Setting::Setting(double d, COLORREF bkclr) : difficulty(d), bkColor(bkclr)
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
	bkColor = sets.bkColor;
	for(int i = 0; i < 7; i++)
	{
		partColor[i] = sets.partColor[i];
	}
}

Setting::~Setting() {}
double Setting::getDifficulty() const {return difficulty;}

//设置与外部获取背景颜色与部件颜色
void Setting::setBkColor(COLORREF clr) {bkColor = clr;}
//设置部件颜色，part值0-6对应顺序为ZSLJOTI
void Setting::setPartColor(int part, COLORREF clr)
{
	if(0 <= part && part <= 6)
	{
		partColor[part] = clr;
		return;
	}
		cout << "[Setting::setPartColor]Illegal part!" << endl;
}
COLORREF Setting::getBkColor() const {return bkColor;}
COLORREF Setting::getPartColor(int part) const {return partColor[part];}

/*----------------------------------------*/

//构造函数与析构函数，外部获取变量值函数
Play::Play(const Setting& sets, int s, int l, int t, bool mp, bool hp) : settings(Setting(sets)), score(s), lines(l), timer(t), movingPart(mp), isHoldingPart(hp) {clearPlayArea();}
Play::~Play() {}
int Play::getScore() const {return score;}
int Play::getTime() const {return timer;}

//清除游玩区域
void Play::clearPlayArea()
{
	for(int i = 0; i < playAreaX; i++)
	{
		for(int j = 0; j < playAreaY; j++)
		{
			playArea[i][j] = settings.getBkColor();
		}
	}
}

//生成新部件
void Play::newPart()
{
	int part = rand() % 7;
	currentPart.setOriginShape(part, settings.getPartColor(part));
	movingPart = true;
}

//绘制游玩区域
void Play::playDraw() const
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

//复制当前控件至游玩区域，若能复制则返回true，已触底返回false
bool Play::copyCurrentPart()
{
	int startCol = partPosOrigin + currentPart.getMovesRight();
	int startRow = currentPart.getBottomRow() - currentPart.getLenY() + 1;
	for(int i = startCol; i < startCol + currentPart.getLenX(); i++)
	{
		for(int j = startRow; j < startRow + currentPart.getLenY(); j++)
		{
			if(playArea[i][j] != settings.getBkColor())
			{
				return false;
			}
		}
	}
	for(int i = startCol; i < startCol + currentPart.getLenX(); i++)
	{
		for(int j = startRow; j < startRow + currentPart.getLenY(); j++)
		{
			playArea[i][j] = currentPart.getData(i - startCol, j - startRow);
		}
	}
	return true;
}

//左移当前部件
bool Play::leftCurrentPart()
{
	return currentPart.partMoveLeft();
}

//右移当前部件
bool Play::rightCurrentPart()
{
	return currentPart.partMoveRight();
}

//硬着陆当前部件
bool Play::dropCurrentPart()
{
	return false;
}

//暂存当前部件
void Play::holdCurrentPart()
{
	if(isHoldingPart)
	{
		Part tempPart(WHITE, 4, 4, 0);
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

Game::Game(double d, COLORREF bkColor) : settings(Setting(d, bkColor)), gamePlay(Play(settings, 0, 0, 0, false, false)) {}
Game::~Game() {}

//游戏初始化
void Game::gameInit() {initgraph(resolutionRow, resolutionCol);}

//绘制主界面
void Game::gameDrawHomeUI()
{
	;
}
