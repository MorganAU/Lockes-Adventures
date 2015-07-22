#include "prototypes.h"


/* HUD */
SDL_Texture *tilesetHUD, *HUD_etoiles;
int one;


void drawGame(void)
{
    /* Affiche le background aux coordonn�es (0,0) */
    drawImage(getBackground(), 0, 0);

    /* Affiche la map de tiles : layer 2 (couche du fond) */
    drawMap(2);

    /* Affiche la map de tiles : layer 1 (couche active : sol, etc.)*/
    drawMap(1);

    /* Affiche le joueur et son attaque */
    drawPlayer();
    drawOnehand();

    /* Affiche les monstres */
    for(int i  = 0 ; i < getMonsterNumber() ; i++)
        drawMonster(getMonster(i));

    /* Affiche la map de tiles : layer 3 (couche en foreground / devant) */
    drawMap(3);

    /* On affiche le HUD par-dessus tout le reste */
    drawHUD();

    /* Affiche l'�cran */
    SDL_RenderPresent(getRenderer());

    /* D�lai pour laisser respirer le processeur */
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

        /* On se d�barrasse du pointeur vers une surface */
        SDL_FreeSurface(loadedImage);
        loadedImage = NULL;
    }
    else printf("L'image n'a pas pu �tre charg�e! SDL_Error : %s\n", SDL_GetError());

    return texture;

}



void drawImage(SDL_Texture *image, int x, int y)
{
    SDL_Rect dest;

    /* R�gle le rectangle � dessiner selon la taille de l'image source */
    dest.x = x;
    dest.y = y;

    /* Dessine l'image enti�re sur l'�cran aux coordonn�es x et y */
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
    /* Rectangle de destination � dessiner */
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

    /* Dessine la tile choisie sur l'�cran aux coordonn�es x et y */
    SDL_RenderCopy(getRenderer(), image, &src, &dest);

}



void initHUD(void)
{
    /* On charge les images du HUD */
    tilesetHUD = loadImage("ressources/graphics/tileset_hud.png");
    HUD_etoiles = loadImage("ressources/graphics/stars.png");

}



void cleanHUD(void)
{
    if(HUD_etoiles != NULL) SDL_DestroyTexture(HUD_etoiles);
    if(tilesetHUD != NULL) SDL_DestroyTexture(tilesetHUD);

}



void drawHUD(void)
{
    /* On cr�e une variable qui contiendra notre texte (moins de 200 caract�res) */

    drawLifePlayer();
    drawCoinPlayer();



    /* Puis on utilise notre fonction cr��e pr�c�demment pour �crire en noir (0, 0, 0, 255)
    et en blanc (255, 255, 255, 255) afin de surligner le texte et le rendre plus visible */


    /* Affiche le nombre d'�toiles en haut � gauche
    drawImage(HUD_etoiles, 60, 60);

    sprintf(text, "%d", getNombreDetoiles());
    drawString(text, 100, 57, 0, 0, 0, 255); */


}



void drawLifePlayer(void)
{
    /* Affiche le nombre de coeurs, on cr�e une boucle pour afficher de 1 � 3 c�urs selon la vie, avec un d�calage de 32 px */
    int ysource = 0;
    int xsource = 0;
    int ydest = 20;
    int xdest = 30;
    float ratioMax = (float)getLifeMax() * 100 / 58;
    float ratio = getLife() / ratioMax * 100;
    float coeff = 2;

    if(ratio > 58) ratio = 58;

    drawTileHUD(tilesetHUD, xdest, ydest, xsource, ysource, 64, 10, coeff);

    for(int i = 0 ; i < ratio ; i++)
        drawTileHUD(tilesetHUD, xdest + 3 * coeff + i * coeff, ydest + 3 * coeff, 3, 3, 1, 3, coeff);

}



void drawCoinPlayer(void)
{
    char text[200];
    GameObject *player = getPlayer();

    /* Affiche le nombre de vies en bas � droite - Adaptation � la fen�tre auto */
    drawTileHUD(tilesetHUD, SCREEN_WIDTH - 115, SCREEN_HEIGHT - 55, 64, 0, 10, 10, 2);

    /* Pour afficher le nombre de vies, on formate notre string pour qu'il la valeur de la variable */
    sprintf(text, " %d", 1000);

    drawString(text, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 54, 0, 0, 0, 255);

    /* Lignes suivantes permettent d'afficher diverses informations en fonction du besoin sans utiliser fprintf() */
    /*sprintf(text, "%d", getLife());
    drawString(text, 10, SCREEN_HEIGHT - 70, 255, 0, 0, 255);
    sprintf(text, "timer = %d", player->life);
    drawString(text, 10, SCREEN_HEIGHT - 55, 255, 0, 0, 255);
    sprintf(text, "input2 = %d", input->input2);
    drawString(text, 10, SCREEN_HEIGHT - 40, 255, 0, 0, 255);*/

}



void drawTileHUD(SDL_Texture *image, int destx, int desty, int srcx, int srcy, int w, int h, float coeff)
{
    /* Rectangle de destination � dessiner */
    SDL_Rect dest;

    dest.x = destx;
    dest.y = desty;
    dest.w = w * coeff;
    dest.h = h * coeff;

    /* Rectangle source */
    SDL_Rect src;

    src.x = srcx;
    src.y = srcy;
    src.w = w;
    src.h = h;

    /* Dessine la tile choisie sur l'�cran aux coordonn�es x et y */
    SDL_RenderCopy(getRenderer(), image, &src, &dest);

}
