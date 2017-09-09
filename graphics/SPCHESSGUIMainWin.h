/*
 * SPCHESSGUIMainWin.h
 *
 *  Created on: 7 בספט׳ 2017
 *      Author: uri
 */

#ifndef GRAPHICS_SPCHESSGUIMAINWIN_H_
#define GRAPHICS_SPCHESSGUIMAINWIN_H_

typedef enum {
	SPCHESS_MAIN_EXIT,
	SPCHESS_MAIN_NEW_GAME,
	SPCHESS_MAIN_INVALID_ARGUMENT,
	SPCHESS_MAIN_LOAD,
	SPCHESS_MAIN_NONE,
	SPCHESS_MAIN_QUIT
} SPCHESS_MAIN_EVENT;

typedef struct spchessmainwin_t {
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* exitTexture;
	SDL_Texture* newGameTexture;
	SDL_Texture* loadTexture;
} SPCHESSMainWin;


SPCHESSMainWin* spMainWindowCreate();
void spMainWindowDraw(SPCHESSMainWin* src);
void spMainWindowDestroy(SPCHESSMainWin* src);
void spMainWindowHide(SPCHESSMainWin* src);
void spMainWindowShow(SPCHESSMainWin* src);
SPCHESS_MAIN_EVENT spMainWindowHandleEvent(SPCHESSMainWin* src, SDL_Event* event);

int isClickOnNewGame(int x, int y);
int isClickOnLoad(int x, int y);
int isClickOnExit(int x, int y);

#endif /* GRAPHICS_SPCHESSGUIMAINWIN_H_ */
