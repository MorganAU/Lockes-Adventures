#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include "structs.h"


/***** Catalogue des prototypes des fonctions utilisées *****/



/* attaques.c */
extern void gestionAttaque(Input *input, GameObject *entity);
extern int canAttack(GameObject *entity);
extern void drawOneHandAttack(GameObject *entity);



/* direction.c */
extern int randomDirection(GameObject *entity);
extern void playerLeft(Input *input, GameObject *entity);
extern void playerUp(Input *input, GameObject *entity);
extern void playerDown(Input *input, GameObject *entity);
extern void playerRight(Input *input, GameObject *entity);
extern void playerDirection(Input *input, GameObject *entity);
extern void playerIdleHorizontale(GameObject *entity);
extern void playerIdleVerticale(GameObject *entity);
extern void playerIdle(Input *input, GameObject *entity);
extern void setEntityDirX(GameObject *entity, float valeur);
extern void setEntityDirY(GameObject *entity, float valeur);
extern void touchDirLeft(GameObject *defenseur, GameObject attaquant);
extern void touchDirRight(GameObject *defenseur, GameObject attaquant);
extern void touchDirUp(GameObject *defenseur, GameObject attaquant);
extern void touchDirDown(GameObject *defenseur, GameObject attaquant);
extern void touchDir(int direction, GameObject *defenseur, GameObject attaquant);



/* draw.c */
extern void drawGame(void);
extern SDL_Texture *loadImage(char *name);
extern void drawImage(SDL_Texture *, int, int);
extern void delay(unsigned int frameLimit);
extern void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);
extern void initHUD(void);
extern void cleanHUD(void);
extern void drawHUD(void);
extern void drawLife(void);
extern void drawLifeMax(void);
extern void drawCoinPlayer(void);



/* font.c */
extern void loadFont(char *name, int size);
extern void closeFont(void);
extern void drawString(char *text, int x, int y, int r, int g, int b, int a);



/* init.c */
extern SDL_Renderer *getRenderer(void);
extern void init(char *title);
extern void cleanup(void);
extern void loadGame(void);



/* input.c */
extern void gestionInputs(Input *input);
extern void getInput(Input *input);
extern void openJoystick(void);
extern void closeJoystick(void);
extern void getJoystick(Input *input);
extern void resetInput(Input *input);



/* map.c */
extern void initMaps(void);
extern SDL_Texture *getBackground(void);
extern SDL_Texture *getTileSetA(void);
extern SDL_Texture *getTileSetB(void);
extern void cleanMaps(void);
extern void loadMap(char *name);
extern void drawMap(int);
extern void changeLevel(void);
extern int getStartX(void);
extern void setStartX(int valeur);
extern int getStartY(void);
extern void setStartY(int valeur);
extern int getMaxX(void);
extern int getMaxY(void);
extern int getBeginX(void);
extern int getBeginY(void);
extern int getTileValue(int y, int x);
extern void mapCollision(GameObject *entity);
extern void monsterCollisionToMap(GameObject *entity);



/* oneHand.c */
extern void drawOnehand(void);
extern int getOneHandX(void);
extern int getOneHandY(void);








extern void centerScrollingOnPlayer(void);
extern int checkFall(GameObject monster);
extern void cleanMonsters(void);
extern void cleanPlayer(void);
extern int collide(GameObject *player, GameObject *monster);
extern void drawMonster(GameObject *entity);
extern void drawPlayer(void);
extern void getJoystick(Input *input);
extern int getLevel(void);
extern int getLife(void);
extern int getLifeMax(void);
extern GameObject *getMonster(int nombre);
extern int getNombreDetoiles(void);
extern int getNombreDeVies(void);
extern int getMonsterNumber(void);
extern GameObject *getPlayer(void);
extern int getPlayerDirection(void);
extern int getPlayerx(void);
extern int getPlayery(void);
extern int getTileValue(int y, int x);
extern void initializePlayer(int newLevel);
extern void initializeNewMonster(int x, int y, int name);
extern void initMonsterSprites(void);
extern void initPlayerSprites(void);
extern void killPlayer(void);
extern void mapCollision(GameObject *entity);
extern void playerHurts(GameObject monster);
extern void resetMonsters(void);
extern void setNombreDeVies(int valeur);
extern void setNombreDetoiles(int valeur);
extern void setValeurDuNiveau(int valeur);
extern void updatePlayer(Input *input);
extern void updateMonsters(void);
extern SDL_Texture *getSprite(void);


/* Nouvelles fonctions, je dois faire le tri :D */
extern int getPlayerFrameNumber(void);
extern int getPlayerDirection(void);
extern int oneHandHurt(int mX, int mY, int mW, int mH);
extern int getAttack(void);



extern void setPlayerDirX(float valeur);
extern void setPlayerDirY(float valeur);
extern void entityTouch(void);
extern int getEtat(int nombre);
extern int getWidthBlaguleSprite(int etat, int frameNumber);
extern int getHeightBlaguleSprite(int etat, int frameNumber);

extern int getMonsterWidth(int frame, int statut);
extern int getMonsterHeight(int frame, int statut);
extern int getMonsterSourceSpriteX(int frame, int statut);
extern int getMonsterSourceSpriteY(int frame, int statut);

extern int getHurts(void);



extern void loadSong(char filename[200]);
extern void cleanUpMusic(void);
extern void loadSound(void);
extern void freeSound(void);
extern void playSoundFx(int type);





extern int getMonsterFrameTimer(int name);
extern int getMonsterFrameMax(int name, int borned);
extern void monsterBlitt(int name, int etat, int frameNumber, int *w, int *h, int *x, int *y, int borned);
extern int getMonsterX(int nombre);
extern int getMonsterY(int nombre);




extern int monsterMoves(GameObject *entity, int name);
extern int blaguleRandomMoves(GameObject *entity);





extern int monsterWasBorned(int *frame, int name);
extern void monsterDirection(int *etat, float *dX, float *dY, int direction);



extern void initialiseStatsMonsters(int *borned, int *frame, float *directionAleatoire);




extern void walkFrameTimer(void);
extern void attackFrameTimer(void);



/**** Prototypes des monstres ****/

/* blagule.c */
extern int getBlaguleWidth(int frame, int statut, int borned);
extern int getBlaguleHeight(int frame, int statut, int borned);
extern int getBlaguleSourceX(int frame, int statut, int borned);
extern int getBlaguleSourceY(int frame, int statut, int borned);
extern void blaguleBlitt(int etat, int frameNumber, int *w, int *h, int *x, int *y, int borned);
extern int getBlaguleFrameTimer(void);
extern int getBlaguleFrameMax(int borned);



/* masterBlagule.c */
extern int getMasterBlaguleWidth(int frame);
extern int getMasterBlaguleHeight(int frame);
extern int getMasterBlaguleSourceX(int frame);
extern int getMasterBlaguleSourceY(int frame);
extern void masterBlaguleBlitt(int frameNumber, int *w, int *h, int *x, int *y);
extern int getMasterBlaguleFrameTimer(void);
extern int getMasterBlaguleFrameMax(void);
extern void masterBlaguleAttack(void);




#endif // PROTOTYPES_H_INCLUDED
