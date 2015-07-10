#include "prototypes.h"

/* D�claration des variables/structures utilis�es par le jeu */
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

    /* Appelle la fonction cleanup � la fin du programme */
    atexit(cleanup);

    /* Boucle infinie, principale, du jeu */
    while(go)
    {
        /* Gestion des inputs clavier */
        gestionInputs(&input);

        /* on met � jour le jeu, en commen�ant par le joueur */
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
