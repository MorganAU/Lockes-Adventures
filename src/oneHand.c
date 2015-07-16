#include "prototypes.h"

GameObject oneHand;


/* Fonction dessinant l'épée pour le moment */
void drawOnehand(void)
{
    GameObject *entity = getPlayer();

    /* Différentes valeurs en fonction de la direction, pour que les collisions soient plus précises */
    oneHand.w = getPlayerDirection() == RIGHT || getPlayerDirection() == LEFT ? SWORD_WIDTH_HORIZONTAL :
                getPlayerDirection() == DOWN ? SWORD_WIDTH_DOWN :
                getPlayerDirection() == UP ? SWORD_WIDTH_UP :
                0;

    oneHand.h = getPlayerDirection() == RIGHT || getPlayerDirection() == LEFT ? SWORD_HEIGHT_HORIZONTAL :
                getPlayerDirection() == DOWN ? SWORD_HEIGHT_DOWN :
                getPlayerDirection() == UP ? SWORD_HEIGHT_UP :
                0;

    SDL_Rect dest;

    dest.x = getPlayerx() - getStartX() + getOneHandX(); //Il faut le x du joueur avec getPlayerx et getStartX
    dest.y = getPlayery() - getStartY() + getOneHandY();
    dest.w = oneHand.w;
    dest.h = oneHand.h;

    SDL_Rect src;

    src.x = entity->frameNumber * oneHand.w;
    src.w = oneHand.w;
    src.h = oneHand.h;

    if(entity->etat >= ATTACK_HORIZONTAL)
    {
        src.y = entity->etat == ATTACK_HORIZONTAL ? SWORD * PLAYER_HEIGHT :
                entity->etat == ATTACK_DOWN ? SWORD * PLAYER_HEIGHT + SWORD_HEIGHT_HORIZONTAL :
                entity->etat == ATTACK_UP ? SWORD * PLAYER_HEIGHT + SWORD_HEIGHT_HORIZONTAL + SWORD_HEIGHT_DOWN :
                0;

        const SDL_RendererFlip flip =
            entity->direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        SDL_RenderCopyEx(getRenderer(), getSprite(), &src, &dest, 0, 0, flip);
    }

}



/* Fonction renvoyant le x en fonction de la frame */
int getOneHandX(void)
{
    if(getPlayerDirection() == RIGHT)
    {
        if(getPlayerFrameNumber() <= 1)
            return 26;
        else if(getPlayerFrameNumber() == 2)
            return 28;
        else if(getPlayerFrameNumber() == 3)
            return 27;
        else //if(getPlayerFrameNumber() == 4)
            return 25;
    }
    else if(getPlayerDirection() == LEFT)
    {
        if(getPlayerFrameNumber() <= 1)
            return -13;
        else if(getPlayerFrameNumber() == 2)
            return -15;
        else if(getPlayerFrameNumber() == 3)
            return -14;
        else //if(getPlayerFrameNumber() == 4)
            return -12;
    }
    else if(getPlayerDirection() == DOWN)
    {
        if(getPlayerFrameNumber() == 0)
            return 16;
        else if(getPlayerFrameNumber() == 1)
            return 14;
        else if(getPlayerFrameNumber() == 2)
            return 11;
        else if(getPlayerFrameNumber() == 3)
            return 7;
        else //if(getPlayerFrameNumber() == 4)
            return -5;
    }
    else //if(getPlayerDirection() == UP)
    {
        if(getPlayerFrameNumber() == 0)
            return 0;
        else if(getPlayerFrameNumber() == 1)
            return 7;
        else if(getPlayerFrameNumber() == 2)
            return 13;
        else if(getPlayerFrameNumber() == 3)
            return 18;
        else //if(getPlayerFrameNumber() == 4)
            return 21;
    }

}



/* Idem pour y */
int getOneHandY(void)
{
    int y;

    if(getPlayerDirection() == RIGHT)
    {
        if(getPlayerFrameNumber() == 0) y = 4;
        else if(getPlayerFrameNumber() == 1) y = 5;
        else if(getPlayerFrameNumber() == 2) y = 13;
        else if(getPlayerFrameNumber() == 3) y = 24;
        else if(getPlayerFrameNumber() == 4) y = 27;
    }
    else if(getPlayerDirection() == LEFT)
    {
        if(getPlayerFrameNumber() == 0) y = 4;
        else if(getPlayerFrameNumber() == 1) y = 5;
        else if(getPlayerFrameNumber() == 2) y = 13;
        else if(getPlayerFrameNumber() == 3) y = 24;
        else if(getPlayerFrameNumber() == 4) y = 27;
    }
    else if(getPlayerDirection() == DOWN)
    {
        if(getPlayerFrameNumber() == 0) y = 34;
        else if(getPlayerFrameNumber() == 1) y = 35;
        else if(getPlayerFrameNumber() == 2) y = 38;
        else if(getPlayerFrameNumber() == 3) y = 35;
        else if(getPlayerFrameNumber() == 4) y = 34;
    }
    else if(getPlayerDirection() == UP)
    {
        if(getPlayerFrameNumber() == 0) y = -2;
        else if(getPlayerFrameNumber() == 1) y = -6;
        else if(getPlayerFrameNumber() == 2) y = -8;
        else if(getPlayerFrameNumber() == 3) y = -6;
        else if(getPlayerFrameNumber() == 4) y = -2;
    }

    return y;

}



/* Collision entre l'arme et le monstre */
int oneHandHurt(int mX, int mY, int mW, int mH)
{
    int hitboxX, hitboxY, hitboxW, hitboxH;

    /* Coordonnées de l'arme en fonction de la position du joueur */
    int x = getOneHandX() + getPlayerx();
    int y = getOneHandY() + getPlayery();
    if(getAttack() == 1)
    {

        if(getPlayerDirection() == UP)
        {
            hitboxX = x - 5;
            hitboxY = y - 5;
            hitboxW = oneHand.w + 5;
            hitboxH = 5;
        }
        else if(getPlayerDirection() == DOWN)
        {
            hitboxX = x - 5;
            hitboxY = y + oneHand.h;
            hitboxW = oneHand.w + 5;
            hitboxH = 5;
        }
        if(getPlayerDirection() == RIGHT)
        {
            hitboxX = x + oneHand.w;
            hitboxY = y;
            hitboxW = 5;
            hitboxH = oneHand.h + 15;
        }
        else if(getPlayerDirection() == LEFT)
        {
            hitboxX = x - 5;
            hitboxY = y;
            hitboxW = 5;
            hitboxH = oneHand.h + 15;
        }


        if ((mX >= hitboxX + hitboxW)
                || (mX + mW <= hitboxX)
                || (mY >= hitboxY + hitboxH )
                || (mY + mH <= hitboxY)) return 0;
        else return 1;
    }
    else return 0;


}

