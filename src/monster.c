#include "prototypes.h"

int nombreMonstres;
GameObject monster[MONSTRES_MAX];
SDL_Texture *monsterSprite;


/* Retourne un monstre donné */
GameObject *getMonster(int nombre)
{
    return &monster[nombre];

}



/* Retourne la coordonnée x d'un monstre donné */
int getMonsterX(int nombre)
{
    return monster[nombre].x;

}



/* Retourne la coordonnée y d'un monstre donné */
int getMonsterY(int nombre)
{
    return monster[nombre].y;

}



/* Retourne le nombre de monstre */
int getMonsterNumber(void)
{
    return nombreMonstres;

}




/* Réinitialise le nombre de monstres à zéro */
void resetMonsters(void)
{
    nombreMonstres = 0;

}




/* Charge le sprite des monstres */
void initMonsterSprites(void)
{
    monsterSprite = loadImage("ressources/graphics/sprites_monsters.png");

}




/* Libère le sprite des monstres */
void cleanMonsters(void)
{
    if(monsterSprite != NULL)
    {
        SDL_DestroyTexture(monsterSprite);
        monsterSprite = NULL;
    }

}



/* Initialise un nouveau monstre */
void initializeNewMonster(int x, int y, int name)
{
    /* Si on n'est pas rendu au max, on rajoute un monstre dont le numéro
    est égal à nombreMonstres : monster[0] si c'est le 1er, monster[1],
     si c'est le 2ème, etc... */

    if(nombreMonstres < MONSTRES_MAX)
    {
        /* On donne au monstre le nom de la MONSTER_TILE*/
        monster[nombreMonstres].name = name;

        /* Ses coordonnées de démarrage seront envoyées
        par la fonction drawMap() en arguments */
        monster[nombreMonstres].x = x;
        monster[nombreMonstres].y = y;

        /* On initialise ses stats (l'animation d'apparition, la numéro de la frame et sa direction) */
        initialiseStatsMonsters(&monster[nombreMonstres].borned, &monster[nombreMonstres].frameNumber, &monster[nombreMonstres].directionAleatoire);

        /* Variables nécessaires au fonctionnement
        de la gestion des collisions comme pour le héros */
        monster[nombreMonstres].timerMort = 0;

        nombreMonstres++;
    }

}



/* Fonction de gestion des monstres */
void updateMonsters(void)
{
    /* On passe en boucle tous les monstres du tableau */
    for(int i = 0 ; i < nombreMonstres ; i++)
    {
       /* Si le timer vaut 0 alors le monstre est vivant donc on peut le gérer */
        if(monster[i].timerMort == 0)
        {
            /* On réinitialise les vecteurs de déplacement, pour éviter que le GameObject
            ne fonce de plus en plus */
            monster[i].dirX = 0;
            monster[i].dirY = 0;

            /* Si l'animation est terminée alors le monstre est apparu */
            if(monsterWasBorned(&monster[i].frameNumber, monster[i].name)) monster[i].borned = 1;

            /* Direction virtuellement aléatoire */
            monster[i].direction = monsterMoves(&monster[i], monster[i].name);

            /* Déplacement du monstre selon la direction */
            monsterDirection(&monster[i].etat, &monster[i].dirX, &monster[i].dirY, monster[i].direction);

            /* On détecte les collisions avec la map */
            monsterCollisionToMap(&monster[i]);

            /* Si l'épée touche le monstre et que le joueur est en train d'attaquer, il y a collision. */
            if(oneHandHurt(monster[i].x, monster[i].y, monster[i].w, monster[i].h) && getAttack())
            {
                /*********** Ajouter gestion de la vie ***********/
                monster[i].timerMort = 1;
                playSoundFx(DESTROY);
            }

            /* On détecte les collisions avec le joueur. Si c'est égal à 1,
            on diminue ses PV */
            if(collide(getPlayer(), &monster[i]))
            {
                if (getLife() > 1) playerHurts(monster[i]);
                else if(getLife() == 1)
                {
                    killPlayer();
                    initialiseStatsMonsters(&monster[i].borned, &monster[i].frameNumber, &monster[i].directionAleatoire);
                    /********* Compteur de masterBlagule à réinitialiser quand le joueur meurt ********/
                }
                if(monster[i].etat != IDLE) monster[i].timerRandDir = 0;
            }
        }

        /* Si le monstre meurt, on active une tempo */
        if(monster[i].timerMort > 0)
        {
            monster[i].timerMort--;

            /* Et on le remplace simplement par le dernier du tableau puis
            on rétrécit le tableau d'une case (on ne peut pas laisser de case
            vide) */
            if(monster[i].timerMort == 0)
            {
                initialiseStatsMonsters(&monster[i].borned, &monster[i].frameNumber, &monster[i].directionAleatoire);
                monster[i] = monster[nombreMonstres - 1];
                nombreMonstres--;
            }
        }
    }

}



