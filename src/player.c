#include "prototypes.h"

int level;
int vies, etoiles;
GameObject player;
SDL_Texture *playerSpriteSheet;


/* Renvoie le GameObject player (h�ros) */
GameObject *getPlayer(void)
{
    return &player;

}



int getAttack(void)
{
    return player.estEnTrainDAttaquer;

}



SDL_Texture *getSprite(void)
{
    return playerSpriteSheet;

}



/* Renvoie les coordonn�es x du h�ros */
int getPlayerx(void)
{
    return player.x;

}



/* Renvoie les coordonn�es y du h�ros */
int getPlayery(void)
{
    return player.y;

}



/* Change la valeur des coordonn�es x du h�ros */
void setPlayerx(int valeur)
{
    player.x = valeur;

}



int getPlayerFrameNumber(void)
{
    return player.frameNumber;

}



int getPlayerDirection(void)
{
    return player.direction;

}



/* Change la valeur des coordonn�es y du h�ros */
void setPlayery(int valeur)
{
    player.y = valeur;

}



void setPlayerDirX(float valeur)
{
    player.dirX = valeur;

}



void setPlayerDirY(float valeur)
{
    player.dirY = valeur;

}



/* Renvoie le num�ro du niveau en cours */
int getLevel(void)
{
    return level;

}



/* Change la valeur du niveau en cours */
void setValeurDuNiveau(int valeur)
{
    level = valeur;

}



int getNombreDeVies(void)
{
    return vies;

}



void setNombreDeVies(int valeur)
{
    vies = valeur;

}



int getNombreDetoiles(void)
{
    return etoiles;

}



void setNombreDetoiles(int valeur)
{
    etoiles = valeur;

}



/* Charge le spritesheet de notre h�ros au d�but du jeu */
void initPlayerSprites(void)
{
    playerSpriteSheet = loadImage("ressources/graphics/sprite_hero2.png");

}



/* Lib�re le sprite du h�ros � la fin du jeu */
void cleanPlayer(void)
{
    if(playerSpriteSheet != NULL)
    {
        SDL_DestroyTexture(playerSpriteSheet);
        playerSpriteSheet = NULL;
    }

}



int getLife(void)
{
    return player.life;

}



int getLifeMax(void)
{
    return player.lifeMax;

}



void killPlayer(void)
{
    /* On met le timer � 1 pour tuer le joueur instantan�ment */
    player.timerMort = 1;

    /* On joue le son */
    playSoundFx(DESTROY);

}



void playerHurts(GameObject entity)
{
    /* Si le timer d'invincibilit� est � 0, on perd un coeur */
    if(player.invincibleTimer == 0)
    {
        player.life--; //En commentaire, toujours pour les tests
        player.invincibleTimer = 10;

        touchDir(player.direction, &player, entity);

        playSoundFx(DESTROY);
        player.touche = 1;
    }

}


int getHurts(void)
{
    return player.touche;

}



/* Initialise le h�ros */
void initializePlayer(int newLevel)
{
    /* PV � 3 */

    player.lifeMax = 12;
    player.life = 12;

    /* Timer d'invincibilit� */
    player.invincibleTimer = 0;
    player.timerTouch = 20;

    /* Indique l'�tat et la direction de notre h�ros */
    player.direction = DOWN;
    player.etat = IDLE_DOWN;

    /* Indique le num�ro de la frame o� commencer */
    player.frameNumber = 0;

    /* ... la valeur de son chrono au timer */
    player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

    /* ... et son nombre de frame max */
    player.frameMax = 9;

    player.x = getBeginX();
    player.y = getBeginY();

    /* On r�initialise les coordonn�es de la cam�ra si on change de niveau */
    if(newLevel == 1)
    {
        setStartX(getBeginX());
        setStartY(getBeginY());
    }

    /* Hauteur et largeur de notre h�ros */
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGHT;

    /* Variables n�cessaires au fonctionnement de la gestion des collisions */
    player.timerMort = 0;

    /* R�initialise les monstres */
    /* Lib�re le sprite des monstres */
    resetMonsters();

}



