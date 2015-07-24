#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include "structs.h"


/***** Catalogue des prototypes des fonctions utilisées *****/



/* attaques.c */
extern void attackManagement(Input *input, GameObject *entity);
extern int canAttack(GameObject *entity);
extern void drawOneHandAttack(GameObject *entity);



/* direction.c */
extern int randomDirection(GameObject *entity);
extern void playerDirLeft(Input *input, GameObject *entity);
extern void playerDirUp(Input *input, GameObject *entity);
extern void playerDirDown(Input *input, GameObject *entity);
extern void playerDirRight(Input *input, GameObject *entity);
extern void playerDir(Input *input, GameObject *entity);
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
extern void drawLifePlayer(void);
extern void drawLifeMonster(GameObject *entity);
extern void drawCoinPlayer(void);
extern void drawTileHUD(SDL_Texture *image, int destx, int desty, int srcx, int srcy, int w, int h, float coeffW, float coeffH);



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



/* monster.c */
extern GameObject *getMonster(int nombre);
extern int getMonsterX(int nombre);
extern int getMonsterY(int nombre);
extern int getMonsterNumber(void);
extern void resetMonsters(void);
extern void initMonsterSprites(void);
extern void cleanMonsters(void);
extern void initializeNewMonster(int x, int y, int name);
extern void updateMonsters(void);
extern int collide(GameObject *player, GameObject *monster);
extern void drawMonster(GameObject *entity);
extern int getMonsterFrameTimer(int name);
extern int getMonsterFrameMax(int name, int borned);
extern void monsterBlitt(int name, int etat, int frameNumber, int *w, int *h, int *x, int *y, int borned);
extern int monsterMoves(GameObject *entity, int name);
extern int monsterWasBorned(int *frame, int name);
extern void monsterDirection(int *etat, float *dX, float *dY, int direction);
extern void initStatsMonsters(int *borned, int *frame, float *directionAleatoire);
extern int monsterLife(int name);
extern int monsterWForLife(int name);



/* oneHand.c */
extern void drawOnehand(void);
extern void getOneHandDest(int *x, int *y);
extern void getOneHandDestRight(int *x, int *y);
extern void getOneHandDestLeft(int *x, int *y);
extern void getOneHandDestUp(int *x, int *y);
extern void getOneHandDestDown(int *x, int *y);
extern int oneHandHurt(int mX, int mY, int mW, int mH);



/* player.c */
extern GameObject *getPlayer(void);
extern int getAttack(void);
extern SDL_Texture *getSprite(void);
extern int getPlayerx(void);
extern int getPlayery(void);
extern int getPlayerFrameNumber(void);
extern int getPlayerDirection(void);
extern void setPlayerDirX(float valeur);
extern void setPlayerDirY(float valeur);
extern int getLevel(void);
extern void setLevelNumber(int valeur);
extern int getLifeNumber(void);
extern void setLifeNumber(int valeur);
extern int getStarNumber(void);
extern int getTouch(void);
extern void setStarNumber(int valeur);
extern void initPlayerSprites(void);
extern void cleanPlayer(void);
extern int getLife(void);
extern int getLifeMax(void);
extern void killPlayer(void);
extern void playerHurts(GameObject monster);
extern int getHurts(void);
extern void initializePlayer(int newLevel);
extern void drawPlayer(void);
extern void updatePlayer(Input *input);
extern void centerScrollingOnPlayer(void);
extern void walkFrameTimer(void);
extern void attackFrameTimer(void);
extern void entityTouch(void);



/* sounds.c */
extern void loadSong(char filename[200]);
extern void cleanUpMusic(void);
extern void loadSound(void);
extern void freeSound(void);
extern void playSoundFx(int type);



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
extern int getMasterBlaguleLife(void);




#endif // PROTOTYPES_H_INCLUDED
