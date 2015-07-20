#include "prototypes.h"


int getBlaguleWidth(int frame, int state, int borned)
{
    if(borned)
    {
        if(state == IDLE_HORIZONTAL ||
                ((state == IDLE_UP || state == IDLE_DOWN) && (frame == 0 || frame == 1)))
            return 32;
        else if((state == WALK_HORIZONTAL && (frame == 0 || frame == 2)) ||
                (state == IDLE_DOWN && (frame == 2 || frame == 3)))
            return 34;
        else if(state == IDLE_UP && (frame == 2 || frame == 3))
            return 35;
        else if(state == WALK_HORIZONTAL && (frame == 1 || frame == 3))
            return 37;
        else if((state == WALK_UP || state == WALK_DOWN) && (frame == 1 || frame == 3))
            return 24;
        else //if((state == WALK_UP || state == WALK_DOWN) && (frame == 0 || frame == 2))
            return 28;
    }
    else //if(!borned)
        return 32;

}



int getBlaguleHeight(int frame, int state, int borned)
{
    if(borned)
    {
        if(state == IDLE_HORIZONTAL || state == WALK_HORIZONTAL || state == IDLE_UP || state == IDLE_DOWN)
            return 24;
        else if((state == WALK_DOWN || state == WALK_UP) && (frame == 0 || frame == 2))
            return 31;
        else //if((state == WALK_DOWN || state == WALK_UP) && (frame == 1 || frame == 3))
            return 37;
    }
    else //if(!borned)
        return 24;

}



int getBlaguleSourceX(int frame, int state, int borned)
{
    if(borned)
    {
        if((state == IDLE_HORIZONTAL && frame < 3) ||
                ((state == WALK_HORIZONTAL || state == WALK_DOWN || state == WALK_UP) && (frame == 0 || frame == 2)) ||
                ((state == IDLE_DOWN || state == IDLE_UP) && frame <= 1))
            return 0;
        else if((state == WALK_DOWN || state == WALK_UP) && (frame == 1 || frame == 3))
            return 28;
        else if((state == IDLE_HORIZONTAL && frame == 3) ||
                ((state == IDLE_DOWN || state == IDLE_UP) && frame == 2))
            return 32;
        else if(state == WALK_HORIZONTAL && (frame == 1 || frame == 3))
            return 34;
        else if(state == IDLE_DOWN && frame == 3)
            return 66;
        else //if(state == IDLE_UP && frame == 3)
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



int getBlaguleSourceY(int frame, int state, int borned)
{
    if(borned)
    {
        if(state == IDLE_HORIZONTAL)
            return 0;
        else if(state == WALK_HORIZONTAL)
            return 24;
        else if(state == IDLE_UP)
            return 48;
        else if(state == WALK_UP)
            return 72;
        else if(state == IDLE_DOWN)
            return 109;
        else if(state == WALK_DOWN && (frame == 0 || frame == 2))
            return 139;
        else //if(state == WALK_DOWN && (frame == 1 || frame == 3))
            return 133;
    }
    else //if(!borned)
        return 0;

}



void blaguleBlitt(int state, int frameNumber, int *w, int *h, int *x, int *y, int borned)
{
    *w = getBlaguleWidth(frameNumber, state, borned);
    *h = getBlaguleHeight(frameNumber, state, borned);
    *x = getBlaguleSourceX(frameNumber, state, borned);
    *y = getBlaguleSourceY(frameNumber, state, borned);

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




