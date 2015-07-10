#include "prototypes.h"



void gestionAttaque(Input *input, GameObject *entity)
{
    if(input->attack) canAttack(entity);

    if(entity->canSwordAttack)
    {
        if(entity->etat < ATTACK_HORIZONTAL) entity->saveEtat = entity->etat;

        drawOneHandAttack(entity);
        entity->estEnTrainDAttaquer = 1;
        playSoundFx(ONEHANDSWORD);
    }
    if(entity->attack && !input->attack) entity->attack = 0;

}



int canAttack(GameObject *entity) //Vérifie si le joueur peu attaquer
{
    if(!entity->attack) entity->canSwordAttack = 1;

    return entity->canSwordAttack;
}



void drawOneHandAttack(GameObject *entity) // Pour dessiner l'attaque (le geste de la main sans l'arme)
{
    entity->dirX = 0;
    entity->dirY = 0;

    if(entity->direction == LEFT || entity->direction == RIGHT)
    {
        /* On enregistre l'anim' de la marche et on l'initialise à 0 */
        entity->etat = ATTACK_HORIZONTAL;
        entity->frameNumber = 0;
        entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER_ATTACK;
        entity->frameMax = 5;

    }

    if(entity->direction == DOWN)
    {
        entity->etat = ATTACK_DOWN;
        entity->frameNumber = 0;
        entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER_ATTACK;
        entity->frameMax = 5;
    }

    if(entity->direction == UP)
    {
        entity->etat = ATTACK_UP;
        entity->frameNumber = 0;
        entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER_ATTACK;
        entity->frameMax = 5;
    }

    entity->attack = entity->canSwordAttack;
    entity->canSwordAttack = 0;

}
