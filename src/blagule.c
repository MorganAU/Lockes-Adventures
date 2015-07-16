#include "prototypes.h"


int getBlaguleWidth(int frame, int statut, int borned)
{
    if(borned)
    {
        if(statut == IDLE_HORIZONTAL ||
                ((statut == IDLE_UP || statut == IDLE_DOWN) && (frame == 0 || frame == 1)))
            return 32;
        else if((statut == WALK_HORIZONTAL && (frame == 0 || frame == 2)) ||
                (statut == IDLE_DOWN && (frame == 2 || frame == 3)))
            return 34;
        else if(statut == IDLE_UP && (frame == 2 || frame == 3))
            return 35;
        else if(statut == WALK_HORIZONTAL && (frame == 1 || frame == 3))
            return 37;
        else if((statut == WALK_UP || statut == WALK_DOWN) && (frame == 1 || frame == 3))
            return 24;
        else //if((statut == WALK_UP || statut == WALK_DOWN) && (frame == 0 || frame == 2))
            return 28;
    }
    else //if(!borned)
        return 32;

}



int getBlaguleHeight(int frame, int statut, int borned)
{
    if(borned)
    {
        if(statut == IDLE_HORIZONTAL || statut == WALK_HORIZONTAL || statut == IDLE_UP || statut == IDLE_DOWN)
            return 24;
        else if((statut == WALK_DOWN || statut == WALK_UP) && (frame == 0 || frame == 2))
            return 31;
        else //if((statut == WALK_DOWN || statut == WALK_UP) && (frame == 1 || frame == 3))
            return 37;
    }
    else //if(!borned)
        return 24;

}



int getBlaguleSourceX(int frame, int statut, int borned)
{
    if(borned)
    {
        if((statut == IDLE_HORIZONTAL && frame < 3) ||
                ((statut == WALK_HORIZONTAL || statut == WALK_DOWN || statut == WALK_UP) && (frame == 0 || frame == 2)) ||
                ((statut == IDLE_DOWN || statut == IDLE_UP) && frame <= 1))
            return 0;
        else if((statut == WALK_DOWN || statut == WALK_UP) && (frame == 1 || frame == 3))
            return 28;
        else if((statut == IDLE_HORIZONTAL && frame == 3) ||
                ((statut == IDLE_DOWN || statut == IDLE_UP) && frame == 2))
            return 32;
        else if(statut == WALK_HORIZONTAL && (frame == 1 || frame == 3))
            return 34;
        else if(statut == IDLE_DOWN && frame == 3)
            return 66;
        else //if(statut == IDLE_UP && frame == 3)
            return 67;
    }
    else //if(!borned)
    {
        if(frame == 0 || frame == 2 || frame == 4 || frame == 6 || frame == 8)
            return 64;
        else //if(frame == 1 || frame == 3 || frame == 5 || frame == 7 || frame == 9)
            return 96;
    }

}



int getBlaguleSourceY(int frame, int statut, int borned)
{
    if(borned)
    {
        if(statut == IDLE_HORIZONTAL)
            return 0;
        else if(statut == WALK_HORIZONTAL)
            return 24;
        else if(statut == IDLE_UP)
            return 48;
        else if(statut == WALK_UP)
            return 72;
        else if(statut == IDLE_DOWN)
            return 109;
        else if(statut == WALK_DOWN && (frame == 0 || frame == 2))
            return 139;
        else //if(statut == WALK_DOWN && (frame == 1 || frame == 3))
            return 133;
    }
    else //if(!borned)
        return 0;

}



void blaguleBlitt(int etat, int frameNumber, int *w, int *h, int *x, int *y, int borned)
{
    *w = getBlaguleWidth(frameNumber, etat, borned);
    *h = getBlaguleHeight(frameNumber, etat, borned);
    *x = getBlaguleSourceX(frameNumber, etat, borned);
    *y = getBlaguleSourceY(frameNumber, etat, borned);

}



int getBlaguleFrameTimer(void)
{
    return 12;

}



int getBlaguleFrameMax(int borned)
{
    if(borned)
        return 3;
    else //if(!borned)
        return 9;

}




