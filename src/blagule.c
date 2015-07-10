#include "prototypes.h"


int getBlaguleWidth(int frame, int statut, int borned)
{
    int width;

    if(borned == 1)
    {
        if(statut == IDLE_HORIZONTAL ||
                ((statut == IDLE_UP || statut == IDLE_DOWN) && (frame == 0 || frame == 1)))
            width = 32;
        else if((statut == WALK_HORIZONTAL && (frame == 0 || frame == 2)) ||
                (statut == IDLE_DOWN && (frame == 2 || frame == 3)))
            width = 34;
        else if(statut == IDLE_UP && (frame == 2 || frame == 3))
            width = 35;
        else if(statut == WALK_HORIZONTAL && (frame == 1 || frame == 3))
            width = 37;
        else if((statut == WALK_UP || statut == WALK_DOWN) && (frame == 1 || frame == 3))
            width = 24;
        else if((statut == WALK_UP || statut == WALK_DOWN) && (frame == 0 || frame == 2))
            width = 28;
    }
    else if(borned == 0) width = 32;

    return width;

}



int getBlaguleHeight(int frame, int statut, int borned)
{
    int height;

    if(borned == 1)
    {
        if(statut == IDLE_HORIZONTAL || statut == WALK_HORIZONTAL || statut == IDLE_UP || statut == IDLE_DOWN)
            height = 24;
        else if((statut == WALK_DOWN || statut == WALK_UP) && (frame == 0 || frame == 2))
            height = 31;
        else if((statut == WALK_DOWN || statut == WALK_UP) && (frame == 1 || frame == 3))
            height = 37;
    }
    else if(borned == 0) height = 24;
    return height;

}



int getBlaguleSourceX(int frame, int statut, int borned)
{
    int srcX;
    if(borned == 1)
    {
        if((statut == IDLE_HORIZONTAL && frame < 3) ||
                ((statut == WALK_HORIZONTAL || statut == WALK_DOWN || statut == WALK_UP) && (frame == 0 || frame == 2)) ||
                ((statut == IDLE_DOWN || statut == IDLE_UP) && frame <= 1))
            srcX = 0;
        else if((statut == WALK_DOWN || statut == WALK_UP) && (frame == 1 || frame == 3))
            srcX = 28;
        else if((statut == IDLE_HORIZONTAL && frame == 3) ||
                ((statut == IDLE_DOWN || statut == IDLE_UP) && frame == 2))
            srcX = 32;
        else if(statut == WALK_HORIZONTAL && (frame == 1 || frame == 3))
            srcX = 34;
        else if(statut == IDLE_DOWN && frame == 3)
            srcX = 66;
        else if(statut == IDLE_UP && frame == 3)
            srcX = 67;
    }
    else if(borned == 0)
    {
        if(frame == 0 || frame == 2 || frame == 4 || frame == 6 || frame == 8) srcX = 64;
        else if(frame == 1 || frame == 3 || frame == 5 || frame == 7 || frame == 9) srcX = 96;
    }

    return srcX;

}



int getBlaguleSourceY(int frame, int statut, int borned)
{
    int srcY;
    if(borned == 1)
    {
        if(statut == IDLE_HORIZONTAL) srcY = 0;
        else if(statut == WALK_HORIZONTAL) srcY = 24;
        else if(statut == IDLE_UP) srcY = 48;
        else if(statut == WALK_UP) srcY = 72;
        else if(statut == IDLE_DOWN) srcY = 109;
        else if(statut == WALK_DOWN && (frame == 0 || frame == 2)) srcY = 139;
        else if(statut == WALK_DOWN && (frame == 1 || frame == 3)) srcY = 133;
    }
    else if(borned == 0) srcY = 0;

    return srcY;

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
    int max;
    if(borned == 1) max = 3;
    else if(borned == 0) max = 9;
    return max;

}



int blaguleRandomMoves(GameObject *entity)
{
    float borneMinimale = 1; /* Le résultat doit être entre 1 et 4 inclut */
    float borneMaximale = 4;

    /*Le monstre alterne entre un déplacement aléatoire de 100 ms et
    un moment d'inactivité de 50 ms */

    if(entity->borned == 1)
    {
        if(entity->timerRandDir <= 0)
        {
            srand((unsigned)time(NULL));
            if(entity->directionAleatoire != 0)
            {
                entity->timerRandDir = 50;
                entity->directionAleatoire = 0;
                entity->frameNumber = 0;
                entity->etat -= 1;
                entity->saveDirection = entity->direction;
            }
            else
            {
                for(int i = 0 ; i < 200000 ; i++)
                {
                    entity->directionAleatoire = rand();
                    entity->directionAleatoire = (int)(entity->directionAleatoire * (borneMaximale + 1 - borneMinimale)
                                                   / RAND_MAX + borneMinimale );
                }

                entity->timerRandDir = 100;
                entity->frameNumber = 0;
                entity->etat -= 1;
            }
        }
        else entity->timerRandDir--;

    }

    return entity->directionAleatoire;

}

