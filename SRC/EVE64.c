#include "player.h"
#include "mission.h"
#include "song.h"
#include "functions.h"

#include <conio.h>

static char *title1[] =
{
" ______   __   __   ______ ", 
"|      | |  | |  | |      |",
"|   ___| |  |_|  | |   ___|",
"|  |___  |       | |  |___ ",
"|   ___| |       | |   ___|",
"|  |___   |     |  |  |___ ",
"|______|   |___|   |______|"
};

static char *title2[] =
{
" _____    _   __ ",
"|  ___|  | | |  |",
"|  |___  | |_|  |",
"|   _  | |      |",
"|  | | | |___   |",
"|  |_| |     |  |",
"|______|     |__|"
};

/**********/
void main()
{
    unsigned char y;

    cursor(0);

    clrscr();

    for(;y<ARRAY_SIZE(title1);y++)
    {
        gotoxy(6,y+2);
        cprintf("%s",title1[y]);

        gotoxy(11,y+10);
        cprintf("%s",title2[y]);
    }

    gotoxy(4,20);
    cprintf("Generate a character using SPACE");

    gotoxy(4,21);
    cprintf("When ready, press ENTER to start");
    
    gotoxy(7,23);
    cprintf("PRESS ANY KEY TO CONTINUE");

    cgetc();

    do
    {
        clrscr();
        PlayerGenerate();
        PlayerDraw();

        
    } while(cgetc()!=0x0D);
    
    MissionGenerate();
    clrscr();
    MissionDraw();
    MissionStart();

    SongStart();
    
    while(1)
    {
        SongUpdate();
        MissionUpdate();
        
        if(MissionCompleted())
        {
            PlayerPostMission();

            //start empty cargo loop
            if(PlayerCargoItems()==10)
            {
                clrscr();
                SongUpdate();//EXTRA
                PlayerDrawSell();
                MissionStart();

                do
                {
                    SongUpdate();
                    MissionUpdate();

                    if(MissionCompleted())
                    {
                        PlayerPostSell();
                        
                        clrscr();
                        SongUpdate();//EXTRA
                        PlayerDrawSell();
                        MissionStart();
                    }

                } while (PlayerCargoItems()>0);
                
                //display stats for some seconds
                clrscr();
                SongUpdate();//EXTRA
                PlayerDraw();

                MissionStart();
                while(!MissionCompleted())
                {   
                    SongUpdate();
                    MissionUpdateNoBar();
                }

            };//end empty cargo loop

            //new mission
            MissionGenerate();
            clrscr();
            SongUpdate();//EXTRA
            MissionDraw();
            MissionStart();
        }

    };
}