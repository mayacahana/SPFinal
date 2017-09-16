/*
 * SPCHESSGUIManager.h
 *
 *  Created on: 7 בספט׳ 2017
 *      Author: uri
 */

#ifndef GRAPHICS_SPCHESSGUIMANAGER_H_
#define GRAPHICS_SPCHESSGUIMANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "SPCHESSGUILoadWin.h"
#include "SPCHESSGUIMainWin.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	SPCHESS_MAIN_WINDOW_ACTIVE,
	SPCHESS_GAME_WINDOW_ACTIVE,
	SPCHESS_LOAD_WINDOW_ACTIVE,
	SPCHESS_SET_WINDOW_ACTIVE,
	SPCHESS_NO_WINDOW
} SPCHESS_ACTIVE_WINDOW;

typedef enum {
	SPCHESS_MANAGER_QUIT, SPCHESS_MANAGER_NONE,
} SPCHESS_MANAGER_EVENT;

typedef struct spchessguimanager_t {
	SPCHESSGameWin* gameWin;
	SPCHESSMainWin* mainWin;
	SPCHESSLoadWin* loadWin;
	SPCHESSSetWin* setWin;
	SPCHESS_ACTIVE_WINDOW activeWin;
	SPCHESS_ACTIVE_WINDOW prevWin;
} SPCHESSGuiManager;

SPCHESSGuiManager* spManagerCreate();
void spManagerDestroy(SPCHESSGuiManager* src);
void spManagerDraw(SPCHESSGuiManager* src, SDL_Event* event);
SPCHESS_MANAGER_EVENT spManagerHandleEvent(SPCHESSGuiManager* src,
		SDL_Event* event);

SPCHESS_MANAGER_EVENT handleManagerDueToMainEvent(SPCHESSGuiManager* src, SPCHESS_MAIN_EVENT event);
SPCHESS_MANAGER_EVENT handleManagerDueToGameEvent(SPCHESSGuiManager* src, SPCHESS_GAME_EVENT event);
SPCHESS_MANAGER_EVENT handleManagerDueToLoadEvent(SPCHESSGuiManager* src, SPCHESS_LOAD_EVENT event);
SPCHESS_MANAGER_EVENT handleManagerDueToSetEvent(SPCHESSGuiManager* src, SPCHESS_SET_EVENT event);


#endif /* GRAPHICS_SPCHESSGUIMANAGER_H_ */
