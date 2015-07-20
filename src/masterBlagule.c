#include "prototypes.h"

int count = 5;

int getMasterBlaguleWidth(int frame)
{
    if(frame <= 35)
        return 138;
    else //if(frame > 35)
        return 160;

}



int getMasterBlaguleHeight(int frame)
{
    return 99;

}



int getMasterBlaguleSourceX(int frame)
{
    if(frame <= 35)
        return 0;
    else if(frame == 37 || frame == 39 || frame == 41 || frame == 43 || frame == 45 || frame == 47 || frame == 49)
        return 138;
    else //if(frame == 36 || frame == 38 || frame == 40 || frame == 42 || frame == 44 || frame == 46 || frame == 48 || frame == 50)
        return 298;

    if(frame == 50) masterBlaguleAttack();

}



int getMasterBlaguleSourceY(int frame)
{
    return 170;

}



void masterBlaguleBlitt(int frameNumber, int *w, int *h, int *x, int *y)
{
    *w = getMasterBlaguleWidth(frameNumber);
    *h = getMasterBlaguleHeight(frameNumber);
    *x = getMasterBlaguleSourceX(frameNumber);
    *y = getMasterBlaguleSourceY(frameNumber);

}



int getMasterBlaguleFrameTimer(void)
{
    return 4;

}



int getMasterBlaguleFrameMax(void)
{
    return 50;

}



void masterBlaguleAttack(void)
{
    if(getMonsterNumber() == 1 && count > 0)
    {
        int espace = 10;

        initializeNewMonster(getMonsterX(0) - espace, getMonsterY(0) - espace, BLAGULE);
        initializeNewMonster(getMonsterX(0) + 122 + espace, getMonsterY(0) - espace, BLAGULE);
        initializeNewMonster(getMonsterX(0) - espace, getMonsterY(0) + 99 + espace, BLAGULE);
        initializeNewMonster(getMonsterX(0) + 122 + espace, getMonsterY(0) + 99 + espace, BLAGULE);

        count--;
    }

}



int getMasterBlaguleLife(void)
{
    return 5;

}
