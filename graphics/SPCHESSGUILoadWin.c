/*
 * SPCHESSGUILoadWin.c
 *
 *  Created on: 8 בספט׳ 2017
 *      Author: uri
 */
#include "SPCHESSGUILoadWin.h"

int countSavedFiles() {
	int cnt = 0;
	while (cnt < NUM_SLOTS && (access(saved_files[cnt], F_OK) != -1)) {
		cnt++;
	}
	return cnt;
}

SPCHESSLoadWin* spLoadWindowCreate() {
	SPCHESSLoadWin* res = (SPCHESSLoadWin*) calloc(sizeof(SPCHESSLoadWin),
			sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL) {
		printf("Couldn't create spChessLoadWin struct\n");
		return NULL;
	}
	res->loadWindow = SDL_CreateWindow("Load", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_OPENGL);
	if (res->loadWindow == NULL) {
		spLoadWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	res->loadRenderer = SDL_CreateRenderer(res->loadWindow, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->loadRenderer == NULL) {
		spLoadWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	//back button
	loadingSurface = SDL_LoadBMP("./graphics/images/back.bmp");
	if (loadingSurface == NULL) {
		spLoadWindowDestroy(res);
		printf("couldn't create back.bmp surface\n");
		return NULL;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->loadRenderer,
			loadingSurface);
	if (res->backTexture == NULL) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create back.bmp texture\n");
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);

	//load button - inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/inactive_load.bmp");
	if (loadingSurface == NULL) {
		spLoadWindowDestroy(res);
		printf("couldn't create inactive_load.bmp surface\n");
		return NULL;
	}
	res->inactiveLoadTexture = SDL_CreateTextureFromSurface(res->loadRenderer,
			loadingSurface);
	if (res->inactiveLoadTexture == NULL) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create inactive_load.bmp texture\n");
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);

	//load button - inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/active_load.bmp");
	if (loadingSurface == NULL) {
		spLoadWindowDestroy(res);
		printf("couldn't create active_load.bmp surface\n");
		return NULL;
	}
	res->loadTexture = SDL_CreateTextureFromSurface(res->loadRenderer,
			loadingSurface);
	if (res->loadTexture == NULL) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create active_load.bmp texture\n");
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);

	//slots buttons
	for (int i = 0; i < NUM_SLOTS; i++) {

		loadingSurface = SDL_LoadBMP(slot_num(i));
		if (loadingSurface == NULL) {
			spLoadWindowDestroy(res);
			printf("couldn't create slot_num%d.bmp surface\n", i);
			return NULL;
		}
		res->slotsTexture[i] = SDL_CreateTextureFromSurface(res->loadRenderer,
				loadingSurface);
		if (res->slotsTexture[i] == NULL) {
			SDL_FreeSurface(loadingSurface);
			spMainWindowDestroy(res);
			printf("couldn't create slot_num%d.bmp texture\n", i);
			return NULL;
		}
		SDL_FreeSurface(loadingSurface);
	}

	res->slotPicked = -1;
	return res;
}

void spLoadWindowDestroy(SPCHESSLoadWin* src) {
	if (!src)
		return;

	if (src->backTexture != NULL)
		SDL_DestroyTexture(src->backTexture);

	if (src->loadTexture != NULL)
		SDL_DestroyTexture(src->loadTexture);

	if (src->inactiveLoadTexture != NULL)
		SDL_DestroyTexture(src->inactiveLoadTexture);

	for (int i = 0; i < NUM_SLOTS; i++) {
		if (src->slotsTexture[i] != NULL)
			SDL_DestroyTexture(src->slotsTexture[i]);
	}

	if (src->loadRenderer != NULL)
		SDL_DestroyRenderer(src->loadRenderer);

	if (src->loadWindow != NULL)
		SDL_DestroyWindow(src->loadWindow);

	free(src);
}

void spLoadWindowDraw(SPCHESSLoadWin* src) {
	if (!src)
		return;

	SDL_SetRenderDrawColor(src->loadRenderer, 255, 255, 255, 255);
	SDL_RenderClear(src->loadRenderer);

	SDL_Rect backR = { .x = 75, .y = 500, .h = 100, .w = 250 };
	SDL_Rect loadR = { .x = 400, .y = 500, .h = 100, .w = 250 };

	int numOfSlotsToDraw = countSavedFiles();
	for (int i = 0; i < numOfSlotsToDraw; i++) {
		SDL_Rect slotR = { .x = 240, .y = 100 + 150 * i, .h = 100, .w = 250 };
		SDL_RenderCopy(src->loadRenderer, src->slotsTexture[i], NULL, &slotR);
	}
	SDL_RenderCopy(src->loadRenderer, src->backTexture, NULL, &backR);
	if (src->slotPicked >= 0)
		SDL_RenderCopy(src->loadRenderer, src->loadTexture, NULL, &loadR);
	else
		SDL_RenderCopy(src->loadRenderer, src->inactiveLoadTexture, NULL,
				&loadR);

	SDL_RenderPresent(src->loadRenderer);
}

SPCHESS_LOAD_EVENT spLoadWindowHandleEvent(SPCHESSLoadWin* src,
		SDL_Event* event) {
	if (!src || !event)
		return SPCHESS_MAIN_INVALID_ARGUMENT;

	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnBack(event->button.x, event->button.y))
			return SPCHESS_LOAD_BACK;
		else if (isClickOnSlot(event->button.x, event->button.y) > 0) {
			src->slotPicked = isClickOnSlot(event->button.x, event->button.y) - 1;
			return SPCHESS_LOAD_SLOT;
		} else if (isClickOnLoad(event->button.x, event->button.y)
				&& src->slotPicked >= 0)
			return SPCHESS_LOAD_LOAD;
		break;

	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE)
			return SPCHESS_LOAD_QUIT;
		break;
	default:
		return SPCHESS_LOAD_NONE;
	}
	return SPCHESS_LOAD_NONE;

}

void spLoadWindowHide(SPCHESSLoadWin* src) {
	SDL_HideWindow(src->loadWindow);
}

void spLoadWindowShow(SPCHESSLoadWin* src) {
	SDL_ShowWindow(src->loadWindow);
}

int isClickOnBack(int x, int y) {
	if ((x >= 75 && x <= 75 + 250) && (y >= 500 && y <= 500 + 100)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot(int x, int y) {
	int numOfSlotsToDraw = countSavedFiles();
	for (int i = 0; i < numOfSlotsToDraw; i++) {
		if ((x >= 240 && x <= 250)
				&& (y >= (100 + 150 * i) && y <= (100 + 150 * i) + 100))
			return i + 1;
	}
	return 0;
}

int isClickOnLoad(int x, int y) {
	if ((x >= 400 && x <= 400 + 250) && (y >= 500 && y <= 500 + 100))
		return 1;

	return 0;
}

