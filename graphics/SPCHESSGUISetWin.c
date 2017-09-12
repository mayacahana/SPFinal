/*
 * SPCHESSGUISetWin.c
 *
 *  Created on: 12 בספט׳ 2017
 *      Author: uri
 */

#include "SPCHESSGUISetWin.h"
#include "SPCHESSGUICommon.h"

SPCHESSSetWin* spSetWindowCreate() {
	SPCHESSSetWin* res = (SPCHESSSetWin*) calloc(sizeof(SPCHESSSetWin),
			sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL) {
		printf("Couldn't create spChessSetWin struct\n");
		return NULL;
	}
	res->setWindow = SDL_CreateWindow("Setting State", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, 1400, 1400, SDL_WINDOW_OPENGL);
	if (res->setWindow == NULL) {
		spSetWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	res->setRenderer = SDL_CreateRenderer(res->setWindow, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->setRenderer == NULL) {
		spLoadWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	res->numOfBtns = NUM_OF_SET_BUTTONS;
	const char* activeImages[NUM_OF_SET_BUTTONS] = { INACT_IMG("game_mode"),
			ACT_IMG("one_player"), ACT_IMG("two_player"), INACT_IMG(
					"difficulty"), ACT_IMG("noob"), ACT_IMG("easy"), ACT_IMG(
					"moderate"), ACT_IMG("hard"), INACT_IMG("select_color"),
			ACT_IMG("black_player"), ACT_IMG("white_player"), ACT_IMG("start"),
			ACT_IMG("back") };

	const char* inactiveImages[NUM_OF_SET_BUTTONS] = { INACT_IMG("game_mode"),
			INACT_IMG("one_player"), INACT_IMG("two_player"), INACT_IMG(
					"difficulty"), INACT_IMG("noob"), INACT_IMG("easy"),
			INACT_IMG("moderate"), INACT_IMG("hard"), INACT_IMG("select_color"),
			INACT_IMG("black_player"), INACT_IMG("white_player"), INACT_IMG(
					"start"), INACT_IMG("back") };

	int xBtns[NUM_OF_SET_BUTTONS] = { 630, 100, 400, 630, 50, 350, 650, 950,
			630, 100, 400, 100, 400 };
	int yBtns[NUM_OF_SET_BUTTONS] = { 50, 150, 150, 250, 350, 350, 350, 350,
			450, 550, 550, 750, 750 };

	bool visible[NUM_OF_SET_BUTTONS] = { true, true, true, true, true, true,
			true, true,
			true, true, true, true, true };

	bool active[NUM_OF_SET_BUTTONS] = { false, true, true, false, false, false,
			false, false,
			false, false, false, false, true };

	SPCHESS_BUTTON_TYPE types[NUM_OF_SET_BUTTONS] = { BUTTON_SET_GAME_MODE,
			BUTTON_SET_ONE_PLAYER, BUTTON_SET_TWO_PLAYER, BUTTON_SET_DIFF,
			BUTTON_SET_NOOB_DIFF, BUTTON_SET_EASY_DIFF, BUTTON_SET_MOD_DIFF,
			BUTTON_SET_HARD_DIFF, BUTTON_SET_SELECT_COLOR,
			BUTTON_SET_BLACK_PLAYER, BUTTON_SET_WHITE_PLAYER, BUTTON_SET_START,
			BUTTON_SET_BACK };

	res->btns = createButtons(res->setRenderer, activeImages, inactiveImages,
			xBtns, yBtns, visible, active, types, res->numOfBtns);

	if (res->btns == NULL) {
		SDL_DestroyRenderer(res->setRenderer);
		SDL_DestroyWindow(res->setWindow);
		free(res);
	}

	res->game = spChessGameCreate(HISTORY_SIZE);
	return res;
}

void spSetWindowDestroy(SPCHESSSetWin* src) {
	if (!src)
		return;

	if (src->game != NULL)
		spChessGameDestroy(src->game);

	if (src->btns != NULL)
		destroyButtons(src->btns);
	if (src->setRenderer != NULL)
		SDL_DestroyRenderer(src->setRenderer);

	if (src->setWindow != NULL)
		SDL_DestroyWindow(src->setWindow);

	free(src);
}

void spSetWindowDraw(SPCHESSSetWin* src) {
	if (src == NULL)
		return;

	SDL_SetRenderDrawColor(src->setRenderer, 255, 255, 255, 255);
	SDL_RenderClear(src->setRenderer);
	for (int i = 0; i < src->numOfBtns; i++)
		drawButton(src->btns[i]);

	SDL_RenderPresent(src->setRenderer);
}

SPCHESS_SET_EVENT spSetWindowHandleEvent(SPCHESSSetWin* src, SDL_Event* event) {
	if (!src || !event)
		return SPCHESS_SET_INVALID_ARGUMENT;

	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		SPCHESS_BUTTON_TYPE btn = getButtonClicked(src->btns, src->numOfBtns,
				event, true);

		if (btn == BUTTON_SET_TWO_PLAYER) {
			src->game->gameMode = 2; //change the game mode to 2
			src->btns->active[11] = true; //activate start button
			//de-activate other options
			src->btns->active[4] = false;
			src->btns->active[5] = false;
			src->btns->active[6] = false;
			src->btns->active[7] = false;
			src->btns->active[9] = false;
			src->btns->active[10] = false;

			return SPCHESS_SET_GAME_MODE;
		} else if (btn == BUTTON_SET_ONE_PLAYER) {

			src->game->gameMode = 1; //change the game mode to 1
			//activate possible difficulty levels
			src->btns->active[4] = true;
			src->btns->active[5] = true;
			src->btns->active[6] = true;
			src->btns->active[7] = true;
			src->btns->active[11] = false; //de-activate start btn
			return SPCHESS_SET_GAME_MODE;
		} else if (btn >= BUTTON_SET_NOOB_DIFF && btn <= BUTTON_SET_HARD_DIFF) {

			src->game->difficulty = btn - 13; //set difficulty (assuming BUTTON_SET_NOOB_DIFF = 14)
			//activate color player stage
			src->btns->active[9] = true;
			src->btns->active[10] = true;
			return SPCHESS_SET_DIFF;
		} else if(btn == BUTTON_SET_WHITE_PLAYER || btn == BUTTON_SET_BLACK_PLAYER) {
			src->game->colorUser = btn - 19; //set user color (assuming BUTTON_SET_BLACK_PLAYER = 19)
			src->btns->active[11] = true; //activate start button
			return SPCHESS_SET_COLOR;
		} else if(btn == BUTTON_SET_BACK)
			return SPCHESS_SET_BACK;
		else if(btn == BUTTON_SET_START)
			return SPCHESS_SET_START;
		break;

	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE)
			return SPCHESS_SET_QUIT;
		break;
	default:
		return SPCHESS_SET_NONE;
	}
	return SPCHESS_SET_NONE;
}

void spSetWindowHide(SPCHESSSetWin* src) {
	SDL_HideWindow(src->setWindow);
}

void spSetWindowShow(SPCHESSSetWin* src) {
	SDL_ShowWindow(src->setWindow);
}
