/*
 * SPCHESSGUILoadWin.h
 *
 *  Created on: 8 בספט׳ 2017
 *      Author: uri
 */

#ifndef GRAPHICS_SPCHESSGUILOADWIN_H_
#define GRAPHICS_SPCHESSGUILOADWIN_H_
#include "SPCHESSGUICommon.h"

#define NUM_OF_LOAD_BUTTONS 7

typedef enum {
	SPCHESS_LOAD_SLOT,
	SPCHESS_LOAD_BACK,
	SPCHESS_LOAD_INVALID_ARGUMENT,
	SPCHESS_LOAD_NONE,
	SPCHESS_LOAD_LOAD,
	SPCHESS_LOAD_QUIT
} SPCHESS_LOAD_EVENT;

typedef struct spchessloadwin_t {
	SDL_Window* loadWindow;
	SDL_Renderer* loadRenderer;
	int numOfBtns;
	Button** btns;
	int slotPicked;
	SPCHESSGame* game;
} SPCHESSLoadWin;

SPCHESSLoadWin* spLoadWindowCreate();
void spLoadWindowDestroy(SPCHESSLoadWin* src);
void spLoadWindowDraw(SPCHESSLoadWin* src);
SPCHESS_LOAD_EVENT spLoadWindowHandleEvent(SPCHESSLoadWin* src, SDL_Event* event);
void spLoadWindowHide(SPCHESSLoadWin* src);
void spLoadWindowShow(SPCHESSLoadWin* src);


#endif /* GRAPHICS_SPCHESSGUILOADWIN_H_ */
