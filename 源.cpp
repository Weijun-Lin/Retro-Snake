//easyx版贪吃蛇 参数：1~29半径10坐标为20倍数

#include<graphics.h>
#include<conio.h>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"Snakeprev.h"
#include"mapgraph.h"

#pragma comment(lib,"Winmm.lib")

#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'
#define stop 'p'
#define speed 150
#define INDEX  20

using namespace std;
/****************************************************/
IMAGE box;
IMAGE MAP;
IMAGE MAPLEFT;
IMAGE foodstyle;
IMAGE foodstylex;
IMAGE apple;       //1 ***** 5 score   
IMAGE applex;      
IMAGE banana;       //2 ***** 10 score
IMAGE bananax;
IMAGE watermelon;  //3  ***** 20 score
IMAGE watermelonx;
IMAGE welcome;
IMAGE bkcolor;
COLORREF scene;
MOUSEMSG mouse;
char click = 0;
char name[20];
char NAME[30] = "你好 ， ";
int number[6] = { 8,8,8,9,8,10 };
snake * const head = snakelist(3,number);
int score = 0;
char SCORE[30];
/****************************************************/
class Food
{
private:
	int x, y;
	IMAGE yuan, yuanx;
	int style;
public:
	Food();
	void drawfood(IMAGE, IMAGE);
	int getx() { return x; }
	int gety() { return y; }
	void setxy();
	void setstyle(int);
	int getstyle() { return style; }
};
Food::Food()
{
	setxy();
}
void Food::setxy()
{
	srand((unsigned)time(NULL));
	int a, b;
	snake *judge = head;
	while (1)
	{
		int panduan = 1,flag = 0;
		a = (rand() % 29 + 1)*INDEX;
		b = (rand() % 29 + 1)*INDEX;
		if (IfinBuding(a, b) == true)
		{
			flag = 1;
			break;
		}
		while (true)
		{
			if (x == judge->x&&y == judge->y)
			{
				panduan = 0;
				break;
			}
			if (judge->next->next == NULL) break;
			judge = judge->next;
		}
		if (panduan == 1 && flag == 1) break;
	}
	x = a;
	y = b;
}
void Food::setstyle(int a)
{
	style = a;
}
void Food::drawfood(IMAGE yuan, IMAGE yuanx)
{
	SetWorkingImage(&yuan);
	putimage(0, 0, &yuanx, SRCINVERT);
	SetWorkingImage(NULL);
	putimage(x-15, y-15, &yuanx, SRCAND);
	putimage(x-15, y-15, &yuan, SRCPAINT);
}
Food food;
/****************************************************/
void welcomegraph();
void Finish();
int clickcontrol();
void Movingsnake(char);
void Changesnakebody(int ,int );
void Eating();
int Deadjudge();
/****************************************************/


