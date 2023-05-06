#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

#define POKE(addr,val) (*(unsigned char*) (addr) = (val))

unsigned int Random(unsigned int max);

unsigned long TimerStart();

unsigned long TimerGet(unsigned long t);

void DrawBox(char *title, unsigned char x, unsigned char y, unsigned char w, unsigned char h);

void DrawBar(unsigned char x, unsigned char y, unsigned char w, unsigned char fill);

#endif