void drawPlayer(void)
{
    /* Gestion du timer */

    /* Si notre timer (un compte � rebours en fait) arrive � z�ro */
    if(player.etat <= WALK_DOWN) walkFrameTimer();
    else attackFrameTimer();

    /* Ensuite, on peut passer la main � notre fonction */

    /* Rectangle de destination � dessiner */
    SDL_Rect dest;

    /* On soustrait des coordonn�es de notre h�ros, ceux du d�but de la map,
    pour qu'il colle au scrolling : */
    dest.x = player.x - getStartX();
    dest.y = player.y - getStartY();
    dest.w = player.w;
    dest.h = player.h;

    /* Rectangle source */
    SDL_Rect src;

    /* Pour conna�tre le X de la bonne frame � dessiner, il suffit de multiplier
    la largeur du sprite par le num�ro de la frame � afficher -> 0 = 0; 1 = 40; 2 = 80... */

    src.x = player.frameNumber * player.w;
    src.w = player.w;
    src.h = player.h;

    /* On calcule le Y de la bonne frame � dessiner, selon la valeur de l'�tat du h�ros :
    Aucun mouvement (Idle) = 0, marche (walk) = 1, etc...
    Tout cela en accord avec notre spritesheet, of course ;) */

    src.y = player.etat * player.h;

    /* Si on a �t� touch�, et qu'on est invincible */
    int q;

    if(player.invincibleTimer > 0) q = 2;
    else q = 1;

    /* On fait clignoter le h�ros une frame sur deux; Pour �a, on calcule
    si le num�ro de la frame est un multiple de deux */
    if(player.frameNumber % q == 0)
    {
        /* Gestion du flip (retournement de l'image selon que le sprite regarde � droite ou
        � gauche */
        const SDL_RendererFlip flip =
            player.direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        SDL_RenderCopyEx(getRenderer(), playerSpriteSheet, &src, &dest, 0, 0, flip);
    }

}



void updatePlayer(Input *input)
{
    /* On rajoute un timer au cas o� notre h�ros mourrait
    Si le timer vaut 0, c'est que tout va bien, sinon, on le d�cr�mente jusqu'� 0, et l�,
    on r�initialise.
    C'est pour �a qu'on ne g�re le joueur que si ce timer vaut 0. */
    if(player.timerMort == 0)
    {
        if(!player.touche) // S'il n'est pas touch�
        {
            /* On g�re le timer de l'invincibilit� */
            if(player.invincibleTimer > 0) player.invincibleTimer--;

            /* On r�initialise notre vecteur de d�placement lat�ral (X), pour �viter que le perso
            ne fonce de plus en plus */
            player.dirX = player.dirY = player.estEnTrainDAttaquer = 0;

            gestionAttaque(input, &player);

            if(player.etat < ATTACK_HORIZONTAL && input->pressed < 3) playerDirection(input, &player);

            /* Si on n'appuie sur rien, on charge l'animation marquant l'inactivit� (Idle), je n'ai pas regarder encore si je pouvais l'optimiser */
            playerIdle(input, &player);

            resetInput(input);
        }
        /* Sinon si il est touch� */
        else if(player.touche) entityTouch();

        /* On rajoute notre fonction de d�tection des collisions qui va mettre �
        jour les coordonn�es de notre h�ros. */
        mapCollision(&player);

        /* On g�re le scrolling */
        centerScrollingOnPlayer();
    }



    /*Gestion de la mort. Si timerMort est diff�rent de 0, c'est qu'il faut r�initialiser le joueur.
    On ignore alors ce qui pr�c�de et on joue cette boucle (un wait en fait) jusqu'� ce que
    timerMort == 1. A ce moment-l�, on le d�cr�mente encore -> il vaut 0 et on r�initialise
    le jeu avec notre bonne vieille fonction d'initialisation */
    if(player.timerMort > 0)
    {
        player.timerMort--;
        if(player.timerMort == 0)
        {
            changeLevel();
            initializePlayer(0);
        }
    }

}



