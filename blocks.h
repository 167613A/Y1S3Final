#ifndef BLOCKS_H
#define BLOCKS_H
#include <easyx/easyx.h>
#include <easyx/graphics.h>

const int sideLength = 45;					//方块边长

const int playAreaX = 10;					//游戏区域列数
const int playAreaY = 16;					//游戏区域行数
const int resolutionRow = 540;				//横向分辨率
const int resolutionCol = 960;				//纵向分辨率

const int partPosOrigin = 4;				//部件初始左边所在列

//部件矩阵初始行列数
const int partLenX[7] = {3, 3, 3, 3, 2, 3, 1};
const int partLenY[7] = {2, 2, 2, 2, 2, 2, 4};
const int partOriX[7][4] = {{0, 0, 1, 1}, {0, 0, 1, 1}, {0, 1, 1, 1}, {0, 1, 1, 1}, {0, 0, 1, 1}, {0, 1, 1, 1}, {0, 1, 2, 3}};
const int partOriY[7][4] = {{0, 1, 1, 2}, {1, 2, 0, 1}, {2, 0, 1, 2}, {0, 0, 1, 2}, {0, 1, 0, 1}, {1, 0, 1, 2}, {0, 0, 0, 0}};

const COLORREF ORANGE = 0x00AAFF;

class Matrix
{
private:
	COLORREF** data;						//矩阵数据
	int row;								//矩阵行数
	int col;								//矩阵列数
	void matrixAllocate(int, int);			//分配矩阵内存
	void matrixDeallocate();				//取回矩阵内存
public:
	Matrix();
	Matrix(int, int);
	~Matrix();
	COLORREF& at(int, int);					//引用对应位置元素地址
	int getRow();
	int getCol();
	void setRow(int);
	void setCol(int);
	Matrix matrixRotate() const;			//矩阵旋转
	void matrixPrint() const;				//矩阵打印
	Matrix& operator=(const Matrix&);		//重载运算符=：矩阵复制
};

//定义组成图形的方块类
class Block
{
private:
	int posX;								//左上角X轴位置
	int posY;								//左上角Y轴位置
	COLORREF color;
public:
	Block(int, int, COLORREF);
	~Block();
	int getBlockPosX();
	int getBlockPosY();
	void setBlockPosX(int);
	void setBlockPosY(int);
	void drawBlock(int, COLORREF);			//绘制方块 (边长, 颜色)
};

class Part
{
protected:
	COLORREF color;
	Matrix shapeOrigin;						//初始存储矩阵
	Matrix shapeRotated;					//旋转后存储矩阵
	Matrix shapeCurrent;					//当前状态存储矩阵
	int rtTimes;							//旋转次数
	int bottomRow;							//底层所在行
	int movesRight;							//右移次数
	int lenX;								//初始X轴长度
	int lenY;								//初始Y轴长度
public:
	Part();
	Part(COLORREF, int, int, int);
	~Part();
	void partSetColor();
	int getBottomRow();
	int getMovesRight();
	void setPartColor(COLORREF);
	void setPartLenX(int);
	void setPartLenY(int);
	void setOriginShape(int, COLORREF);		//设置部件初始形态
	void partRotate();						//部件旋转
	void partSoftDrop();					//部件下落一格
	void partHardDrop();					//部件降至落地
	void partMoveLeft();					//部件左移
	void partMoveRight();					//部件右移
	Part& operator=(const Part&);			//重载运算符=：部件复制
};

class Setting
{
private:
	double difficulty;
	COLORREF bgColor;						//背景颜色
	COLORREF partColor[7];					//部件颜色(顺序为ZSLJOTI)
public:
	Setting(double, COLORREF);
	Setting(const Setting&);
	~Setting();
	double getDifficulty();
	void setDifficulty(double);
	void setBgColor(COLORREF);
	void setPartColor(int, COLORREF);
	COLORREF getBgColor();
	COLORREF getPartColor(int);
};

class Play
{
private:
	Setting settings;						//设置类
	int score;								//分数
	int lines; 								//消除行数
	int timer;								//时间
	bool movingPart;						//是否有未落下的部件
	bool isHoldingPart;						//暂存区是否有部件
	COLORREF playArea[playAreaX][playAreaY];//游玩区域
	Part currentPart;						//正在控制的部件
	Part holdPart;							//暂存区的部件
public:
	Play(const Setting&, int, int, int, bool, bool);
	~Play();
	void setSettings(const Setting&); 		//获取设置
	void clearPlayArea();					//清除游玩区域
	void playDraw();						//绘制游玩区域
	void playDrawUI();						//绘制游玩界面UI
	int getScore();
	int getTime();
	void newPart();							//生成新部件
	void copyCurrentPart();					//复制控制部件至游玩区域
	void holdCurrentPart();					//将控制部件与暂存部件交换
	void checkFinishedLine();				//检查行是否完整
};

//定义游戏类
class Game
{
private:
	Setting settings;						//设置类
	Play gamePlay;							//游玩类
public:
	Game(double, COLORREF);
	~Game();
	void deleteLine();						//消除行
	void gameInit();						//游戏初始化
	void gameDrawHomeUI();					//绘制主界面UI
	void gameDrawSettingUI();				//绘制设置界面UI
	void gameStart();						//开始游玩
	void gameRestart();						//重新开始游戏
	void gameQuit();						//退出游玩界面
	void gameSetting();						//进入设置界面
	void gameClose();						//关闭程序
	void playDraw();						//绘制游玩区域
};
#endif
