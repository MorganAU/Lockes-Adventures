#include "prototypes.h"


/* D�claration de notre police de caract�res */
TTF_Font *font;


void loadFont(char *name, int size)
{
    /* On utilise SDL_TTF pour charger la police � la taille sp�cifi�e par size */
    font = TTF_OpenFont(name, size);

    if(font == NULL)
    {
        printf("Failed to open Font %s: %s\n", name, TTF_GetError());
        exit(EXIT_FAILURE);
    }

}



void closeFont()
{
    /* On ferme la police (font) */
    if(font != NULL) TTF_CloseFont(font);

}



void drawString(char *text, int x, int y, int r, int g, int b, int a)
{
    SDL_Rect dest, destOption;
    SDL_Surface *surface, *surfaceOption; /* Pour �crire le texte */
    SDL_Texture *texture, *textureOption; /* Pour convertir la surface en texture */
    SDL_Color foregroundColor, foregroundColorOption;


    /* Couleur du texte RGBA */
    foregroundColor.r = r;
    foregroundColor.g = g;
    foregroundColor.b = b;
    foregroundColor.a = a;

    foregroundColorOption.r = 255;
    foregroundColorOption.g = 255;
    foregroundColorOption.b = 255;
    foregroundColorOption.a = 255;


    /* On utilise SDL_TTF pour g�n�rer une SDL_Surface � partir d'une cha�ne de caract�res (string) */
    surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);
    surfaceOption = TTF_RenderUTF8_Blended(font, text, foregroundColorOption);

    if(surface != NULL || surfaceOption == NULL)
    {

        /* Conversion de l'image en texture */
        texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
        textureOption = SDL_CreateTextureFromSurface(getRenderer(), surfaceOption);

        /* On se d�barrasse du pointeur vers une surface et on lib�re la SDL_Surface temporaire */
        SDL_FreeSurface(surface);
        surface = NULL;
        SDL_FreeSurface(surfaceOption);
        surfaceOption = NULL;

        /* On dessine cette texture � l'�cran */
        dest.x = x;
        dest.y = y;

        destOption.x = x + 1;
        destOption.y = y + 1;

        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(getRenderer(), texture, NULL, &dest);

        SDL_QueryTexture(textureOption, NULL, NULL, &destOption.w, &destOption.h);
        SDL_RenderCopy(getRenderer(), textureOption, NULL, &destOption);

        /* On supprime la texture */
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(textureOption);
    }
    else
    {
        printf("La cha�ne n'a pas pu �tre �crite %s: %s\n", text, TTF_GetError());
        exit(EXIT_FAILURE);
    }

}
