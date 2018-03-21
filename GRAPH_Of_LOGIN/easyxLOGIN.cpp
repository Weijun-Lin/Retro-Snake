#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	initgraph(640, 480);
	setbkcolor(RGB(208, 208, 208));
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
	settextcolor(BLACK);
	settextstyle(35, 0, _T("ËÎÌå"));
	outtextxy(16, 4, "L O G I N");
	settextstyle(18, 0, _T("ºÚÌå"));
	outtextxy(17, 50, "ID:");
	outtextxy(10, 78, "PWD:");
	solidrectangle(50, 50, 150, 70);
	solidrectangle(50, 78, 150, 98);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	//line(x, 51, x, 69);
	int x = 52, i = 0, y = 40;
	int c1 = 51, Flag = 0;
	char c = 0;
	char str[20] = "";
	char pwd[20] = "";
	while (true)
	{
		if (_kbhit())
		{
			c = _getch();
			if (c == '\b')
			{
				solidrectangle(y, c1 - 1, y + 10, c1 - 1 + 20);
				setlinecolor(WHITE);
				line(x, c1, x, c1 + 18);
				x -= 10;
				y -= 10;
				i--;
			}
			else
			{
				if (i < 20 && Flag == 0) str[i++] = c;
				if (i < 20 && Flag == 1) pwd[i++] = c;
				setlinecolor(WHITE);
				line(x, c1, x, c1 + 18);
				x += 10;
				y += 10;
				if (c == '\r')
				{
					if (Flag == 0)
					{
						str[i] = '\0';
						setlinecolor(WHITE);
						line(x, c1, x, c1 + 18);
						c = 0;
						c1 = 79;
						x = 52;
						i = 0;
						y = 40;
						Flag = 1;
					}
					else
					{
						pwd[i] = '\0';
						outtextxy(100, 200, "your ID is:");
						outtextxy(200, 200, str);
						outtextxy(90, 250, "your PWD is:");
						outtextxy(200, 250, pwd);
						break;
					}
					
				}
			}
		}
		setlinecolor(BLACK);
		line(x, c1, x, c1 + 18);
		if (c != '\b'&&Flag == 0) outtextxy(y, c1, c);
		if (c != '\b'&&Flag == 1 && c != 0) outtextxy(y, c1, '*');
	}
	_getch();
	closegraph();


	return 0;
}