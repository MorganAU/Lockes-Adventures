#include "prototypes.h"


/* HUD */
SDL_Texture *HUD_vie, *HUD_etoiles;
int one;


void drawGame(void)
{
    /* Affiche le background aux coordonnées (0,0) */
    drawImage(getBackground(), 0, 0);

    /* Affiche la map de tiles : layer 2 (couche du fond) */
    drawMap(2);

    /* Affiche la map de tiles : layer 1 (couche active : sol, etc.)*/
    drawMap(1);

     /* Affiche le joueur et son attaque */
    drawPlayer();
    drawOnehand();

    /* Affiche les monstres */
    for(int i  = 0 ; i < getMonsterNumber() ; i++) drawMonster(getMonster(i));

    /* Affiche la map de tiles : layer 3 (couche en foreground / devant) */
    drawMap(3);

    /* On affiche le HUD par-dessus tout le reste */
    drawHUD();

    /* Affiche l'écran */
    SDL_RenderPresent(getRenderer());

    /* Délai pour laisser respirer le processeur */
    SDL_Delay(1);

}



SDL_Texture *loadImage(char *name)
{
    /* Charge les images avec SDL Image dans une SDL_Surface */
    SDL_Surface *loadedImage = IMG_Load(name);
    SDL_Texture *texture = NULL;

    if(loadedImage != NULL)
    {
        /* Conversion de l'image en texture */
        texture = SDL_CreateTextureFromSurface(getRenderer(), loadedImage);

        /* On se débarrasse du pointeur vers une surface */
        SDL_FreeSurface(loadedImage);
        loadedImage = NULL;
    }
    else printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());

    return texture;

}



void drawImage(SDL_Texture *image, int x, int y)
{
    SDL_Rect dest;

    /* Règle le rectangle à dessiner selon la taille de l'image source */
    dest.x = x;
    dest.y = y;

    /* Dessine l'image entière sur l'écran aux coordonnées x et y */
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(getRenderer(), image, NULL, &dest);

}



void delay(unsigned int frameLimit)
{
    /* Gestion des 60 fps */
    unsigned int ticks = SDL_GetTicks();

    if(frameLimit < ticks) return;

    if(frameLimit > ticks + 16) SDL_Delay(16);
    else SDL_Delay(frameLimit - ticks);

}



void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy)
{
    /* Rectangle de destination à dessiner */
    SDL_Rect dest;

    dest.x = destx;
    dest.y = desty;
    dest.w = TILE_SIZE;
    dest.h = TILE_SIZE;

    /* Rectangle source */
    SDL_Rect src;

    src.x = srcx;
    src.y = srcy;
    src.w = TILE_SIZE;
    src.h = TILE_SIZE;

    /* Dessine la tile choisie sur l'écran aux coordonnées x et y */
    SDL_RenderCopy(getRenderer(), image, &src, &dest);

}



void initHUD(void)
{
    /* On charge les images du HUD */
    HUD_vie = loadImage("ressources/graphics/life.png");
    HUD_etoiles = loadImage("ressources/graphics/stars.png");

}



void cleanHUD(void)
{
    if(HUD_etoiles != NULL) SDL_DestroyTexture(HUD_etoiles);
    if(HUD_vie != NULL) SDL_DestroyTexture(HUD_vie);

}



void drawHUD(void)
{
    /* On crée une variable qui contiendra notre texte (moins de 200 caractères) */

    drawLife();
    drawCoinPlayer();



    /* Puis on utilise notre fonction créée précédemment pour écrire en noir (0, 0, 0, 255)
    et en blanc (255, 255, 255, 255) afin de surligner le texte et le rendre plus visible */


    /* Affiche le nombre d'étoiles en haut à gauche
    drawImage(HUD_etoiles, 60, 60);

    sprintf(text, "%d", getNombreDetoiles());
    drawString(text, 100, 57, 0, 0, 0, 255); */


}



void drawLife(void)
{
    int boucle = getLife() / 4;
    int reste = getLife() % 4;

    drawLifeMax();

    /* Affiche le nombre de coeurs, on crée une boucle pour afficher de 1 à 3 cœurs selon la vie, avec un décalage de 32 px */
    for(int i = 0 ; i <= getLife() / 4 ; i++)
    {
        int ysource = 12 / 10 * TILE_SIZE;
        int xsource;
        int ydest, xdest;

        if(i < 10) ydest = 20;
        else ydest = 35;

        if(i < 10) xdest = 30 + i * 16;
        else xdest = 30 + (i - 10) * 16;

        if(boucle > 0)
        {
            boucle--;
            xsource = 13 % 10 * TILE_SIZE;

            /* Calcul pour découper le tileset comme dans la fonction drawMap() */
            drawTile(getTileSetA(), xdest, ydest, xsource, ysource);
        }
        else if(reste != 0)
        {
            xsource = (13 + reste) % 10 * TILE_SIZE;
            drawTile(getTileSetA(), xdest, ydest, xsource, ysource);
        }
    }

}



void drawLifeMax(void)
{
    for(int i = 0 ; i < getLifeMax() / 4 ; i++)
    {
        int ysource = 12 /10 * TILE_SIZE;
        int xsource = 17 % 10 * TILE_SIZE;
        int ydest, xdest;

        if(i < 10) ydest = 20;
        else ydest = 35;

        if(i < 10) xdest = 30 + i * 16;
        else xdest = 30 + (i - 10) * 16;

        drawTile(getTileSetA(), xdest, ydest, xsource, ysource);
    }

}



void drawCoinPlayer(void)
{
    char text[200];
GameObject *player = getPlayer();

    /* Affiche le nombre de vies en bas à droite - Adaptation à la fenêtre auto */
    drawTile(getTileSetA(), SCREEN_WIDTH - 120, SCREEN_HEIGHT - 60, 18 % 10 * TILE_SIZE, 12 /10 * TILE_SIZE);

    /* Pour afficher le nombre de vies, on formate notre string pour qu'il la valeur de la variable */
    sprintf(text, " %d", 1000);

    drawString(text, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 54, 0, 0, 0, 255);

    sprintf(text, "%d", getLife());
    drawString(text, 10, SCREEN_HEIGHT - 70, 255, 0, 0, 255);
        sprintf(text, "timer = %d", player->life);
    drawString(text, 10, SCREEN_HEIGHT - 55, 255, 0, 0, 255);
   /* sprintf(text, "input2 = %d", input->input2);
    drawString(text, 10, SCREEN_HEIGHT - 40, 255, 0, 0, 255);*/

}
