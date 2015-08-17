#include "prototypes.h"

/* Direction aléatoire du monstre */
int randomDirection(GameObject *entity)
{
    float lowerBound = 1; /* Le résultat doit être entre 1 et 4 inclut */
    float upperBound = 4;

    /*Le monstre alterne entre un déplacement aléatoire de 100 ms et
    un moment d'inactivité de 50 ms */

    if(entity->borned)
    {
        if(entity->timerRandDir <= 0)
        {
            srand((unsigned)time(NULL));
            if(entity->randomDir != 0)
            {
                entity->timerRandDir = 50;
                entity->randomDir = 0;
                entity->frameNumber = 0;
                entity->state -= 1;
                entity->saveDirection = entity->direction;
            }
            else
            {
                for(int i = 0 ; i < 200000 ; i++)
                {
                    entity->randomDir = rand();
                    entity->randomDir = (int)(entity->randomDir * (upperBound + 1 - lowerBound)
                                                       / RAND_MAX + lowerBound );
                }

                entity->timerRandDir = 100;
                entity->frameNumber = 0;
                entity->state -= 1;
            }
        }
        else entity->timerRandDir--;
    }

    return entity->randomDir;

}



/* Les quatre fonctions de direction du joueur */
void playerDirLeft(Input *input, GameObject *entity)
{
    /* Le héros ne bouge pas si on appuie sur gauche et droite en même temps */
    if(input->left && !input->right && (input->input1 == INPUT_LEFT || input->input1 == NONE))
    {
        input->input1 = INPUT_LEFT;

        entity->dirX -= PLAYER_SPEED;
        entity->frameMax = 9;

        /* Et on indique qu'il va à gauche */
        entity->direction = LEFT;

        /* Si ce n'était pas son état auparavant */
        if(entity->state != WALK_HORIZONTAL)
        {
            /* On enregistre l'anim' de la marche et on l'initialise à 0 */
            entity->state = WALK_HORIZONTAL;
            entity->frameNumber = 0;
            entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        }

        /* pour mes belles diagonales */
        if(input->up)
        {
            input->input2 = INPUT_UP;
            entity->dirY -= PLAYER_SPEED;
        }

        if(input->down)
        {
            input->input2 = INPUT_DOWN;
            entity->dirY += PLAYER_SPEED;
        }
    }

}



void playerDirRight(Input *input, GameObject *entity)
{
    if(input->right && !input->left && (input->input1 == INPUT_RIGHT || input->input1 == NONE))
    {
        input->input1 = INPUT_RIGHT;

        /* On augmente les coordonnées en x du joueur */
        entity->dirX += PLAYER_SPEED;
        entity->frameMax = 9;

        /* Et on indique qu'il va à droite */
        entity->direction = RIGHT;

        /* Si ce n'était pas son état auparavant */
        if(entity->state != WALK_HORIZONTAL)
        {
            /* On enregistre l'anim' de la marche et on l'initialise à 0 */
            entity->state = WALK_HORIZONTAL;
            entity->frameNumber = 0;
            entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        }

        if(input->up)
        {
            input->input2 = INPUT_UP;
            entity->dirY -= PLAYER_SPEED;
        }

        if(input->down)
        {
            input->input2 = INPUT_DOWN;
            entity->dirY += PLAYER_SPEED;
        }
    }

}



void playerDirDown(Input *input, GameObject *entity)
{
    if(input->down && !input->up && (input->input1 == INPUT_DOWN || input->input1 == NONE))
    {
        input->input1 = INPUT_DOWN;

        entity->dirY += PLAYER_SPEED;
        entity->frameMax = 9;
        entity->direction = DOWN;


        if(entity->state != WALK_DOWN)
        {
            entity->state = WALK_DOWN;
            entity->frameNumber = 0;
            entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        }
        if(input->left)
        {
            input->input2 = INPUT_LEFT;
            entity->dirX -= PLAYER_SPEED;
        }

        if(input->right)
        {
            input->input2 = INPUT_RIGHT;
            entity->dirX += PLAYER_SPEED;
        }
    }

}



