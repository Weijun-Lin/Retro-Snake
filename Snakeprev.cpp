#include"Snakeprev.h"
#include<graphics.h>
#include<stdio.h>
#define size 10
#define INDEX  20
#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'

snake* snakelist(int a,int *number)
{
	int mid = a * 2;
	snake *head = new snake;
	snake *tail = new snake;//tail dont have data just a table
	head->next = tail;
	tail->next = NULL;
	head->next = tail;
	a--;
	if (a > 0)
	{
		snake *mid = head;
		while (a)
		{
			snake *p = new snake;
			mid->next = p;
			p->next = tail;
			mid = p;
			a--;
		}
	}
	snake *p = head;
	for (int b = 0; b < mid; b+=2)
	{
		p->x = number[b]*INDEX;
		p->y = number[b + 1]*INDEX;
		p = p->next;
	}
	return head;
}

void addsnake(snake* head)
{
	while (head->next != NULL)
	{
		head = head->next;//prev
	}
	snake *p = new snake;//new
    head->next = p;
    p->next = NULL;
}

void drawsnake(snake *head,char click)
{
	//head draw
	setlinecolor(YELLOW);
	setfillcolor(GREEN);
	circle(head->x, head->y, 10);
	setfillcolor(RED);
	floodfill(head->x, head->y, YELLOW);
	setlinecolor(RED);
	setfillcolor(BLACK);
	switch (click)
	{
	case down:
		solidcircle(head->x + 5, head->y + 5, 4);//右下
		solidcircle(head->x - 5, head->y + 5, 4);//左下
		line(head->x, head->y + 15, head->x, head->y + 11);
		line(head->x - 2, head->y + 15 + 3, head->x, head->y + 15);
		line(head->x + 2, head->y + 15 + 3, head->x, head->y + 15);
		break;
	case right:
		solidcircle(head->x + 5, head->y - 5, 4);
		solidcircle(head->x + 5, head->y + 5, 4);
		line(head->x+15, head->y, head->x+11, head->y);
		line(head->x +15+3, head->y +2, head->x+15, head->y);
		line(head->x +15+3, head->y -2, head->x+15, head->y);
		break;
	case left:
		solidcircle(head->x - 5, head->y + 5, 4);
		solidcircle(head->x - 5, head->y - 5, 4);
		line(head->x-15, head->y, head->x-11, head->y);
		line(head->x-15-3, head->y+2, head->x-15, head->y);
		line(head->x-15-3, head->y-2, head->x-15, head->y);
		break;
	case up:
		solidcircle(head->x - 5, head->y - 5, 4);//左上
		solidcircle(head->x + 5, head->y - 5, 4);//右上
		line(head->x, head->y - 15, head->x, head->y - 11);
		line(head->x - 2, head->y - 15 - 3, head->x, head->y - 15);
		line(head->x + 2, head->y - 15 - 3, head->x, head->y - 15);
	}

	head = head->next;

	while (head != NULL)
	{
		setlinecolor(YELLOW);
		setlinestyle(PS_SOLID, 3);
		setfillcolor(RED);
		circle(head->x, head->y, 10);
		floodfill(head->x, head->y, YELLOW);
		setfillcolor(YELLOW);
		setfillcolor(GREEN);
		solidcircle(head->x, head->y, 3);
		head = head->next;
	}
}