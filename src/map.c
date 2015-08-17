#include "prototypes.h"


/* Déclaration des variables/structures utilisées par le jeu */
Map map;


void initMaps(void)
{
    /* Charge le background */
    map.background = loadImage("ressources/graphics/background.png");

    /* On initialise le timer */
    map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;
    map.tileSetNumber = 0;

}



SDL_Texture *getBackground(void)
{
    return map.background;

}



SDL_Texture *getTileSetA(void)
{
    return map.tileSet;

}



SDL_Texture *getTileSetB(void)
{
    return map.tileSetB;

}


void cleanMaps(void)
{
    /* Libère la texture du background */
    if(map.background != NULL)
    {
        SDL_DestroyTexture(map.background);
        map.background = NULL;
    }

    /* Libère les textures des tilesets */
    if(map.tileSet != NULL)
    {
        SDL_DestroyTexture(map.tileSet);
        map.tileSet = NULL;
    }

    if(map.tileSetB != NULL)
    {
        SDL_DestroyTexture(map.tileSetB);
        map.tileSetB = NULL;
    }

}



void loadMap(char *name)
{
    int x, y;
    FILE *fp = fopen(name, "rb");

    /* Si on ne peut pas ouvrir le fichier, on quitte */
    if(fp == NULL)
    {
        printf("Failed to open map %s\n", name);
        exit(EXIT_FAILURE);
    }

    /* Lit les données du fichier dans la map */

    /* Lit les coordonnées de début du joueur */
    fscanf(fp, "%d", &map.beginx);
    fscanf(fp, "%d", &map.beginy);

    /* Read the number of the tileset */
    fscanf(fp, "%d", &map.tilesetDisplay);
    map.maxX = map.maxY = 0;

    for(y = 0 ; y < MAX_MAP_Y ; y++)
    {
        for(x = 0 ; x < MAX_MAP_X ; x++)
        {
            /* On lit le numéro de la tile et on le copie dans notre tableau */
            fscanf(fp, "%d", &map.tile[y][x]);

            /* Permet de déterminer la taille de la map (voir plus bas) */
            if(map.tile[y][x] > 0)
            {
                if(x > map.maxX)
                    map.maxX = x;
                if(y > map.maxY)
                    map.maxY = y;
            }
        }
    }

    /* Deuxième couche de tiles */
    for(y = 0 ; y < MAX_MAP_Y ; y++)
    {
        /* On lit le numéro de la tile et on le copie dans notre tableau */
        for(x = 0 ; x < MAX_MAP_X ; x++)
            fscanf(fp, "%d", &map.tile2[y][x]);
    }

    /* Troisième couche de tiles */
    for(y = 0 ; y < MAX_MAP_Y ; y++)
    {
        /* On lit le numéro de la tile et on le copie dans notre tableau */
        for(x = 0 ; x < MAX_MAP_X ; x++)
            fscanf(fp, "%d", &map.tile3[y][x]);
    }

    /* maxX et maxY sont les coordonnées de fin de la map.
    On les trouve dès qu'il n'y a plus que des zéros à la suite.
    Comme ça, on peut faire des maps de tailles différentes avec la même
    structure de fichier. */
    map.maxX = (map.maxX + 1) * TILE_SIZE;
    map.maxY = (map.maxY + 1) * TILE_SIZE;

    /* Et on referme le fichier */
    fclose(fp);

}



