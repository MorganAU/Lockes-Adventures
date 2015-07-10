#include "prototypes.h"

SDL_Window *screen;
SDL_Renderer *renderer;


SDL_Renderer *getRenderer(void)
{
    return renderer;

}



void init(char *title)
{
    /* On cr�e la fen�tre, repr�sent�e par le pointeur jeu.window en utilisant la largeur et la
    hauteur d�finies dans les defines (defs.h).
    Nouveaut�s SDL2 : on peut centrer la fen�tre avec SDL_WINDOWPOS_CENTERED, et choisir la taille
    de la fen�tre, pour que la carte graphique l'agrandisse automatiquement. Notez aussi qu'on peut
    maintenant cr�er plusieurs fen�tres. */

    screen = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    /* On cr�e un renderer pour la SDL et on active la synchro verticale : VSYNC */
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);

    /* Si on n'y arrive pas, on quitte en enregistrant l'erreur dans stdout.txt */
    if(screen == NULL || renderer == NULL)
    {
        printf("Impossible d'initialiser le mode �cran � %d x %d: %s\n", SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Initialisation du chargement des images png avec SDL_Image 2 */
    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image n'a pu �tre initialis�e! SDL_image Error: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    /* On cache le curseur de la souris */
    SDL_ShowCursor(SDL_DISABLE);

    /* On initialise SDL_ttf 2 qui g�rera l'�criture de texte */
    if(TTF_Init() < 0)
    {
        printf("Impossible d'initialis�e SDL TTF: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    /* Chargement de la police */
    loadFont("ressources/font/GenBasB.ttf", 16);

    /* On initialise SDL_Mixer 2, qui g�rera la musique et les effets sonores */
    int flags = MIX_INIT_MP3;
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

    /* D�finit le nombre de pistes audio (channels) � mixer */
    Mix_AllocateChannels(32);

    /* Initialise le sous-syst�me de la SDL g�rant les joysticks */
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    /* On cherche si il y a des joysticks */
    if(SDL_NumJoysticks() > 0) openJoystick();

}



void cleanup()
{
    /* Nettoie les sprites de la map */
    cleanMaps();

    /* Lib�re le sprite du h�ros */
    cleanPlayer();

    /* Lib�re le sprite des monstres */
    cleanMonsters();

    /* Lib�re le HUD */
    cleanHUD();

    /* Ferme la prise en charge du joystick */
    closeJoystick();

    /* On lib�re la musique */
    cleanUpMusic();

    /* On lib�re les sons */
    freeSound();

    /* On quitte SDL_Mixer 2 et on d�charge la m�moire */
    Mix_CloseAudio();
    Mix_Quit();

    /* On fait le m�nage et on remet les pointeurs � NULL */
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
    /* On charge les donn�es pour la map */
    initMaps();

    /* On charge la feuille de sprites du monstre */
    initMonsterSprites();

    /* On charge le spritesheet de notre h�ros */
    initPlayerSprites();

    /* On commence au premier niveau */
    setValeurDuNiveau(1);
    changeLevel();

    /* On initialise les variables du jeu */
    setNombreDeVies(3);
    setNombreDetoiles(0);

    /* On charge le HUD */
    initHUD();

    /* on charge la musique */
    loadSong("ressources/music/tavern.mp3");

    /* On charge les sounds Fx */
    loadSound();

}
