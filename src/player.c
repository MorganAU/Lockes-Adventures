#include "prototypes.h"

int level;
int vies, etoiles;
GameObject player;
SDL_Texture *playerSpriteSheet;


/* Renvoie le GameObject player (héros) */
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



/* Renvoie les coordonnées x du héros */
int getPlayerx(void)
{
    return player.x;

}



/* Renvoie les coordonnées y du héros */
int getPlayery(void)
{
    return player.y;

}



/* Change la valeur des coordonnées x du héros */
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



/* Change la valeur des coordonnées y du héros */
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



/* Renvoie le numéro du niveau en cours */
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



/* Charge le spritesheet de notre héros au début du jeu */
void initPlayerSprites(void)
{
    playerSpriteSheet = loadImage("ressources/graphics/sprite_hero2.png");

}



/* Libère le sprite du héros à la fin du jeu */
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
    /* On met le timer à 1 pour tuer le joueur instantanément */
    player.timerMort = 1;

    /* On joue le son */
    playSoundFx(DESTROY);

}



void playerHurts(GameObject entity)
{
    /* Si le timer d'invincibilité est à 0, on perd un coeur */
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



/* Initialise le héros */
void initializePlayer(int newLevel)
{
    /* PV à 3 */

    player.lifeMax = 12;
    player.life = 12;

    /* Timer d'invincibilité */
    player.invincibleTimer = 0;
    player.timerTouch = 20;

    /* Indique l'état et la direction de notre héros */
    player.direction = DOWN;
    player.etat = IDLE_DOWN;

    /* Indique le numéro de la frame où commencer */
    player.frameNumber = 0;

    /* ... la valeur de son chrono au timer */
    player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

    /* ... et son nombre de frame max */
    player.frameMax = 9;

    player.x = getBeginX();
    player.y = getBeginY();

    /* On réinitialise les coordonnées de la caméra si on change de niveau */
    if(newLevel == 1)
    {
        setStartX(getBeginX());
        setStartY(getBeginY());
    }

    /* Hauteur et largeur de notre héros */
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGHT;

    /* Variables nécessaires au fonctionnement de la gestion des collisions */
    player.timerMort = 0;

    /* Réinitialise les monstres */
    /* Libère le sprite des monstres */
    resetMonsters();

}



void drawPlayer(void)
{
    /* Gestion du timer */

    /* Si notre timer (un compte à rebours en fait) arrive à zéro */
    if(player.etat <= WALK_DOWN) walkFrameTimer();
    else attackFrameTimer();

    /* Ensuite, on peut passer la main à notre fonction */

    /* Rectangle de destination à dessiner */
    SDL_Rect dest;

    /* On soustrait des coordonnées de notre héros, ceux du début de la map,
    pour qu'il colle au scrolling : */
    dest.x = player.x - getStartX();
    dest.y = player.y - getStartY();
    dest.w = player.w;
    dest.h = player.h;

    /* Rectangle source */
    SDL_Rect src;

    /* Pour connaître le X de la bonne frame à dessiner, il suffit de multiplier
    la largeur du sprite par le numéro de la frame à afficher -> 0 = 0; 1 = 40; 2 = 80... */

    src.x = player.frameNumber * player.w;
    src.w = player.w;
    src.h = player.h;

    /* On calcule le Y de la bonne frame à dessiner, selon la valeur de l'état du héros :
    Aucun mouvement (Idle) = 0, marche (walk) = 1, etc...
    Tout cela en accord avec notre spritesheet, of course ;) */

    src.y = player.etat * player.h;

    /* Si on a été touché, et qu'on est invincible */
    int q;

    if(player.invincibleTimer > 0) q = 2;
    else q = 1;

    /* On fait clignoter le héros une frame sur deux; Pour ça, on calcule
    si le numéro de la frame est un multiple de deux */
    if(player.frameNumber % q == 0)
    {
        /* Gestion du flip (retournement de l'image selon que le sprite regarde à droite ou
        à gauche */
        const SDL_RendererFlip flip =
            player.direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        SDL_RenderCopyEx(getRenderer(), playerSpriteSheet, &src, &dest, 0, 0, flip);
    }

}



void updatePlayer(Input *input)
{
    /* On rajoute un timer au cas où notre héros mourrait
    Si le timer vaut 0, c'est que tout va bien, sinon, on le décrémente jusqu'à 0, et là,
    on réinitialise.
    C'est pour ça qu'on ne gère le joueur que si ce timer vaut 0. */
    if(player.timerMort == 0)
    {
        if(!player.touche) // S'il n'est pas touché
        {
            /* On gère le timer de l'invincibilité */
            if(player.invincibleTimer > 0) player.invincibleTimer--;

            /* On réinitialise notre vecteur de déplacement latéral (X), pour éviter que le perso
            ne fonce de plus en plus */
            player.dirX = player.dirY = player.estEnTrainDAttaquer = 0;

            gestionAttaque(input, &player);

            if(player.etat < ATTACK_HORIZONTAL && input->pressed < 3) playerDirection(input, &player);

            /* Si on n'appuie sur rien, on charge l'animation marquant l'inactivité (Idle), je n'ai pas regarder encore si je pouvais l'optimiser */
            playerIdle(input, &player);

            resetInput(input);
        }
        /* Sinon si il est touché */
        else if(player.touche) entityTouch();

        /* On rajoute notre fonction de détection des collisions qui va mettre à
        jour les coordonnées de notre héros. */
        mapCollision(&player);

        /* On gère le scrolling */
        centerScrollingOnPlayer();
    }



    /*Gestion de la mort. Si timerMort est différent de 0, c'est qu'il faut réinitialiser le joueur.
    On ignore alors ce qui précède et on joue cette boucle (un wait en fait) jusqu'à ce que
    timerMort == 1. A ce moment-là, on le décrémente encore -> il vaut 0 et on réinitialise
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
    /* Nouveau scrolling à sous-boîte limite :
    Pour éviter les effets de saccades dus à une caméra qui se centre
    automatiquement et constamment
    sur le joueur, on crée
    une "boîte" imaginaire autour du joueur.
    Quand on dépasse un de ses bords (en haut, en bas, à gauche ou à
    droite), on scrolle.
    Mais là encore, au lieu de centrer sur le joueur, on déplace
    simplement la caméra jusqu'à arriver au joueur.
    On a choisi la valeur de 3 pixels pour pouvoir avoir le plaisir
    d'aller plus vite que le cameraman
    On accélère aussi la vitesse de la caméra
    en cas de chute rapide (pour ne pas
    perdre le joueur de vue non plus. */

    int cxperso = player.x + player.w / 2;
    int cyperso = player.y + player.h / 2;
    int xlimmin = getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;

    /* Effet de retour en arrière quand on est mort :
    Si on est très loin de la caméra, plus loin que le bord
    de la map, on accélère le scrolling : */
    if(cxperso < getStartX()) setStartX(getStartX() - 30);

    /* Si on dépasse par la gauche, on recule la caméra de 3 pixels (vous
    pouvez modifier cette valeur) */
    if(cxperso < xlimmin) setStartX(getStartX() - 3);

    /* Effet de retour en avant quand on est mort (au
    cas où le joueur s'amuse à faire le niveau à rebours
    après une checkpoint) :
    Si on est très loin de la caméra, plus loin que le bord
    de la map, on accélère le scrolling : */
    if(cxperso > getStartX() + SCREEN_WIDTH) setStartX(getStartX() + 30);

    /* Si on dépasse par la droite, on avance la caméra de 3 pixels (vous
    pouvez modifier cette valeur) */
    if(cxperso > xlimmax) setStartX(getStartX() + 3);

    /*Si on arrive au bout de la map à gauche, on stoppe le scrolling */
    if(getStartX() < 0) setStartX(0);

    /* Si on arrive au bout de la map à droite, on stoppe le scrolling à la
    valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir). */
    else if(getStartX() + SCREEN_WIDTH >= getMaxX())
        setStartX(getMaxX() - SCREEN_WIDTH);

    /* Si on dépasse par le haut, on remonte la caméra de 3 pixels (vous
    pouvez modifier cette valeur) */
    if(cyperso < ylimmin) setStartY(getStartY() - 3);

    /* Si on dépasse par le bas, on descend la caméra de 3 pixels (vous
    pouvez modifier cette valeur) */
    if(cyperso > ylimmax) setStartY(getStartY() + 3);

    /*Si on arrive au bout de la map en haut, on stoppe le scrolling */
    if (getStartY() < 0) setStartY(0);

    /*Si on arrive au bout de la map en bas, on stoppe le scrolling à la
    valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir). */
    else if (getStartY() + SCREEN_HEIGHT >= getMaxY())
        setStartY(getMaxY() - SCREEN_HEIGHT);

}



void walkFrameTimer(void)
{
    if(player.frameTimer <= 0)
    {
        /* On le réinitialise */
        player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

        /*Et on incrémente notre variable qui compte les frames de 1 pour passer
        à la suivante */
        player.frameNumber++;

        /* Mais si on dépasse la frame max, il faut revenir à la première : */
        if(player.frameNumber >= player.frameMax) player.frameNumber = 0;
    }
    /* Sinon, on décrémente notre timer */
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