/****************************************************/
int main()
{
	mciSendString("open resource//bgm.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("open resource//dead.wav type waveaudio alias dead", NULL, 0, NULL);
	mciSendString("open resource//eat.mp3 alias eat", NULL, 0, NULL);
	mciSendString("open resource//click.wav type waveaudio alias click",NULL,0,NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
	welcomegraph();
	if (clickcontrol() == 0)
	{
		closegraph();
		return 0;
	}
}

void welcomegraph()
{
	initgraph(850, 600);
	scene = setcolor();
	box = setbox();
	MAP = setmap(scene, box);
	float H = 190, S = 1, L = 0.7;//H 色相：S 饱和度：L 亮度
	for (int i = 0; i < 600; i++)
	{
		L += 0.0005;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, i, 849, i);
	}
	loadimage(&welcome, "resource//snake.jpg",320,600);
	loadimage(&apple, "resource//apple.jpg",30,30);
	loadimage(&applex, "resource//applex.jpg",30,30);
	loadimage(&banana, "resource//banana.jpg", 30, 30);
	loadimage(&bananax, "resource//bananax.jpg", 30, 26);
	loadimage(&watermelon, "resource//watermelon.jpg", 30, 30);
	loadimage(&watermelonx, "resource//watermelonx.jpg", 30, 30);
	foodstyle = apple;
	foodstylex = applex;
	food.setstyle(0);
	putimage(265,0,&welcome);
	while (TRUE)
	{
		mouse = GetMouseMsg();
		if (mouse.x >= 370 && mouse.x <= 480 && mouse.y >= 380 && mouse.y <= 420 && mouse.mkLButton)
		{
			mciSendString("play click", NULL, 0, NULL);
			for (int i = 0; i <= 300; i++)
			{
				setlinecolor(GREEN);
				line(0, i, 849, i);
				line(0, (600 - i), 849, (600 - i));
				Sleep(4);
			}
			InputBox(name, 10, "你的名字是");
			strcat(NAME, name);
			loadimage(NULL, "resource//bkcolor.jpg");
			getimage(&MAPLEFT, 600, 0, 250, 600);
			settextcolor(RGB(0, 0, 0));
			setbkmode(TRANSPARENT);
			settextstyle(25, 0, _T("华文行楷"));
			outtextxy(650, 100, NAME);
			outtextxy(650, 150, "你的得分是：");
			settextstyle(130, 0, _T("黑体"));
			itoa(score, SCORE, 10);
			outtextxy(690, 270, SCORE);
			return;
		}
	}
}

int Deadjudge()
{
	if (head->x == 0 * INDEX || head->x == 30 * INDEX || head->y == 0 * INDEX || head->y == 30 * INDEX)
	{
		Finish();
		return 0;
	}
	if (IfinBuding(head->x, head->y) == false)
	{
		Finish();
		return 0;
	}
	int a = head->x, b = head->y;
	snake *p = head->next;
	while (p->next != NULL)
	{
		if (p->x == a&&p->y == b)
		{
			Finish();
			return 0;
		}
		p = p->next;
	}
	return 1;
}

void Finish()
{
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("play dead", NULL, 0, NULL);;
	loadimage(NULL, "resource//over.jpg",850,600);
	setfillcolor(RGB(128, 255, 128));
	solidrectangle(0, 0, 849, 180);
	solidrectangle(0, 400, 849, 600);
	Sleep(1000);
	_getch();
}

int clickcontrol()
{
	while (TRUE)
	{
		if (Deadjudge() == 0) return 0;
		if (_kbhit())
		{
			click = _getch();
		}
		Movingsnake(click);
		Eating();
	}
	return 1;
}

void Movingsnake(char c)
{
	BeginBatchDraw();
	int x = head->x, y = head->y;
	switch (c)
	{
	case up:
		head->y -= INDEX;
		Changesnakebody(x,y);
		break;
	case down:
		head->y += INDEX;
		Changesnakebody(x,y);
		break;
	case left:
		head->x -= INDEX;
		Changesnakebody(x,y);
		break;
	case right:
		head->x += INDEX;
		Changesnakebody(x,y);
		break;
	}
	putimage(0, 0, &MAP);
	settextcolor(RGB(0, 0, 0));
	food.drawfood(foodstyle,foodstylex);
	drawsnake(head,c);
	FlushBatchDraw();
	Sleep(speed);
	EndBatchDraw();
}

void Changesnakebody(int x,int y)
{
	snake *p = head->next;
	int mid1, mid2, _mid1, _mid2;
	mid1 = p->x;
	mid2 = p->y;
	while (1)
	{
		if (p->next->next == NULL) break;
		_mid1 = p->next->x;
		_mid2 = p->next->y;
		p->next->x = mid1;
		p->next->y = mid2;
		mid1 = _mid1;
		mid2 = _mid2;
		p = p->next;
	}
	p = head->next;
	p->x = x;
	p->y = y;
}

void Eating()
{	
	if (head->x == food.getx() && head->y == food.gety())
	{
		if (food.getstyle() == 0) score += 5;
		else if (food.getstyle() == 1) score += 10;
		else if (food.getstyle() == 2) score += 20;
		srand((unsigned)time(NULL));
		int middle = rand() % 7;
		if (middle == 0)
		{
			foodstyle = watermelon;
			foodstylex = watermelonx;
			food.setstyle(2);
		}
		else if (middle == 1||middle==2)
		{
			foodstyle = banana;
			foodstylex = bananax;
			food.setstyle(1);
		}
		else
		{
			foodstyle = apple;
			foodstylex = applex;
			food.setstyle(0);
		}
		mciSendString("play eat from 0", NULL, 0, NULL);
		snake *p = head;
		snake *q = new snake;
		while (p->next->next != NULL)
		{
			p = p->next;
		}
		snake *tail = p->next;
		p->next = q;
		q->next = tail;
		putimage(600, 0, &MAPLEFT);
		setbkmode(TRANSPARENT);
		settextstyle(25, 0, _T("华文行楷"));
		outtextxy(650, 100, NAME);
		outtextxy(650, 150, "你的得分是：");
		settextstyle(50, 0, _T("黑体"));
		itoa(score, SCORE, 10);
		outtextxy(670, 270, SCORE);
		food.setxy();
		food.drawfood(foodstyle, foodstylex);
	}
}
