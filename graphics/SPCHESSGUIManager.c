/*
 * SPCHESSGUIManager.c
 *
 *  Created on: 7 בספט׳ 2017
 *      Author: uri
 */
#include "SPCHESSGUIManager.h"

SPCHESSGuiManager* spManagerCreate() {
	SPCHESSGuiManager* res = (SPCHESSGuiManager*) malloc(
			sizeof(SPCHESSGuiManager));
	if (!res)
		return NULL;

	res->mainWin = spMainWindowCreate();
	if (res->mainWin == NULL) {
		free(res);
		return NULL;
	}
	res->gameWin = NULL;
	res->loadWin = NULL;
	res->setWin = NULL;
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
	if (src->activeWin == SPCHESS_SET_WINDOW_ACTIVE) {
		spSetWindowDestroy(src->setWin);
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
		spLoadWindowDraw(src->loadWin);
	else if (src->activeWin == SPCHESS_GAME_WINDOW_ACTIVE)
		spGameWindowDraw(src->gameWin);
	else if(src->activeWin == SPCHESS_SET_WINDOW_ACTIVE)
		spSetWindowDraw(src->setWin);
}

SPCHESS_MANAGER_EVENT handleManagerDueToMainEvent(SPCHESSGuiManager* src,
		SPCHESS_MAIN_EVENT event) {
	if (!src)
		return SPCHESS_MANAGER_NONE;

	if (event == SPCHESS_MAIN_NEW_GAME) {
		spMainWindowHide(src->mainWin);
		src->setWin = spSetWindowCreate();
		if (src->setWin == NULL) {
			printf("couldn't create set window\n");
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
	if (event == SPCHESS_MAIN_EXIT || event == SPCHESS_MAIN_QUIT) {
		return SPCHESS_MANAGER_QUIT;
	}
	return SPCHESS_MANAGER_NONE;
}

SPCHESS_MANAGER_EVENT handleManagerDueToLoadEvent(SPCHESSGuiManager* src,
		SPCHESS_LOAD_EVENT event) {

	if (!src)
		return SPCHESS_MANAGER_NONE;

	if (event == SPCHESS_LOAD_BACK) {
		spLoalWindowHide(src->loadWin);
		spMainWindowShow(src->mainWin);
		src->activeWin = SPCHESS_MAIN_WINDOW_ACTIVE;
	}
	if (event == SPCHESS_LOAD_LOAD) {
		spLoadWindowHide(src->loadWin);
		src->gameWin = spGameWindowCreate();
		if (src->gameWin == NULL) {
			printf("couldn't create game window\n");
			return SPCHESS_MANAGER_QUIT;
		}
		src->activeWin = SPCHESS_GAME_WINDOW_ACTIVE;
	}
	if (event == SPCHESS_LOAD_QUIT)
		return SPCHESS_MANAGER_QUIT;

	return SPCHESS_MANAGER_NONE;

}

//implements dueToGame, dueToSet function

SPCHESS_MANAGER_EVENT spManagerHandleEvent(SPCHESSGuiManager* src,
		SDL_Event* event) {
	if (!src || !event)
		return SPCHESS_MANAGER_NONE;

	if (src->activeWin == SPCHESS_MAIN_WINDOW_ACTIVE) {
		SPCHESS_MAIN_EVENT mainEvent = spMainWindowHandleEvent(src->mainWin,
				event);
		spManagerDraw(src);
		return handleManagerDueToMainEvent(src, mainEvent);
	} else if (src->activeWin == SPCHESS_GAME_WINDOW_ACTIVE) {
		SPCHESS_GAME_EVENT gameEvent = spGameWindowHandleEvent(src->gameWin,
				event);
		spManagerDraw(src);
		return handleManagerDueToGameEvent(src, gameEvent);
	} else if (src->activeWin == SPCHESS_LOAD_WINDOW_ACTIVE) {
		SPCHESS_LOAD_EVENT loadEvent = spLoadWindowHandleEvent(src->loadWin,
				event);
		spManagerDraw(src);
		return handleManagerDueToLoadEvent(src, loadEvent);
	} else if (src->activeWin == SPCHESS_SET_WINDOW_ACTIVE) {
		SPCHESS_SET_EVENT setEvent = spSetWindowHandleEvent(src->setWin, event);
		spManagerDraw(src);
		return handleManagerDueToSetEvent(src, setEvent);
	}
	return SPCHESS_MANAGER_NONE;
}

