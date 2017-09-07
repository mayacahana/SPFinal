/*
 * SPCHESSGUIManager.c
 *
 *  Created on: 7 בספט׳ 2017
 *      Author: uri
 */
#include "SPCHESSGUIManager.h"
#include <stdio.h>
#include <stdlib.h>

SPCHESSGuiManager* spManagerCreate() {
	SPCHESSGuiManager* res = (SPCHESSGuiManager*) malloc(
			sizeof(SPCHESSGuiManager));
	if (!res)
		return NULL;

	res->mainWin = spMainWindowCreate();
	if (!(res->mainWin)) {
		free(res);
		return NULL;
	}
	res->gameWin = NULL;
	res->loadWin = NULL;
	res->activeWin = SPCHESS_MAIN_WINDOW_ACTIVE;
	return res;
}

void spManagerDestroy(SPCHESSGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == SPCHESS_GAME_WINDOW_ACTIVE) {
		spGameWindowDestroy(src->gameWin);
	}
	if (src->activeWin == SPCHESS_LOAD_WINDOW_ACTIVE) {
		spGameWindowDestroy(src->loadWin);
	}
	spMainWindowDestroy(src->mainWin);
	free(src);
}

void spManagerDraw(SPCHESSGuiManager* src) {
	if (!src)
		return;

	if (src->activeWin == SPCHESS_MAIN_WINDOW_ACTIVE)
		spMainWindowDraw(src->mainWin);
	else if (src->activeWin == SPCHESS_LOAD_WINDOW_ACTIVE)
		spGameWindowDraw(src->loadWin);
	else if (src->activeWin == SPCHESS_GAME_WINDOW_ACTIVE)
		spGameWindowDraw(src->gameWin);
}

SPCHESS_MANAGER_EVENT handleManagerDueToMainEvent(SPCHESSGuiManager* src,
		SPCHESS_MAIN_EVENT event) {
	if (!src) {
		return SPCHESS_MANAGER_NONE;
	}
	if (event == SPCHESS_MAIN_NEW_GAME) {
		spMainWindowHide(src->mainWin);
		src->gameWin = spGameWindowCreate();
		if (src->gameWin == NULL) {
			printf("couldn't create game window\n");
			return SPCHESS_MANAGER_QUIT;
		}
		src->activeWin = SPCHESS_GAME_WINDOW_ACTIVE;
	}
	if (event == SPCHESS_MAIN_LOAD) {
		spMainWindowHide(src->mainWin);
		src->loadWin = spLoadWindowCreate();
		if (src->loadWin == NULL) {
			printf("couldn't create load window\n");
			return SPCHESS_MANAGER_QUIT;
		}
		src->activeWin = SPCHESS_LOAD_WINDOW_ACTIVE;
	}
	if (event == SPCHESS_MAIN_EXIT) {
		return SPCHESS_MANAGER_QUIT;
	}
	return SPCHESS_MANAGER_NONE;
}

//TODO: implement othor dueToEvent functions

SPCHESS_MANAGER_EVENT spManagerHandleEvent(SPCHESSGuiManager* src,
		SDL_Event* event) {
	if (!src || !event)
		return SPCHESS_MANAGER_NONE;

	if (src->activeWin == SPCHESS_MAIN_WINDOW_ACTIVE) {
		SPCHESS_MAIN_EVENT mainEvent = spMainWindowHandleEvent(src->mainWin,
				event);
		return handleManagerDueToMainEvent(src, mainEvent);
	} else if (src->activeWin == SPCHESS_GAME_WINDOW_ACTIVE) {
		SPCHESS_GAME_EVENT gameEvent = spGameWindowHandleEvent(src->gameWin,
				event);
		spManagerDraw(src);
		return handleManagerDueToGameEvent(src, gameEvent);
	} else if (src->activeWin == SPCHESS_LOAD_WINDOW_ACTIVE) {
		SPCHESS_LOAD_EVENT loadEvent = spGameWindowHandleEvent(src->loadWin,
				event);
		spManagerDraw(src);
		return handleManagerDueToLoadEvent(src, loadEvent);
	}
	return SPCHESS_MANAGER_NONE;
}

