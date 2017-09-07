/*
 * SPCHESSGUIMainWin.c
 *
 *  Created on: 7 בספט׳ 2017
 *      Author: uri
 */

#include "SPCHESSGUIMainWin.h"
#include <SDL2/SDL_video.h>
#include <stdio.h>

int isClickOnNewGame(int x, int y) {
	if ((x >= 75 && x <= 250) && (y >= 100 && y <= 200)) {
		return 1;
	}
	return 0;
}

int isClickOnExit(int x, int y) {
	if ((x >= 75 && x <= 250) && (y >= 400 && y <= 500)) {
		return 1;
	}
	return 0;
}

int isClickOnLoad(int x, int y) {
	if ((x >= 75 && x <= 250) && (y >= 250 && y <= 350)) {
		return 1;
	}
	return 0;
}

SPCHESSMainWin* spMainWindowCreate() {
	SPCHESSMainWin* res = NULL;
	SDL_Surface* loadingSurface = NULL;
	res = (SPCHESSMainWin*) calloc(sizeof(SPCHESSMainWin), sizeof(char));
	if (res == NULL)
		return NULL;

	res->mainWindow = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_OPENGL);

	if (res->mainWindow == NULL) {
		spMainWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}
	res->mainRenderer = SDL_CreateRenderer(res->mainWindow, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->mainRenderer == NULL) {
		spMainWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}
	//new game button
	loadingSurface = SDL_LoadBMP("./graphics/images/new_game.bmp");
	if (loadingSurface == NULL) {
		spMainWindowDestroy(res);
		printf("couldn't create new_game.bmp surface\n");
		return NULL;
	}
	res->newGameTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->newGameTexture == NULL) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create new_game.bmp texture\n");
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);

	//load button
	loadingSurface = SDL_LoadBMP("./graphics/images/load.bmp");
	if (loadingSurface == NULL) {
		spMainWindowDestroy(res);
		printf("couldn't create load.bmp surface\n");
		return NULL;
	}
	res->loadTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->loadTexture == NULL) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create load.bmp texture\n");
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);

	//exit button
	loadingSurface = SDL_LoadBMP("./graphics/images/exit.bmp");
	if (loadingSurface == NULL) {
		spMainWindowDestroy(res);
		printf("couldn't create exit.bmp surface\n");
		return NULL;
	}
	res->exitTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->exitTexture == NULL) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create exit.bmp texture\n");
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);

	return res;
}

void spMainWindowDestroy(SPCHESSMainWin* src) {
	if (!src)
		return;

	if (src->newGameTexture != NULL)
		SDL_DestroyTexture(src->newGameTexture);

	if (src->loadTexture != NULL)
		SDL_DestroyTexture(src->loadTexture);

	if (src->exitTexture != NULL)
		SDL_DestroyTexture(src->exitTexture);

	if (src->mainRenderer != NULL)
		SDL_DestroyRenderer(src->mainRenderer);

	if (src->mainWindow != NULL)
		SDL_DestroyWindow(src->mainWindow);

	free(src);
}

void spMainWindowDraw(SPCHESSMainWin* src) {
	if (src == NULL)
		return;

	SDL_Rect newGameR = { .x = 75, .y = 100, .h = 100, .w = 250 };
	SDL_Rect loadR = { .x = 75, .y = 250, .h = 100, .w = 250 };
	SDL_Rect exitR = { .x = 75, .y = 400, .h = 100, .w = 250 };
	SDL_SetRenderDrawColor(src->mainRenderer, 255, 255, 255, 255);
	SDL_RenderClear(src->mainRenderer);
	SDL_RenderCopy(src->mainRenderer, src->newGameTexture, NULL, &newGameR);
	SDL_RenderCopy(src->mainRenderer, src->loadTexture, NULL, &loadR);
	SDL_RenderCopy(src->mainRenderer, src->exitTexture, NULL, &exitR);
	SDL_RenderPresent(src->mainRenderer);
}

SPCHESS_MAIN_EVENT spMainWindowHandleEvent(SPCHESSMainWin* src, SDL_Event* event) {
	if (!event) {
		return SPCHESS_MAIN_INVALID_ARGUMENT;
	}

	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnNewGame(event->button.x, event->button.y))
			return SPCHESS_MAIN_NEW_GAME;
		else if (isClickOnLoad(event->button.x, event->button.y))
			return SPCHESS_MAIN_LOAD;
		else if(isClickOnExit(event->button.x, event->button.y))
			return SPCHESS_MAIN_EXIT;

		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE)
			return SPCHESS_MAIN_EXIT;
		break;
	default:
		return SPCHESS_MAIN_NONE;
	}
	return SPCHESS_MAIN_NONE;
}

void spMainWindowHide(SPCHESSMainWin* src) {
	SDL_HideWindow(src->mainWindow);
}

void spMainWindowShow(SPCHESSMainWin* src) {
	SDL_ShowWindow(src->mainWindow);
}

