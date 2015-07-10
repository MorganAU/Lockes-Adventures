#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "defs.h"

/* Structures qui seront utilisées pour gérer le jeu */

/* Structure pour gérer l'input */
typedef struct Input
{
    int left, right, up, down, useItem, attack, enter, erase, pause;
    int pressed;
    int input1, input2;

} Input;



/* Structure pour gérer la map */
typedef struct Map
{
    SDL_Texture *background;
    SDL_Texture *tileSet, *tileSetB;

    /* Numéro du tileset à utiliser */
    int tilesetAffiche;

    /* Coordonnées de départ du héros, lorsqu'il commence le niveau */
    int beginx, beginy;

    /* Coordonnées de début, lorsqu'on doit dessiner la map */
    int startX, startY;

    /* Coordonnées max de fin de la map */
    int maxX, maxY;

    /* Tableau à double dimension représentant la map de tiles */
    int tile[MAX_MAP_Y][MAX_MAP_X];

    /* Deuxième couche de tiles */
    int tile2[MAX_MAP_Y][MAX_MAP_X];

    /* Troisième couche de tiles */
    int tile3[MAX_MAP_Y][MAX_MAP_X];

    /* Timer et numéro du tileset à afficher pour animer la map */
    int mapTimer, tileSetNumber;

} Map;



/* Structure pour gérer nos sprites */
typedef struct GameObject
{
    /* Points de vie/santé + chrono d'invincibilité */
    int life, lifeMax, invincibleTimer;

    int name, borned;

    /* Coordonnées du sprite */
    int x, y;

    /* Largeur, hauteur du sprite */
    int h, w;

    /* Largeur, hauteur du sprite quand le héros attaque */
    int wAttack, hAttack;

    /* Checkpoint pour le héros (actif ou non) */
    int checkpointActif;

    /* Coordonnées de respawn */
    int respawnX, respawnY;

    /* Attaque */
    int attack, timerAttack, canSwordAttack, estEnTrainDAttaquer, touche;
    float power;


    /* Variables utiles pour l'animation :
        Numéro de la frame en cours + timer */
        int frameNumber, frameTimer, frameMax;

        /* Nombre max de frames, état du sprite et direction
        dans laquelle il se déplace */
        int etat, direction;
        float directionAleatoire;
        int saveEtat, saveDirection;


    /*Variables utiles pour la gestion des collisions :
        Chrono une fois mort */
        int timerMort;
        int timerDirection;
        int timerTouch;
        int timerRandDir;

        /* Vecteurs de déplacement temporaires avant détection
        des collisions avec la map */
        float dirX, dirY;

        /* Sauvegarde des coordonnées de départ */
        int saveX, saveY;

} GameObject;



#endif // STRUCTS_H_INCLUDED