/* Fonction de gestion des collisions */
int collide(GameObject *player, GameObject *monster)
{
    if ((player->x >= monster->x + monster->w - 6)
            || (player->x + player->w <= monster->x + 6)
            || (player->y >= monster->y + monster->h - 6)
            || (player->y + player->h <= monster->y + 6)) return 0;

    else return 1;

}



void drawMonster(GameObject *entity)
{
    /* Gestion du timer */

    /* Si notre timer arrive à zéro */
    if(entity->frameTimer <= 0)
    {
        /* On le réinitialise */
        entity->frameTimer = getMonsterFrameTimer(entity->name);

        /* Et on incrémente notre variable qui compte les frames de 1
        pour passer à la suivante */
        entity->frameNumber++;

        /* Mais si on dépasse la frame max, il faut revenir à la première,
        sauf si c'est une animation unique (qui ne s'exécute qu'une seule fois
        comme les explosions), auquel cas, OneTimeAnimation vaudra 1. */
        if(entity->frameNumber > getMonsterFrameMax(entity->name, entity->borned)) entity->frameNumber = 0;
    }
    /* Sinon, on décrémente notre timer */
    else entity->frameTimer--;

    int srcX, srcY;

    monsterBlitt(entity->name, entity->etat, entity->frameNumber, &entity->w, &entity->h, &srcX, &srcY, entity->borned);
    /* Ensuite, on peut passer la main à notre fonction */

    /* Rectangle de destination à dessiner */
    SDL_Rect dest;

    /* On soustrait des coordonnées de notre monstre, ceux du début de la map,
    pour qu'il colle au scrolling : */
    dest.x = entity->x - getStartX();
    dest.y = entity->y - getStartY();
    dest.w = entity->w;
    dest.h = entity->h;

    /* Rectangle source */
    SDL_Rect src;

    /* Pour connaître le X de la bonne frame à dessiner,
    il suffit de multiplier la largeur du sprite par le numéro de la frame
    à afficher -> 0 = 0; 1 = 40; 2 = 80... */
    src.x = srcX;
    src.y = srcY;
    src.w = entity->w;
    src.h = entity->h;


    /* Gestion du flip (retournement de l'image selon que le monstre
    regarde à droite ou à gauche */
    if(entity->direction == LEFT || (entity->saveDirection == LEFT && entity->direction == IDLE))
        SDL_RenderCopyEx(getRenderer(), monsterSprite, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else SDL_RenderCopyEx(getRenderer(), monsterSprite, &src, &dest, 0, 0, SDL_FLIP_NONE);

}



int getMonsterFrameTimer(int name)
{
    if(name == BLAGULE) return getBlaguleFrameTimer();
    else if(name == MASTER_BLAGULE) return getMasterBlaguleFrameTimer();
    else return 0;

}



int getMonsterFrameMax(int name, int borned)
{
    if(name == BLAGULE) return getBlaguleFrameMax(borned);
    else if(name == MASTER_BLAGULE) return getMasterBlaguleFrameMax();
    else return 0;

}




void monsterBlitt(int name, int etat, int frameNumber, int *w, int *h, int *x, int *y, int borned)
{
    if(name == BLAGULE) blaguleBlitt(etat, frameNumber, w, h, x, y, borned);
    else if(name == MASTER_BLAGULE) masterBlaguleBlitt(frameNumber, w, h, x, y);

}



int monsterMoves(GameObject *entity, int name)
{
    if(name == BLAGULE) return blaguleRandomMoves(entity);
    else if(name == MASTER_BLAGULE) return 0;
    else return 0;

}



int monsterWasBorned(int *frame, int name)
{
    if(*frame == getMonsterFrameMax(name, 0))
    {
        *frame = 0;
        return 1;
    }
    else return 0;

}



void monsterDirection(int *etat, float *dX, float *dY, int direction)
{
    if(direction == LEFT)
    {
        *etat = WALK_HORIZONTAL;
        *dX -= 2;
    }
    else if(direction == RIGHT)
    {
        *etat = WALK_HORIZONTAL;
        *dX += 2;
    }
    else if(direction == UP)
    {
        *etat = WALK_UP;
        *dY -= 2;
    }
    else if(direction == DOWN)
    {
        *etat = WALK_DOWN;
        *dY += 2;
    }

}



void initialiseStatsMonsters(int *borned, int *frame, float *timerDeDir)
{
    *borned = 0;
    *frame = 0;
    *timerDeDir = 0;

}



