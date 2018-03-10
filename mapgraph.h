//图形地图界面设置

#ifndef MAP_H
#define MAP_H
#include<graphics.h>
#define INDEX  20

COLORREF setcolor();
IMAGE setbox();
IMAGE setmap(COLORREF,IMAGE);
bool IfinBuding(int,int);

#endif // !MAP_H