void playerDirUp(Input *input, GameObject *entity)
{
    if(input->up && !input->down && (input->input1 == INPUT_UP || input->input1 == NONE))
    {
        input->input1 = INPUT_UP;

        entity->dirY -= PLAYER_SPEED;
        entity->frameMax = 9;
        entity->direction = UP;

        if(entity->state != WALK_UP)
        {
            entity->state = WALK_UP;
            entity->frameNumber = 0;
            entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        }

        if(input->left)
        {
            input->input2 = INPUT_LEFT;
            entity->dirX -= PLAYER_SPEED;
        }

        if(input->right)
        {
            input->input2 = INPUT_RIGHT;
            entity->dirX += PLAYER_SPEED;
        }
    }

}



void playerDir(Input *input, GameObject *entity)
{
    playerDirLeft(input, entity);
    playerDirDown(input, entity);
    playerDirUp(input, entity);
    playerDirRight(input, entity);

}



void playerIdleHorizontale(GameObject *entity)
{
    /* On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
    à chaque tour de boucle */
    if(entity->state == WALK_HORIZONTAL)
    {
        entity->dirX = 0;
        entity->dirY = 0;

        /* On enregistre l'anim' de l'inactivité et on l'initialise à 0 */
        entity->state = IDLE_HORIZONTAL;
        entity->frameNumber = 0;
        entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        entity->frameMax = 9;
    }

}



void playerIdleVerticale(GameObject *entity)
{
    if(entity->state == WALK_UP || entity->state == WALK_DOWN)
    {
        entity->dirX = 0;
        entity->dirY = 0;
        entity->state = entity->state == WALK_UP ? IDLE_UP : IDLE_DOWN;
        entity->frameNumber = 0;
        entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        entity->frameMax = 9;
    }

}



void playerIdle(Input *input, GameObject *entity)
{
    if((!input->right && !input->left && input->puched <= 1) || (input->left && input->right) || ((input->left || input->right) && (input->up && input->down)))
    {
        playerIdleHorizontale(entity);
    }

    /* Idem qu'au-dessus mais pour l'axe Y */
    if((!input->up && !input->down && input->puched <= 1) || (input->up && input->down) || ((input->up || input->down) && (input->left && input->right)))
    {
        playerIdleVerticale(entity);
    }

}



void setEntityDirX(GameObject *entity, float valeur)
{
    entity->dirX = valeur;

}



void setEntityDirY(GameObject *entity, float valeur)
{
    entity->dirY = valeur;

}



void touchDirLeft(GameObject *defenseur, GameObject attaquant)
{

    setEntityDirX(defenseur, PLAYER_HURT);
    if(defenseur->y + defenseur->h / 2 <= attaquant.y + attaquant.h / 2)
        setEntityDirY(defenseur, -PLAYER_HURT);
    else
        setEntityDirY(defenseur, PLAYER_HURT);

}



void touchDirRight(GameObject *defenseur, GameObject attaquant)
{
    setEntityDirX(defenseur, -PLAYER_HURT);
    if(defenseur->y + defenseur->h / 2  <= attaquant.y + attaquant.h / 2) setEntityDirY(defenseur, -PLAYER_HURT);
    else setEntityDirY(defenseur, PLAYER_HURT);

}



void touchDirUp(GameObject *defenseur, GameObject attaquant)
{
    setEntityDirY(defenseur, PLAYER_HURT);
    if(defenseur->x + defenseur->w / 2  <= attaquant.x + attaquant.w / 2) setEntityDirX(defenseur, -PLAYER_HURT);
    else setEntityDirX(defenseur, PLAYER_HURT);

}



void touchDirDown(GameObject *defenseur, GameObject attaquant)
{
    setEntityDirY(defenseur, -PLAYER_HURT);
    if(defenseur->x + defenseur->w / 2  <= attaquant.x + attaquant.w / 2) setEntityDirX(defenseur, -PLAYER_HURT);
    else setEntityDirX(defenseur, PLAYER_HURT);

}



void touchDir(int direction, GameObject *defenseur, GameObject attaquant)
{
    if(direction == LEFT) touchDirLeft(defenseur, attaquant);
    else if(direction == RIGHT) touchDirRight(defenseur, attaquant);
    else if(direction == UP) touchDirUp(defenseur, attaquant);
    else if(direction == DOWN) touchDirDown(defenseur, attaquant);

}







