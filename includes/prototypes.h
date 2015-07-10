#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include "structs.h"

/* Catalogue des prototypes des fonctions utilisées */
extern int canAttack(GameObject *entity);
extern void centerScrollingOnPlayer(void);
extern void changeLevel(void);
extern int checkFall(GameObject monster);
extern void cleanHUD(void);
extern void cleanMaps(void);
extern void cleanMonsters(void);
extern void cleanPlayer(void);
extern void cleanup(void);
extern void closeJoystick(void);
extern int collide(GameObject *player, GameObject *monster);
extern void delay(unsigned int frameLimit);
extern void drawString(char *text, int x, int y, int r, int g, int b, int a);
extern void drawGame(void);
extern void drawHUD(void);
extern void drawImage(SDL_Texture *, int, int);
extern void drawMap(int);
extern void drawMonster(GameObject *entity);
extern void drawPlayer(void);
extern void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);
extern void gestionInputs(Input *input);
extern SDL_Texture *getBackground(void);
extern int getBeginX(void);
extern int getBeginY(void);
extern void getInput(Input *input);
extern void getJoystick(Input *input);
extern int getLevel(void);
extern int getLife(void);
extern int getLifeMax(void);
extern int getMaxX(void);
extern int getMaxY(void);
extern GameObject *getMonster(int nombre);
extern int getNombreDetoiles(void);
extern int getNombreDeVies(void);
extern int getMonsterNumber(void);
extern GameObject *getPlayer(void);
extern int getPlayerDirection(void);
extern int getPlayerx(void);
extern int getPlayery(void);
extern SDL_Texture *getTileSetA(void);
extern SDL_Texture *getTileSetB(void);
extern int getTileValue(int y, int x);
extern SDL_Renderer *getRenderer(void);
extern int getStartX(void);
extern int getStartY(void);
extern void init(char *);
extern void initHUD(void);
extern void initializePlayer(int newLevel);
extern void initMaps(void);
extern void initializeNewMonster(int x, int y, int name);
extern void initMonsterSprites(void);
extern void initPlayerSprites(void);
extern void killPlayer(void);
extern void loadFont(char *name, int size);
extern void loadGame(void);
extern SDL_Texture *loadImage(char *name);
extern void loadMap(char *name);
extern void mapCollision(GameObject *entity);
extern void monsterCollisionToMap(GameObject *entity);
extern void openJoystick(void);
extern void playerHurts(GameObject monster);
extern void resetMonsters(void);
extern void setNombreDeVies(int valeur);
extern void setNombreDetoiles(int valeur);
extern void setStartX(int valeur);
extern void setStartY(int valeur);
extern void setValeurDuNiveau(int valeur);
extern void updatePlayer(Input *input);
extern void updateMonsters(void);
extern SDL_Texture *getSprite(void);
extern void drawOneHandAttack(GameObject *entity);


/* Nouvelles fonctions, je dois faire le tri :D */
extern void drawOnehand(void);
extern int getPlayerFrameNumber(void);
extern int getOneHandX(void);
extern int getOneHandY(void);
extern int getPlayerDirection(void);
extern int randomDirection(GameObject *entity);
extern void secondDirection(GameObject *entity);
extern int oneHandHurt(int mX, int mY, int mW, int mH);
extern int getAttack(void);
extern void playerLeft(Input *input, GameObject *entity);
extern void playerUp(Input *input, GameObject *entity);
extern void playerDown(Input *input, GameObject *entity);
extern void playerRight(Input *input, GameObject *entity);
extern void playerDirection(Input *input, GameObject *entity);
extern void gestionAttaque(Input *input, GameObject *entity);



extern void setPlayerDirX(float valeur);
extern void setPlayerDirY(float valeur);
extern void entityTouch(GameObject *entity);
extern int getEtat(int nombre);
extern int getWidthBlaguleSprite(int etat, int frameNumber);
extern int getHeightBlaguleSprite(int etat, int frameNumber);

extern int getMonsterWidth(int frame, int statut);
extern int getMonsterHeight(int frame, int statut);
extern int getMonsterSourceSpriteX(int frame, int statut);
extern int getMonsterSourceSpriteY(int frame, int statut);

extern void drawLifeMax(void);
extern void drawLife(void);
extern void drawCoinPlayer(void);
extern int getHurts(void);



extern void loadSong(char filename[200]);
extern void cleanUpMusic(void);
extern void loadSound(void);
extern void freeSound(void);
extern void playSoundFx(int type);




extern int getBlaguleWidth(int frame, int statut, int borned);
extern int getBlaguleHeight(int frame, int statut, int borned);
extern int getBlaguleSourceX(int frame, int statut, int borned);
extern int getBlaguleSourceY(int frame, int statut, int borned);
extern void blaguleBlitt(int etat, int frameNumber, int *w, int *h, int *x, int *y, int borned);
extern void masterBlaguleBlitt(int frameNumber, int *w, int *h, int *x, int *y);

extern int getMasterBlaguleWidth(int frame);
extern int getMasterBlaguleHeight(int frame);
extern int getMasterBlaguleSourceX(int frame);
extern int getMasterBlaguleSourceY(int frame);
extern int getMonsterFrameTimer(int name);
extern int getMasterBlaguleFrameTimer(void);
extern int getBlaguleFrameTimer(void);
extern int getMonsterFrameMax(int name, int borned);
extern int getMasterBlaguleFrameMax(void);
extern int getBlaguleFrameMax(int borned);
extern void monsterBlitt(int name, int etat, int frameNumber, int *w, int *h, int *x, int *y, int borned);
extern int getMonsterX(int nombre);
extern int getMonsterY(int nombre);

extern void masterBlaguleAttack(void);



extern int monsterMoves(GameObject *entity, int name);
extern int blaguleRandomMoves(GameObject *entity);





extern int monsterWasBorned(int *frame, int name);
extern void monsterDirection(int *etat, float *dX, float *dY, int direction);



extern void initialiseStatsMonsters(int *borned, int *frame, float *directionAleatoire);
extern void setEntityDirX(GameObject *entity, float valeur);
extern void setEntityDirY(GameObject *entity, float valeur);

extern void touchDirLeft(GameObject *defenseur, GameObject attaquant);
extern void touchDirRight(GameObject *defenseur, GameObject attaquant);
extern void touchDirUp(GameObject *defenseur, GameObject attaquant);
extern void touchDirDown(GameObject *defenseur, GameObject attaquant);
extern void touchDir(int direction, GameObject *defenseur, GameObject attaquant);


extern void resetInput(Input *input);


#endif // PROTOTYPES_H_INCLUDED