void drawMap(int layer)
{
    int mapX, x1, x2, mapY, y1, y2;

    /* On initialise mapX à la première colonne qu'on doit blitter.
    Celle-ci correspond au x de la map (en pixels) divisés par la taille d'une tile (32)
    pour obtenir la bonne colonne de notre map
    Exemple : si x du début de la map = 1026, on fait 1026 / 32
    et on sait qu'on doit commencer par afficher la 32ème colonne de tiles de notre map */
    mapX = map.startX / TILE_SIZE;

    /* Coordonnées de départ pour l'affichage de la map : permet
    de déterminer à quels coordonnées blitter la première colonne de tiles au pixel près
    (par exemple, si la première colonne n'est visible qu'en partie, on devra commencer à blitter
    hors écran, donc avoir des coordonnées négatives - d'où le -1). */
    x1 = (map.startX % TILE_SIZE) * -1;

    /* Calcul des coordonnées de la fin de la map : jusqu'où doit-on blitter ?
    Logiquement, on doit aller à x1 (départ) + SCREEN_WIDTH (la largeur de l'écran).
    Mais si on a commencé à blitter en dehors de l'écran la première colonne, il
    va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
    blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
    if(x1 != 0)
    x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forcément, c'est plus long ;)*/

    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    /* On fait exactement pareil pour calculer y */
    mapY = map.startY / TILE_SIZE;
    y1 = (map.startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    /* On met en place un timer pour animer la map */
    if(map.mapTimer <= 0)
    {
        map.tileSetNumber =
            map.tileSetNumber == 0 ? 1 : 0;

        map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;
    }
    else map.mapTimer--;

    /* Dessine la carte en commençant par startX et startY
    On dessine ligne par ligne en commençant par y1 (0) jusqu'à y2 (480)
    A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
    de tile (qui fait 32 pixels de hauteur) */
    drawLayer(layer, mapX, x1, x2, mapY, y1, y2);

}



void drawLayer(int layer, int mapX, int x1, int x2, int mapY, int y1, int y2)
{
    int x, y, xsource, ysource, a;

    for(y = y1 ; y < y2 ; y += TILE_SIZE)
    {
        /* A chaque début de ligne, on réinitialise mapX qui contient la colonne
        (0 au début puisqu'on ne scrolle pas) */
        mapX = map.startX / TILE_SIZE;

        /* A chaque colonne de tile, on dessine la bonne tile en allant
        de x = 0 à x = 640 */
        for(x = x1 ; x < x2 ; x += TILE_SIZE)
        {
            /* Suivant le numéro de notre tile, on découpe le tileset (a = le numéro
            de la tile */
            if(layer == 1)
            {
                drawTileMonster(mapY, mapX);
                a = map.tile[mapY][mapX];
            }
            else if(layer == 2)
                a = map.tile2[mapY][mapX];
            else
                a = map.tile3[mapY][mapX];

            /* Calcul pour obtenir son y (pour un tileset de 10 tiles
            par ligne, d'où le 10) */
            ysource = a / 10 * TILE_SIZE;

            /* Et son x */
            xsource = a % 10 * TILE_SIZE;

            /* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
            SDL_Texture *tileset =
                map.tileSetNumber == 0 ? map.tileSet : map.tileSetB;

            drawTile(tileset, x, y, xsource, ysource);
            mapX++;
        }
        mapY++;
    }
}



void drawTileMonster(int mapY, int mapX)
{
    /* Si la tile à dessiner n'est pas une tile vide */
    if(map.tile[mapY][mapX] != 0)
    {
        /* On teste si c'est une tile monstre (tile numéro 12) */
        if(map.tile[mapY][mapX] >= TILE_MONSTER)
        {
            /* On initialise un monstre en envoyant les
            coordonnées de la tile */
            initializeNewMonster(mapX * TILE_SIZE, mapY * TILE_SIZE, map.tile[mapY][mapX]);

            /* Et on efface cette tile de notre tableau pour éviter un spawn de monstres infini */
            map.tile[mapY][mapX] = 0;
        }
    }

}



void changeLevel(void)
{
    char file[200];

    /* Charge la map depuis le fichier */
    sprintf(file, "ressources/map/map%d.txt", getLevel());
    loadMap(file);

    /* Charge le tileset */
    if(map.tileSet != NULL)
        SDL_DestroyTexture(map.tileSet);
    if(map.tileSetB != NULL)
        SDL_DestroyTexture(map.tileSetB);

    sprintf(file, "ressources/graphics/tileset%d.png", map.tilesetDisplay);
    map.tileSet = loadImage(file);

    sprintf(file, "ressources/graphics/tileset%dB.png", map.tilesetDisplay);
    map.tileSetB = loadImage(file);

}



int getStartX(void)
{
    return map.startX;

}



void setStartX(int valeur)
{
    map.startX = valeur;

}



int getStartY(void)
{
    return map.startY;

}



void setStartY(int valeur)
{
    map.startY = valeur;

}



int getMaxX(void)
{
    return map.maxX;

}



int getMaxY(void)
{
    return map.maxY;

}



int getBeginX(void)
{
    return map.beginx;

}



int getBeginY(void)
{
    return map.beginy;

}



int getTileValue(int y, int x)
{
    return map.tile[y][x];

}



void mapCollision(GameObject *entity)
{
    int i;

    /* On va tester les mouvements horizontaux en premier
    (axe des X). On va se servir de i comme compteur pour notre boucle.
    En fait, on va découper notre sprite en blocs de tiles pour voir
    quelles tiles il est susceptible de recouvrir.
    On va donc commencer en donnant la valeur de Tile_Size à i pour qu'il
    teste la tile où se trouve le x du joueur mais aussi la suivante SAUF
    dans le cas où notre sprite serait inférieur à la taille d'une tile.
    Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
    Et on testera ensuite 2 fois la même tile. Mais comme ça notre code
    sera opérationnel quelle que soit la taille de nos sprites ! */
    if(entity->h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->h;

    /* On lance alors une boucle for infinie car on l'interrompra selon
    les résultats de nos calculs */
    mapCollisionHorizontal(entity, i);

    /* On recommence la même chose avec le mouvement vertical (axe des Y) */
    if(entity->w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->w;

    mapCollisionVertical(entity, i);

    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
    entity->x += entity->dirX;
    entity->y += entity->dirY;

    /* Et on contraint son déplacement aux limites de l'écran. */
    if(entity->x < 0)
        entity->x = 0;
    else if(entity->x + entity->w >= map.maxX)
    {
        /* Si on touche le bord droit de l'écran, on annule
        et on limite le déplacement du joueur */
        entity->x = map.maxX - entity->w - 1;
    }

    if(entity->y < 0)
        entity->y = 0;
    else if(entity->y + entity->h >= map.maxY)
        entity->y = map.maxY - entity->h - 1;

}



void mapCollisionHorizontal(GameObject *entity, int i)
{
    for( ; ; )
    {
        /* On va calculer ici les coins de notre sprite à gauche et à
        droite pour voir quelle tile ils touchent. */
        int x1 = (entity->x + entity->dirX) / TILE_SIZE;
        int x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

        /*Même chose avec y, sauf qu'on va monter au fur et à mesure
        pour tester toute la hauteur de notre sprite, grâce à notre
        fameuse variable i. */
        int y1 = entity->y / TILE_SIZE;
        int y2 = (entity->y + i - 1) / TILE_SIZE;

        /* De là, on va tester les mouvements initiés dans updatePlayer
        grâce aux vecteurs dirX et dirY, tout en testant avant qu'on
        se situe bien dans les limites de l'écran. */
        if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            /* Si on a un mouvement à droite */
            if(entity->dirX > 0 && (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE))
            {
                /* On vérifie si les tiles recouvertes sont solides */
                /* Si c'est le cas, on place le joueur aussi près que possible
                de ces tiles, en mettant à jour ses coordonnées. Enfin, on
                réinitialise son vecteur déplacement (dirX). */
                entity->x = x2 * TILE_SIZE;
                entity->x -= entity->w + 1;
                entity->dirX = 0;
            }
            /* Même chose à gauche */
            else if(entity->dirX < 0 && (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE))
            {
                entity->x = (x1 + 1) * TILE_SIZE;
                entity->dirX = 0;
            }

        }

        /* On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite. */
        if(i == entity->h)
            break;

        /* Sinon, on teste les tiles supérieures en se limitant à la hauteur du sprite. */
        i += TILE_SIZE;

        if (i > entity->h)
            i = entity->h;
    }

}



void mapCollisionVertical(GameObject *entity, int i)
{
    for( ; ; )
    {
        int x1 = (entity->x) / TILE_SIZE;
        int x2 = (entity->x + i) / TILE_SIZE;

        int y1 = (entity->y + entity->dirY) / TILE_SIZE;
        int y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

        if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if(entity->dirY > 0 && (map.tile[y2][x1] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE))
            {
                /* Déplacement en bas. Si la tile est une tile solide, on y colle le joueur */
                entity->y = y2 * TILE_SIZE;
                entity->y -= entity->h;
                entity->dirY = 0;
            }
            else if(entity->dirY < 0 && (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE))
            {
                /* Déplacement vers le haut */
                entity->y = (y1 + 1) * TILE_SIZE;
                entity->dirY = 0;
            }
        }

        /* On teste la largeur du sprite (même technique que pour la hauteur précédemment) */
        if(i == entity->w)
            break;

        i += TILE_SIZE;

        if (i > entity->w)
            i = entity->w;
    }

}




void monsterCollisionToMap(GameObject *entity)
{
    int i;

    /* On va tester les mouvements horizontaux en premier
    (axe des X). On va se servir de i comme compteur pour notre boucle.
    En fait, on va découper notre sprite en blocs de tiles pour voir
    quelles tiles il est susceptible de recouvrir.
    On va donc commencer en donnant la valeur de Tile_Size à i pour qu'il
    teste la tile où se trouve le x du joueur mais aussi la suivante SAUF
    dans le cas où notre sprite serait inférieur à la taille d'une tile.
    Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
    Et on testera ensuite 2 fois la même tile. Mais comme ça notre code
    sera opérationnel quelle que soit la taille de nos sprites ! */
    if(entity->h > TILE_SIZE) i = TILE_SIZE;
    else i = entity->h;

    /* On lance alors une boucle for infinie car on l'interrompra selon
    les résultats de nos calculs */
    monsterCollisionToMapHorizontal(entity, i);

    /* On recommence la même chose avec le mouvement vertical (axe des Y) */
    if(entity->w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->w;

    monsterCollisionToMapVertical(entity, i);

    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
    entity->x += entity->dirX;
    entity->y += entity->dirY;

}



void monsterCollisionToMapHorizontal(GameObject *entity, int i)
{
    for( ; ; )
    {
        /* On va calculer ici les coins de notre sprite à gauche et à
        droite pour voir quelle tile ils touchent. */
        int x1 = (entity->x + entity->dirX) / TILE_SIZE;
        int x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

        /*Même chose avec y, sauf qu'on va monter au fur et à mesure
        pour tester toute la hauteur de notre sprite, grâce à notre
        fameuse variable i. */
        int y1 = entity->y / TILE_SIZE;
        int y2 = (entity->y + i - 1) / TILE_SIZE;

        /* De là, on va tester les mouvements initiés dans updatePlayer
        grâce aux vecteurs dirX et dirY, tout en testant avant qu'on
        se situe bien dans les limites de l'écran. */
        if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            /* Si on a un mouvement à droite */
            if(entity->dirX > 0 && (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE))
            {
                /* On vérifie si les tiles recouvertes sont solides
                Si c'est le cas, on place le joueur aussi près que possible
                de ces tiles, en mettant à jour ses coordonnées. Enfin, on
                réinitialise son vecteur déplacement (dirX). */
                entity->x = x2 * TILE_SIZE;
                entity->x -= entity->w + 1;
                entity->dirX = 0;
                entity->timerRandDir = 0;
            }
            /* Même chose à gauche */
            else if(entity->dirX < 0 && (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE))
            {
                entity->x = (x1 + 1) * TILE_SIZE;
                entity->dirX = 0;
                entity->timerRandDir = 0;
            }
        }

        /* On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite. */
        if(i == entity->h)
            break;

        /* Sinon, on teste les tiles supérieures en se limitant à la hauteur du sprite. */
        i += TILE_SIZE;

        if (i > entity->h)
            i = entity->h;
    }

}



void monsterCollisionToMapVertical(GameObject *entity, int i)
{
    for( ; ; )
    {
        int x1 = (entity->x) / TILE_SIZE;
        int x2 = (entity->x + i) / TILE_SIZE;

        int y1 = (entity->y + entity->dirY) / TILE_SIZE;
        int y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

        if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if(entity->dirY > 0 && (map.tile[y2][x1] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE))
            {
                /* Déplacement en bas. Si la tile est une tile solide, on y colle le joueur */
                entity->y = y2 * TILE_SIZE;
                entity->y -= entity->h;
                entity->dirY = 0;
                entity->timerRandDir = 0;
            }
            else if(entity->dirY < 0 && (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE))
            {
                /* Déplacement vers le haut */
                entity->y = (y1 + 1) * TILE_SIZE;
                entity->dirY = 0;
                entity->timerRandDir = 0;
            }
        }

        /* On teste la largeur du sprite (même technique que pour la hauteur précédemment) */
        if(i == entity->w)
            break;

        i += TILE_SIZE;

        if (i > entity->w)
            i = entity->w;
    }

}



