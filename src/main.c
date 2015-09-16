#include "prototypes.h"

/* Déclaration des variables/structures utilisées par le jeu */
Input input;


int main(int argc, char *argv[])
{
    unsigned int frameLimit = 16;
    int go = 1;

    /* Initialisation de la SDL */
    init("Locke's Adventures");

    /* Chargement des ressources (graphismes, sons) */
    loadGame();

    /* On initialise le joueur */
    initializePlayer(1);

    /* Appelle la fonction cleanup à la fin du programme */
    atexit(cleanup);

    /* Boucle infinie, principale, du jeu */
    while(go)
    {
        /* Gestion des inputs clavier */
        gestionInputs(&input);

        /* on met à jour le jeu, en commençant par le joueur */
        updatePlayer(&input);

        /* Puis les monstres */
        updateMonsters();

        /* On dessine tout */
        drawGame();

        /* Gestion des 60 fps (1000ms/60 = 16.6 -> 16 */
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
    }

    /* On quitte */
    exit(EXIT_SUCCESS);

}
