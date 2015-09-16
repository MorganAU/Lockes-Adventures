#include "prototypes.h"

SDL_Window *screen;
SDL_Renderer *renderer;


SDL_Renderer *getRenderer(void)
{
    return renderer;

}



void init(char *title)
{
    /* On crée la fenêtre, représentée par le pointeur jeu.window en utilisant la largeur et la
    hauteur définies dans les defines (defs.h).
    Nouveautés SDL2 : on peut centrer la fenêtre avec SDL_WINDOWPOS_CENTERED, et choisir la taille
    de la fenêtre, pour que la carte graphique l'agrandisse automatiquement. Notez aussi qu'on peut
    maintenant créer plusieurs fenêtres. */

    screen = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    /* On crée un renderer pour la SDL et on active la synchro verticale : VSYNC */
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);

    /* Si on n'y arrive pas, on quitte en enregistrant l'erreur dans stdout.txt */
    if(screen == NULL || renderer == NULL)
    {
        printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Initialisation du chargement des images png avec SDL_Image 2 */
    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image n'a pu être initialisée! SDL_image Error: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    /* On cache le curseur de la souris */
    SDL_ShowCursor(SDL_DISABLE);

    /* On initialise SDL_ttf 2 qui gérera l'écriture de texte */
    if(TTF_Init() < 0)
    {
        printf("Impossible d'initialisée SDL TTF: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    /* Chargement de la police */
    loadFont("ressources/font/GenBasB.ttf", 16);

    /* On initialise SDL_Mixer 2, qui gérera la musique et les effets sonores */
    int flags = MIX_INIT_FLAG;
    int initted = Mix_Init(flags);

    if((initted & flags) != flags)
    {
        printf("Mix_Init: Failed to init SDL_Mixer\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    /* Définit le nombre de pistes audio (channels) à mixer */
    Mix_AllocateChannels(32);

    /* Initialise le sous-système de la SDL gérant les joysticks */
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    /* On cherche si il y a des joysticks */
    if(SDL_NumJoysticks() > 0) openJoystick();

}



void cleanup()
{
    /* Nettoie les sprites de la map */
    cleanMaps();

    /* Libère le sprite du héros */
    cleanPlayer();

    /* Libère le sprite des monstres */
    cleanMonsters();

    /* Libère le HUD */
    cleanHUD();

    /* Ferme la prise en charge du joystick */
    closeJoystick();

    /* On libère la musique */
    cleanUpMusic();

    /* On libère les sons */
    freeSound();

    /* On quitte SDL_Mixer 2 et on décharge la mémoire */
    Mix_CloseAudio();
    Mix_Quit();

    /* On fait le ménage et on remet les pointeurs à NULL */
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(screen);
    screen = NULL;

    /* On quitte SDL_TTF 2 */
    TTF_Quit();

    /* On quitte la SDL */
    SDL_Quit();

}



void loadGame(void)
{
    /* On charge les données pour la map */
    initMaps();

    /* On charge la feuille de sprites du monstre */
    initMonsterSprites();

    /* On charge le spritesheet de notre héros */
    initPlayerSprites();

    /* On commence au premier niveau */
    setLevelNumber(1);
    changeLevel();

    /* On initialise les variables du jeu */
    setLifeNumber(3);
    setStarNumber(0);

    /* On charge le HUD */
    initHUD();

    /* on charge la musique */
    loadSong(TAVERNE_SONG);

    /* On charge les sounds Fx */
    loadSound();

}
