#include "functions.h"
#include "DB/corps.h"
#include "DB/items.h"
#include "DB/names.h"
#include "DB/races.h"
#include "DB/ships.h"
#include "DB/skills.h"
#include <conio.h>
#include <stdlib.h>

/**********/
typedef struct Player
{
    //info
    char *name;
    char *surname;

    char *race;
    char *corp;
    char *ship;

    //stats
    unsigned char charisma;
    unsigned char intelligence;
    unsigned char memory;
    unsigned char perception;
    unsigned char willpower;

    //data
    unsigned long isks;
    unsigned long sp;

    //skills
    char *skills[10];

    //cargo
    char *cargo[10];
    unsigned char cargo_items;

} Player;

/**********/
static Player PLAYER;

/**********/
static void PlayerGenerateInfo()
{
    unsigned int index;

    index = Random(ARRAY_SIZE(NAMES));
    PLAYER.name = NAMES[index];

    index = Random(ARRAY_SIZE(SURNAMES));
    PLAYER.surname = SURNAMES[index];

    index = Random(ARRAY_SIZE(RACES));
    PLAYER.race = RACES[index];

    index = Random(ARRAY_SIZE(CORPS));
    PLAYER.corp = CORPS[index];

    index = Random(ARRAY_SIZE(SHIPS));
    PLAYER.ship = SHIPS[index];
}

/**********/
static void PlayerGenerateStats()
{
    PLAYER.charisma = 10 + Random(10);
    PLAYER.intelligence = 10 + Random(10);
    PLAYER.memory = 10 + Random(10);
    PLAYER.perception = 10 + Random(10);
    PLAYER.willpower = 10 + Random(10);
}


/**********/
static unsigned char PlayerHaveSkill(char *skill)
{
    unsigned char i = 0;

    for(;i<10;i++)
    {
        if(PLAYER.skills[i] == skill) { return 1; }
    }

    return 0;
}

/**********/
static void PlayerGenerateSkills()
{
    unsigned char i = 0;
    unsigned int index;

    for(;i<10;i++)
    {
        do
        {
            index = Random(ARRAY_SIZE(SKILLS));

        } while (PlayerHaveSkill(SKILLS[index]));
        
        PLAYER.skills[i] = SKILLS[index];
    }
}

/**********/
void PlayerGenerate()
{
    _randomize();

    PlayerGenerateInfo();
    PlayerGenerateStats();
    PLAYER.isks = 1000000LU;
    PLAYER.sp =  100000LU;   
    PlayerGenerateSkills();
    
    PLAYER.cargo_items = 0;
}

/**********/
static void PlayerDrawInfo()
{
    DrawBox("INFO", 0, 0, 40, 6);  

    gotoxy(1,1);
    cprintf("Name: %s %s", PLAYER.name, PLAYER.surname);

    gotoxy(1,2);
    cprintf("Race: %s", PLAYER.race);

    gotoxy(1,3);
    cprintf("Corp: %s", PLAYER.corp);

    gotoxy(1,4);
    cprintf("Ship: %s", PLAYER.ship);
}

/**********/
void PlayerDrawSP()
{
    DrawBox("SKILLPOINTS", 0, 6, 20, 3);  
    gotoxy(1, 7);
    cprintf("%lu", PLAYER.sp);
}

/**********/
void PlayerDrawDataHoriz()
{
    DrawBox("SKILLPOINTS", 0, 6, 20, 3);  
    gotoxy(1, 7);
    cprintf("%lu", PLAYER.sp);

    DrawBox("ISKS", 20, 6, 20, 3); 
    gotoxy(21, 7);
    cprintf("%lu", PLAYER.isks);
}

/**********/
static void PlayerDrawData()
{
    DrawBox("SKILLPOINTS", 20, 6, 20, 3);
    gotoxy(21, 7);
    cprintf("%lu", PLAYER.sp);

    DrawBox("ISKS", 20, 10, 20, 3);  
    gotoxy(21, 11);
    cprintf("%lu", PLAYER.isks);
}

/**********/
static void PlayerDrawStats()
{

    DrawBox("STATS", 0, 6, 20, 7);  

    gotoxy(1, 7);
    cprintf("Charisma    :   %d", PLAYER.charisma);

    gotoxy(1, 8);
    cprintf("Intelligence:   %d", PLAYER.intelligence);

    gotoxy(1, 9);
    cprintf("Memory      :   %d", PLAYER.memory);

    gotoxy(1, 10);
    cprintf("Perception  :   %d", PLAYER.perception);

    gotoxy(1, 11);
    cprintf("Willpower   :   %d", PLAYER.willpower);
}

/**********/
static void PlayerDrawSkills()
{
    unsigned char i = 0;

    DrawBox("SKILLS", 0, 13, 40, 12);  

    for(;i<10;i++)
    {
        gotoxy(1,14+i);
        cprintf("%s", PLAYER.skills[i]);
    }
}

/**********/
void PlayerDrawCargo()
{
    unsigned char i = 0;

    DrawBox("CARGO", 0, 9, 40, 12);

    for(;i<PLAYER.cargo_items;i++)
    {
        gotoxy(1,10+i);
        cprintf("%s",PLAYER.cargo[i]);
    }
}

/**********/
void PlayerDraw()
{
    PlayerDrawInfo();
    PlayerDrawStats();
    PlayerDrawData();
    PlayerDrawSkills();
}

/**********/
unsigned char PlayerCargoItems()
{
    return PLAYER.cargo_items;
}

/**********/
void PlayerPostMission()
{
    //add cargo
    unsigned char index = Random(ARRAY_SIZE(ITEMS));
    PLAYER.cargo[PLAYER.cargo_items] = ITEMS[index];
    PLAYER.cargo_items++;

    //add sp
    PLAYER.sp += Random(50) * 10UL;
}

/**********/
void PlayerDrawSell()
{
    DrawBox("INFO", 0, 0, 40, 6);  

    gotoxy(1,1);
    cprintf("Status : DOCKED");

    gotoxy(1,2);
    cprintf("System : Jita IV - Moon 4");

    gotoxy(1,3);
    cprintf("Station: Caldari Navy Assembly Plant");

    gotoxy(1,4);
    cprintf("Action : Selling items on the market");

    PlayerDrawDataHoriz();
    PlayerDrawCargo();

    //box bar
    DrawBox("PROGRESS", 0, 22, 40, 3);
}

/**********/
void PlayerPostSell()
{
    PLAYER.cargo_items--;
    PLAYER.isks += Random(1000) * 10UL;
}






