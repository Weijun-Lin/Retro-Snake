//ÉßÉí²Ù×÷

#ifndef Snakeprev_H
#define Snakeprev_H

typedef struct Snake
{
	int x, y;
	struct Snake* next;
}snake;

snake * snakelist(int,int*);//creat a list belong to number
void addsnake(snake *);//creat a point in the tail
void drawsnake(snake *,char);
void clearsnake(snake *);

#endif // !Addition_H