void centerScrollingOnPlayer(void)
{
    /* Nouveau scrolling � sous-bo�te limite :
    Pour �viter les effets de saccades dus � une cam�ra qui se centre
    automatiquement et constamment
    sur le joueur, on cr�e
    une "bo�te" imaginaire autour du joueur.
    Quand on d�passe un de ses bords (en haut, en bas, � gauche ou �
    droite), on scrolle.
    Mais l� encore, au lieu de centrer sur le joueur, on d�place
    simplement la cam�ra jusqu'� arriver au joueur.
    On a choisi la valeur de 3 pixels pour pouvoir avoir le plaisir
    d'aller plus vite que le cameraman
    On acc�l�re aussi la vitesse de la cam�ra
    en cas de chute rapide (pour ne pas
    perdre le joueur de vue non plus. */

    int cxperso = player.x + player.w / 2;
    int cyperso = player.y + player.h / 2;
    int xlimmin = getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;

    /* Effet de retour en arri�re quand on est mort :
    Si on est tr�s loin de la cam�ra, plus loin que le bord
    de la map, on acc�l�re le scrolling : */
    if(cxperso < getStartX()) setStartX(getStartX() - 30);

    /* Si on d�passe par la gauche, on recule la cam�ra de 3 pixels (vous
    pouvez modifier cette valeur) */
    if(cxperso < xlimmin) setStartX(getStartX() - 3);

    /* Effet de retour en avant quand on est mort (au
    cas o� le joueur s'amuse � faire le niveau � rebours
    apr�s une checkpoint) :
    Si on est tr�s loin de la cam�ra, plus loin que le bord
    de la map, on acc�l�re le scrolling : */
    if(cxperso > getStartX() + SCREEN_WIDTH) setStartX(getStartX() + 30);

    /* Si on d�passe par la droite, on avance la cam�ra de 3 pixels (vous
    pouvez modifier cette valeur) */
    if(cxperso > xlimmax) setStartX(getStartX() + 3);

    /*Si on arrive au bout de la map � gauche, on stoppe le scrolling */
    if(getStartX() < 0) setStartX(0);

    /* Si on arrive au bout de la map � droite, on stoppe le scrolling � la
    valeur Max de la map - la moiti� d'un �cran (pour ne pas afficher du noir). */
    else if(getStartX() + SCREEN_WIDTH >= getMaxX())
        setStartX(getMaxX() - SCREEN_WIDTH);

    /* Si on d�passe par le haut, on remonte la cam�ra de 3 pixels (vous
    pouvez modifier cette valeur) */
    if(cyperso < ylimmin) setStartY(getStartY() - 3);

    /* Si on d�passe par le bas, on descend la cam�ra de 3 pixels (vous
    pouvez modifier cette valeur) */
    if(cyperso > ylimmax) setStartY(getStartY() + 3);

    /*Si on arrive au bout de la map en haut, on stoppe le scrolling */
    if (getStartY() < 0) setStartY(0);

    /*Si on arrive au bout de la map en bas, on stoppe le scrolling � la
    valeur Max de la map - la moiti� d'un �cran (pour ne pas afficher du noir). */
    else if (getStartY() + SCREEN_HEIGHT >= getMaxY())
        setStartY(getMaxY() - SCREEN_HEIGHT);

}



void walkFrameTimer(void)
{
    if(player.frameTimer <= 0)
    {
        /* On le r�initialise */
        player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

        /*Et on incr�mente notre variable qui compte les frames de 1 pour passer
        � la suivante */
        player.frameNumber++;

        /* Mais si on d�passe la frame max, il faut revenir � la premi�re : */
        if(player.frameNumber >= player.frameMax) player.frameNumber = 0;
    }
    /* Sinon, on d�cr�mente notre timer */
    else player.frameTimer--;

}



void attackFrameTimer(void)
{
    if(player.frameTimer <= 0)
    {
        player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER_ATTACK;
        player.frameNumber++;

        if(player.frameNumber >= player.frameMax) player.etat = player.saveEtat;
    }
    else player.frameTimer--;

}



void entityTouch(void)
{
    if(player.timerTouch <= 0)
    {
        player.timerTouch = 20;
        player.touche = 0;

    }
    else player.timerTouch--;

}
