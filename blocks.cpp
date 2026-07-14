#include "blocks.h"
using namespace std;

int** matrixRotate(const int** mat, int r, int c)
{
	int** res = new int*[c];
	for(int i = 0; i < c; i++)
	{
		res[i] = new int[r];
	}
	
	for(int i = 0; i < r; i++)
	{
		for(int j = 0; j < c; j++)
		{
			res[j][r - 1 - i] = mat[i][j];
		}
	}
	
	return res;
}

void freeMatrixMemory(int** mat, int r)
{
	for(int i = 0; i < r; i++)
	{
		delete[] mat[i];
	}
	
	delete[] mat;
}

Game::Game(int s, int t, double d) : score(s), time(t), difficulty(d)
{
	movingPart = false;
}

Game::~Game() {}
int Game::getScore() {return score;}
int Game::getTime() {return time;}
double Game::getDifficulty() {return difficulty;}

void Game::clearPlayArea()
{
	for(int i = 0; i < playAreaRow; i++)
	{
		for(int j = 0; j < playAreaCol; j++)
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

void gameDrawHomeUI()
{
	
}


int Block::getBlockPosX() {return posX;}
int Block::getBlockPosY() {return posY;}

void Parts::partRotate() {}
