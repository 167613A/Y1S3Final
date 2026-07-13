#include <iostream>
#include <easyx/easyx.h>
#include <easyx/graphics.h>
using namespace std;

int main(void)
{
	
	initgraph(640, 480);
	circle(320, 240, 100);
	closegraph();
	return 0;
}
