#include "prototypes.h"

GameObject oneHand;


/* Fonction dessinant l'épée pour le moment */
void drawOnehand(void)
{
    GameObject *entity = getPlayer();

    int x, y;

    getOneHandDest(&x, &y);

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

    dest.x = getPlayerx() - getStartX() + x; //Il faut le x du joueur avec getPlayerx et getStartX
    dest.y = getPlayery() - getStartY() + y;
    dest.w = oneHand.w;
    dest.h = oneHand.h;

    SDL_Rect src;

    src.x = entity->frameNumber * oneHand.w;
    src.w = oneHand.w;
    src.h = oneHand.h;

    if(entity->state >= ATTACK_HORIZONTAL)
    {
        src.y = entity->state == ATTACK_HORIZONTAL ? SWORD * PLAYER_HEIGHT :
                entity->state == ATTACK_DOWN ? SWORD * PLAYER_HEIGHT + SWORD_HEIGHT_HORIZONTAL :
                entity->state == ATTACK_UP ? SWORD * PLAYER_HEIGHT + SWORD_HEIGHT_HORIZONTAL + SWORD_HEIGHT_DOWN :
                0;

        const SDL_RendererFlip flip =
            entity->direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        SDL_RenderCopyEx(getRenderer(), getSprite(), &src, &dest, 0, 0, flip);
    }

}



/* Série de fonctions renvoyant le x et le y en fonction de la frame */
void getOneHandDest(int *x, int *y)
{
    if(getPlayerDirection() == RIGHT)
        getOneHandDestRight(x, y);
    else if(getPlayerDirection() == LEFT)
        getOneHandDestLeft(x, y);
    else if(getPlayerDirection() == UP)
        getOneHandDestUp(x, y);
    else if(getPlayerDirection() == DOWN)
        getOneHandDestDown(x, y);

}



void getOneHandDestRight(int *x, int *y)
{
    getPlayerFrameNumber() == 0 ? (*x = 26, *y = 4) :
    getPlayerFrameNumber() == 1 ? (*x = 26, *y = 5) :
    getPlayerFrameNumber() == 2 ? (*x = 28, *y = 13) :
    getPlayerFrameNumber() == 3 ? (*x = 27, *y = 24) :
    getPlayerFrameNumber() == 4 ? (*x = 25, *y = 27) :
    0;

}



void getOneHandDestLeft(int *x, int *y)
{
    getPlayerFrameNumber() == 0 ? (*x = -13, *y = 4) :
    getPlayerFrameNumber() == 1 ? (*x = -13, *y = 5) :
    getPlayerFrameNumber() == 2 ? (*x = -15, *y = 13) :
    getPlayerFrameNumber() == 3 ? (*x = -14, *y = 24) :
    getPlayerFrameNumber() == 4 ? (*x = -12, *y = 27) :
    0;

}



void getOneHandDestUp(int *x, int *y)
{
    getPlayerFrameNumber() == 0 ? (*x = 0, *y = -2) :
    getPlayerFrameNumber() == 1 ? (*x = 7, *y = -6) :
    getPlayerFrameNumber() == 2 ? (*x = 13, *y = -8) :
    getPlayerFrameNumber() == 3 ? (*x = 18, *y = -6) :
    getPlayerFrameNumber() == 4 ? (*x = 21, *y = -2) :
    0;

}



void getOneHandDestDown(int *x, int *y)
{
    getPlayerFrameNumber() == 0 ? (*x = 16, *y = 34) :
    getPlayerFrameNumber() == 1 ? (*x = 14, *y = 35) :
    getPlayerFrameNumber() == 2 ? (*x = 11, *y = 38) :
    getPlayerFrameNumber() == 3 ? (*x = 7, *y = 35) :
    getPlayerFrameNumber() == 4 ? (*x = -5, *y = 34) :
    0;

}





/* Collision entre l'arme et le monstre */
int oneHandHurt(int mX, int mY, int mW, int mH)
{
    int hitboxX, hitboxY, hitboxW, hitboxH, x, y;

    getOneHandDest(&x, &y);

    /* Coordonnées de l'arme en fonction de la position du joueur */
    x = x + getPlayerx();
    y = y + getPlayery();

    if(getAttack())
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
                || (mY + mH <= hitboxY))
            return 0;
        else
            return 1;
    }
    else
        return 0;


}

