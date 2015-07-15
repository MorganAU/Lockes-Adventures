#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <time.h>

/* On inclut les libs supplémentaires */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

/* Taille de la fenêtre */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

/* Taille maxi de la map */
#define MAX_MAP_X 400
#define MAX_MAP_Y 150

/* Taille d'une tile */
#define TILE_SIZE 32

/* Constante pour l'animation */
#define TIME_BETWEEN_2_FRAMES 20
#define TIME_BETWEEN_2_FRAMES_PLAYER 4
#define TIME_BETWEEN_2_FRAMES_PLAYER_ATTACK 3

/* Taille du sprite de notre héros */
#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 46

/* Taille du sprite de l'épée */
#define SWORD_WIDTH_HORIZONTAL 17
#define SWORD_HEIGHT_HORIZONTAL 19

#define SWORD_WIDTH_DOWN 15
#define SWORD_HEIGHT_DOWN 17

#define SWORD_WIDTH_UP 9
#define SWORD_HEIGHT_UP 10

/* Vitesse de déplacement en pixel du sprite */
#define PLAYER_SPEED 3
#define PLAYER_HURT 2

/* Valeurs attribuées aux états/directions */
#define IDLE_HORIZONTAL 0
#define WALK_HORIZONTAL 1
#define IDLE_UP 2
#define WALK_UP 3
#define IDLE_DOWN 4
#define WALK_DOWN 5
#define DEAD 55
#define ATTACK_HORIZONTAL 6
#define ATTACK_DOWN 7
#define ATTACK_UP 8
#define BORN 9

#define IDLE 0
#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

/* Position des armes */
#define SWORD 9



/* Constantes pour les limites de la caméra avant scrolling */
#define LIMITE_X 400
#define LIMITE_Y 220
#define LIMITE_W 100
#define LIMITE_H 80

/* Constante définissant le seuil entre les tiles traversables
(blank) et les tiles solides */
#define BLANK_TILE 7

/* Tiles des monstres */
#define TILE_MONSTER 19
#define TILE_MONSTER2 12

/* Monstres */
#define BLAGULE 12
#define MASTER_BLAGULE 19

/* Constantes pour la gestion des doubles directions */
#define INPUT_LEFT 1
#define INPUT_RIGHT 2
#define INPUT_UP 3
#define INPUT_DOWN 4
#define NONE 0

/* Dead zone de la manette pour éviter les mouvements involontaires */
#define DEAD_ZONE 8000

/* Mapping de la manette */
#define BOUTON_HAUT 13
#define BOUTON_DROITE 14
#define BOUTON_BAS 15
#define BOUTON_GAUCHE 16

#define BOUTON_ITEM 4
#define BOUTON_ATTAQUE 2
#define BOUTON_PAUSE 10
#define BOUTON_QUIT 9

/* Nombre max de monstres à l'écran */
#define MONSTRES_MAX 50

/* Dimensions du monstre */
#define MONSTER_WIDTH 32
#define MONSTER_HEIGHT 24

/* Une enum pour la gestion des sons */
enum
{
    BUMPER, DESTROY, ONEHANDSWORD, STAR
};




#endif // DEFS_H_INCLUDED
