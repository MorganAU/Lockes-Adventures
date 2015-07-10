#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "defs.h"

/* Structures qui seront utilis�es pour g�rer le jeu */

/* Structure pour g�rer l'input */
typedef struct Input
{
    int left, right, up, down, useItem, attack, enter, erase, pause;
    int pressed;
    int input1, input2;

} Input;



/* Structure pour g�rer la map */
typedef struct Map
{
    SDL_Texture *background;
    SDL_Texture *tileSet, *tileSetB;

    /* Num�ro du tileset � utiliser */
    int tilesetAffiche;

    /* Coordonn�es de d�part du h�ros, lorsqu'il commence le niveau */
    int beginx, beginy;

    /* Coordonn�es de d�but, lorsqu'on doit dessiner la map */
    int startX, startY;

    /* Coordonn�es max de fin de la map */
    int maxX, maxY;

    /* Tableau � double dimension repr�sentant la map de tiles */
    int tile[MAX_MAP_Y][MAX_MAP_X];

    /* Deuxi�me couche de tiles */
    int tile2[MAX_MAP_Y][MAX_MAP_X];

    /* Troisi�me couche de tiles */
    int tile3[MAX_MAP_Y][MAX_MAP_X];

    /* Timer et num�ro du tileset � afficher pour animer la map */
    int mapTimer, tileSetNumber;

} Map;



/* Structure pour g�rer nos sprites */
typedef struct GameObject
{
    /* Points de vie/sant� + chrono d'invincibilit� */
    int life, lifeMax, invincibleTimer;

    int name, borned;

    /* Coordonn�es du sprite */
    int x, y;

    /* Largeur, hauteur du sprite */
    int h, w;

    /* Largeur, hauteur du sprite quand le h�ros attaque */
    int wAttack, hAttack;

    /* Checkpoint pour le h�ros (actif ou non) */
    int checkpointActif;

    /* Coordonn�es de respawn */
    int respawnX, respawnY;

    /* Attaque */
    int attack, timerAttack, canSwordAttack, estEnTrainDAttaquer, touche;
    float power;


    /* Variables utiles pour l'animation :
        Num�ro de la frame en cours + timer */
        int frameNumber, frameTimer, frameMax;

        /* Nombre max de frames, �tat du sprite et direction
        dans laquelle il se d�place */
        int etat, direction;
        float directionAleatoire;
        int saveEtat, saveDirection;


    /*Variables utiles pour la gestion des collisions :
        Chrono une fois mort */
        int timerMort;
        int timerDirection;
        int timerTouch;
        int timerRandDir;

        /* Vecteurs de d�placement temporaires avant d�tection
        des collisions avec la map */
        float dirX, dirY;

        /* Sauvegarde des coordonn�es de d�part */
        int saveX, saveY;

} GameObject;



#endif // STRUCTS_H_INCLUDED
