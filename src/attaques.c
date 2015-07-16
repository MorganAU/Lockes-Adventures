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

    /* Réinitialise l'attaque */
    if(entity->attack && !input->attack) entity->attack = 0;

}



int canAttack(GameObject *entity) //Vérifie si le joueur peut attaquer
{
    if(!entity->attack) return entity->canSwordAttack = 1;
    else return 0;


}



void drawOneHandAttack(GameObject *entity) // Pour dessiner l'attaque (le geste de la main sans l'arme)
{
    entity->dirX = 0;
    entity->dirY = 0;

    entity->etat = entity->direction == LEFT || entity->direction == RIGHT ? ATTACK_HORIZONTAL :
                   entity->direction == DOWN ? ATTACK_DOWN :
                   entity->direction == UP ? ATTACK_UP :
                   0 ;

    entity->frameNumber = 0;
    entity->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER_ATTACK;
    entity->frameMax = 5;

    entity->attack = entity->canSwordAttack;
    entity->canSwordAttack = 0;

}
