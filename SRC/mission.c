#include "functions.h"
#include "player.h"
#include "DB/regions.h"
#include "DB/systems.h"
#include "DB/missions.h"
#include "DB/enemies.h"
#include <conio.h>

/**********/
typedef struct Mission
{
    char *region; 
    char *system;
    char *desc;
    char *target;

    unsigned char progress;

    unsigned long timer;

} Mission;

/**********/
static Mission MISSION;

/**********/
void MissionGenerate()
{
    unsigned int index;

    index = Random(ARRAY_SIZE(SYSTEMS));
    
    MISSION.region = REGIONS[SYSTEMS[index].regionid];
    MISSION.system = SYSTEMS[index].name;

    index = Random(ARRAY_SIZE(MISSIONS));
    MISSION.desc = MISSIONS[index];

    index = Random(ARRAY_SIZE(ENEMIES));
    MISSION.target = ENEMIES[index];

    MISSION.progress = 0;

    MISSION.timer = 0;
}

/**********/
void MissionDraw()
{
    DrawBox("Mission", 0, 0, 40, 6);  

    gotoxy(1,1);
    cprintf("Region: %s", MISSION.region);

    gotoxy(1,2);
    cprintf("System: %s", MISSION.system);

    gotoxy(1,3);
    cprintf("Desc  : %s", MISSION.desc);

    gotoxy(1,4);
    cprintf("Target: %s", MISSION.target);

    //progress bar
    DrawBox("PROGRESS", 0, 22, 40, 3);

    //sp
    PlayerDrawDataHoriz();

    //cargo
    PlayerDrawCargo();
}

/*********/
void MissionStart()
{
    MISSION.progress = 0;
    MISSION.timer = TimerStart();
}

/*********/
void MissionUpdate()
{
    if(TimerGet(MISSION.timer)>100)
    {
        MISSION.progress++;

        DrawBar(1,23,38,MISSION.progress);

        MISSION.timer = TimerStart();
    }
}

/*********/
void MissionUpdateNoBar()
{
    if(TimerGet(MISSION.timer)>250)
    {
        MISSION.progress++;

        MISSION.timer = TimerStart();
    }
}

/*********/
unsigned char MissionCompleted()
{
    return MISSION.progress >= 38;
}