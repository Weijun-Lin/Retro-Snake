#include"mapgraph.h"

COLORREF setcolor()
{
	IMAGE box;
	loadimage(&box, "resource//box.jpg");
	SetWorkingImage(&box);
	COLORREF scene = getpixel(0,0);
	SetWorkingImage(NULL);
	return scene;
}

IMAGE setbox()
{
	IMAGE box;
	loadimage(&box, "resource//box.jpg", 2 * INDEX, 2 * INDEX);
	return box;
}

IMAGE setmap(COLORREF scene, IMAGE box)
{
	//InputBox(name, 16, "ÄãµÄÃû×ÖÊÇ£º","snake hello",NULL,200,100);
	IMAGE MAP;
	IMAGE bridge;
	loadimage(NULL, "resource//bkcolor.jpg");
	loadimage(&bridge, "resource//bridge.jpg",60,40);
	setlinecolor(scene);
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 10);
	setfillcolor(getpixel(520, 280));
	solidrectangle(270, 0, 330, 599);//lake
	rectangle(5, 5, 595, 595);
	for (int i = 10; i <= 10*INDEX; i += 2*INDEX)  //1
	{
		putimage(110, i, &box);
	}
	putimage(110, 230, &box); //2
	for (int i = 30; i <= 240; i += 2 * INDEX) //3
	{
		putimage(i, 290, &box);
	}
	for (int i = 350; i <= 580; i += 2 * INDEX)//4
	{
		putimage(110, i, &box);
	}
	for (int i = 550; i >= 20; i -= 2 * INDEX)//5
	{
		putimage(350, i, &box);
	}
	for (int i = 550; i >= 410; i -= 2 * INDEX)//6
	{
		putimage(i, 390, &box);
	}
	putimage(270, 150, &bridge);
	putimage(270, 390, &bridge);
	getimage(&MAP, 0, 0, 600, 600);
	cleardevice();
	return MAP;
}

bool IfinBuding(int x, int y)
{
	//juage if in lake
	if ((x >= 270 && x <= 330) && ((y <= 150 && y >= 0) || (y >= 190 && y <= 390) || (y >= 430 && y <= 599)))
	{
		return false;
	}
	//juage 1 box
	else if ((x >= 110 && x <= 150) && (y >= 10 && y <= 210))
	{
		return false;
	}
	//judge 2 box
	else if ((x >= 110 && x <= 150) && (y >= 230 && y <= 270))
	{
		return false;
	}
	//judge 4 box
	else if ((x >= 110 && x <= 150) && (y >= 350 && y <= 599))
	{
		return false;
	}
	//juage 3 box
	else if ((x >= 30 && x <= 270) && (y >= 290 && y <= 330))
	{
		return false;
	}
	//judge 5 box
	else if ((x >= 350 && x <= 390) && (y >= 30 && y <= 599))
	{
		return false;
	}
	//judge 6 box
	else if ((x >= 430 && x <= 599) && (y >= 390 && y <= 430))
	{
		return false;
	}
	else return true;
}