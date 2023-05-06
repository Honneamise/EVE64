#include "notes.h"
#include "functions.h"
#include <c64.h>

static unsigned long SONG_TIMER = 0UL;

static unsigned int SONG_INDEX = 0;

static unsigned SONG[][2] = 
    {
        { C4, 500UL},
        { G4, 250UL},
        { F4, 250UL},

        { C4, 500UL},
        { G4, 250UL},
        { F4, 250UL},

        { C4, 500UL},
        { G4, 250UL},
        { Ab4, 500UL},
    
        { G4, 250UL},
        { F4, 250UL},
        { G4, 250UL},

    };

/**********/
void SongStart()
{
    //this should go in generic SoundInit()
    SID.amp = 0xFF;
    SID.v1.ad = 0x0F;
    SID.v1.sr  = 0x0F;

    //start playing the first note
    SONG_INDEX = 0;
    SID.v1.freq = SONG[SONG_INDEX][0];
    SID.v1.ctrl = 0x11;
    SONG_TIMER = TimerStart();
}

/**********/
void SongUpdate()
{
    if(TimerGet(SONG_TIMER) < SONG[SONG_INDEX][1]) { return; } 
      
    SID.v1.ctrl = 0x10;//stop the note

    SONG_INDEX++;

    if( SONG_INDEX >= ARRAY_SIZE(SONG) ){ SONG_INDEX=0; }
    
    SID.v1.freq = SONG[SONG_INDEX][0];
    
    SID.v1.ctrl = 0x11;

    SONG_TIMER = TimerStart();
}