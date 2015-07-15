#include "prototypes.h"

/* Direction aléatoire du monstre */
int randomDirection(GameObject *entity)
{
    int i;
    float borneMinimale = 1; /* Le résultat doit être entre 1 et 4 inclut */
    float borneMaximale = 4;



    /*Le monstre alterne entre un déplacement aléatoire de 100 ms et un moment d'inactivité de 50 ms */
    if(entity->name != MASTER_BLAGULE)
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
                for(i = 0 ; i < 200000 ; i++)
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


/* La fonction pour l'alternative, mais elle ne me plaît pas :( */
void secondDirection(GameObject *entity)
{
    if(entity->direction == RIGHT) randomDirection(entity);
    if(entity->direction == LEFT) randomDirection(entity);
    if(entity->direction == DOWN) randomDirection(entity);
    if(entity->direction == UP) randomDirection(entity);

}


/* Les quatre fonctions de direction du joueur */
void playerLeft(Input *input, GameObject *entity)
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

        if(entity->etat != WALK_HORIZONTAL && input->input1 == INPUT_LEFT)
        {
            /* On enregistre l'anim' de la marche et on l'initialise à 0 */
            entity->etat = WALK_HORIZONTAL;
            entity->frameNumber = 0;
            entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        }

        /* pour mes belles diagonales :D */
        if(input->up && input->input1 == INPUT_LEFT)
        {
            input->input2 = INPUT_UP;
            entity->dirY -= PLAYER_SPEED;
        }

        if(input->down && input->input1 == INPUT_LEFT)
        {
            input->input2 = INPUT_DOWN;
            entity->dirY += PLAYER_SPEED;
        }
    }

}



void playerRight(Input *input, GameObject *entity)
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
        if(entity->etat != WALK_HORIZONTAL && input->input1 == INPUT_RIGHT)
        {
            /* On enregistre l'anim' de la marche et on l'initialise à 0 */
            entity->etat = WALK_HORIZONTAL;
            entity->frameNumber = 0;
            entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        }

        if(input->up && input->input1 == INPUT_RIGHT)
        {
            input->input2 = INPUT_UP;
            if(entity->etat != ATTACK_HORIZONTAL) entity->dirY -= PLAYER_SPEED;
        }

        if(input->down && input->input1 == INPUT_RIGHT)
        {
            input->input2 = INPUT_DOWN;
            if(entity->etat != ATTACK_HORIZONTAL) entity->dirY += PLAYER_SPEED;
        }
    }

}



void playerDown(Input *input, GameObject *entity)
{
    if(input->down && !input->up && (input->input1 == INPUT_DOWN || input->input1 == NONE))
    {
        input->input1 = INPUT_DOWN;

        entity->dirY += PLAYER_SPEED;
        entity->frameMax = 9;
        entity->direction = DOWN;


        if(entity->etat != WALK_DOWN && input->input1 == INPUT_DOWN)
        {
            entity->etat = WALK_DOWN;
            entity->frameNumber = 0;
            entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        }
        if(input->left && input->input1 == INPUT_DOWN)
        {
            input->input2 = INPUT_LEFT;
            entity->dirX -= PLAYER_SPEED;
        }

        if(input->right && input->input1 == INPUT_DOWN)
        {
            input->input2 = INPUT_RIGHT;
            entity->dirX += PLAYER_SPEED;
        }
    }

}



void playerUp(Input *input, GameObject *entity)
{
    if(input->up && !input->down && (input->input1 == INPUT_UP || input->input1 == NONE))
    {
        input->input1 = INPUT_UP;

        entity->dirY -= PLAYER_SPEED;
        entity->frameMax = 9;
        entity->direction = UP;

        if(entity->etat != WALK_UP && input->input1 == INPUT_UP)
        {
            entity->etat = WALK_UP;
            entity->frameNumber = 0;
            entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        }

        if(input->left && input->input1 == INPUT_UP)
        {
            input->input2 = INPUT_LEFT;
            entity->dirX -= PLAYER_SPEED;
        }

        if(input->right && input->input1 == INPUT_UP)
        {
            input->input2 = INPUT_RIGHT;
            entity->dirX += PLAYER_SPEED;
        }
    }

}



void playerDirection(Input *input, GameObject *entity)
{
    playerLeft(input, entity);
    playerDown(input, entity);
    playerUp(input, entity);
    playerRight(input, entity);

}



void playerIdleHorizontale(GameObject *entity)
{
    /* On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
    à chaque tour de boucle */
    if(entity->etat == WALK_HORIZONTAL)
    {
        entity->dirX = 0;
        entity->dirY = 0;

        /* On enregistre l'anim' de l'inactivité et on l'initialise à 0 */
        entity->etat = IDLE_HORIZONTAL;
        entity->frameNumber = 0;
        entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        entity->frameMax = 9;
    }

}



void playerIdleVerticale(GameObject *entity)
{
    if(entity->etat == WALK_UP || entity->etat == WALK_DOWN)
    {
        entity->dirX = 0;
        entity->dirY = 0;
        entity->etat = entity->etat == WALK_UP ? IDLE_UP : IDLE_DOWN;
        entity->frameNumber = 0;
        entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        entity->frameMax = 9;
    }

}



void playerIdle(Input *input, GameObject *entity)
{
    if((!input->right && !input->left && input->pressed <= 1) || (input->left && input->right) || ((input->left || input->right) && (input->up && input->down)))
    {
        if(input->left && input->right) entity->attack = 1;
        playerIdleHorizontale(entity);
        fprintf(stderr, "r");
    }

    /* Idem qu'au-dessus mais pour l'axe Y */
    if((!input->up && !input->down && input->pressed <= 1) || (input->up && input->down) || ((input->up || input->down) && (input->left && input->right)))
    {
        if(input->up && input->down) entity->attack = 1;
        playerIdleVerticale(entity);
    }

}



void entityTouch(GameObject *entity)
{
    if(entity->timerTouch <= 0)
    {
        entity->timerTouch = 20;
        entity->touche = 0;

    }
    else entity->timerTouch--;

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
    if(defenseur->y + defenseur->h / 2 <= attaquant.y + attaquant.h / 2) setEntityDirY(defenseur, -PLAYER_HURT);
    else setEntityDirY(defenseur, PLAYER_HURT);

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







