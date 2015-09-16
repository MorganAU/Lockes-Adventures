#include "prototypes.h"



/* Sound Fx */
Mix_Chunk *bumper_sound, *destroy_sound, *oneHandSword_sound, *star_sound;

/* Musique */
Mix_Music *musique;


void loadSong(char filename[200])
{
    /* On libère la chanson précédente s'il y en a une */
    if(musique != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(musique);
    }

    /* On charge la nouvelle chanson */
    musique = Mix_LoadMUS(filename);

    if(musique == NULL)
    {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    /* On active la répétition de la musique à l'infini */
    if(Mix_PlayMusic(musique, -1) == -1)
    {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
    }

}



void cleanUpMusic(void)
{
    /* On libère la musique */
    if(musique != NULL) Mix_FreeMusic(musique);

}



void loadSound(void)
{
    bumper_sound = Mix_LoadWAV("ressources/sounds/bumper.wav");
    if(bumper_sound == NULL)
    {
        fprintf(stderr, "Can't read the bumper sound Fx \n");
        exit(EXIT_FAILURE);
    }

    destroy_sound = Mix_LoadWAV("ressources/sounds/destroy.wav");
    if(destroy_sound == NULL)
    {
        fprintf(stderr, "Can't read the destroy sound Fx \n");
        exit(EXIT_FAILURE);
    }

    oneHandSword_sound = Mix_LoadWAV("ressources/sounds/oneHandSword.wav");
    if(oneHandSword_sound == NULL)
    {
        fprintf(stderr, "Can't read the oneHandSword sound Fx \n");
        exit(EXIT_FAILURE);
    }

    star_sound = Mix_LoadWAV("ressources/sounds/star.wav");
    if(star_sound == NULL)
    {
        fprintf(stderr, "Can't read the star sound Fx \n");
        exit(EXIT_FAILURE);
    }

}



void freeSound(void)
{
    Mix_FreeChunk(bumper_sound);
    Mix_FreeChunk(destroy_sound);
    Mix_FreeChunk(oneHandSword_sound);
    Mix_FreeChunk(star_sound);

}



void playSoundFx(int type)
{
    switch(type)
    {
    case BUMPER:
        Mix_PlayChannel(-1, bumper_sound, 0);
        break;

    case DESTROY:
        Mix_PlayChannel(-1, destroy_sound, 0);
        break;

    case ONEHANDSWORD:
        Mix_PlayChannel(-1, oneHandSword_sound, 0);
        break;

    case STAR:
        Mix_PlayChannel(-1, star_sound, 0);
        break;
    }

}
