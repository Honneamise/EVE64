#include "functions.h"
#include <stdlib.h>
#include <conio.h>
#include <time.h>

/**********/
unsigned int Random(unsigned int max)
{
    _randomize();

    return rand()%max;
}

/**********/
unsigned long TimerStart()
{
	return clock();
}

/**********/
unsigned long TimerGet(unsigned long t)
{
    clock_t ticks = 0;
    unsigned long sec = 0;
    unsigned long msec = 0;

    if(t)
    {
        ticks = clock() - t;
            
        sec = ticks / CLOCKS_PER_SEC;
        msec = (sec*1000) + ((ticks % CLOCKS_PER_SEC) * 1000) / CLOCKS_PER_SEC; 
    }

    return msec;
}

/**********/
void DrawBox(char *title, unsigned char x, unsigned char y, unsigned char w, unsigned char h)
{
    //lines
    gotoxy(x, y);
    chline(w);

    gotoxy(x, y+h-1);
    chline(w);

    gotoxy(x, y);
    cvline(h);

    gotoxy(x+w-1, y);
    cvline(h);

    //edges
    gotoxy(x, y);
    cputc(0xF0);//top left

    gotoxy(x+w-1, y);
    cputc(0xEE);//top right

    gotoxy(x, y+h-1);
    cputc(0xED);//bottom left

    gotoxy(x+w-1, y+h-1);
    cputc(0xFD);//bottom right

    if(title)
    {
        revers(1);
        
        gotoxy(x+1, y);

        cprintf("%s", title);

        revers(0);
    }
}

/**********/
void DrawBar(unsigned char x, unsigned char y, unsigned char w, unsigned char fill)
{
    int i = 0;

    gotoxy(x, y);
    for(;i<fill;i++)
    {
        cputc(0xA9);
    }

    for(;i<w;i++)
    {
        cputc(0x20);
    }
}