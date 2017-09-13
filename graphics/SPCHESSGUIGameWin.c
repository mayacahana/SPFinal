/*
 * SPCHESSGUIGameWin.c
 *
 *  Created on: 13 בספט׳ 2017
 *      Author: uri
 */
#include "SPCHESSGUIGameWin.h"

SPCHESSGameWin* spGameWindowCreate(SPCHESSGame* gameCopy) {
	SPCHESSGameWin* res = (SPCHESSGameWin*) calloc(sizeof(SPCHESSGameWin),
			sizeof(char));
	SDL_Surface* loadingSurfaceWhite = NULL; //Used as temp surface
	SDL_Surface* loadingSurfaceBlack = NULL; //Used as temp surface
	SDL_Surface* loadingSurfaceGrid = NULL; //loading surface grid
	if (res == NULL) {
		printf("Couldn't create spChessGameWin struct\n");
		return NULL;
	}
	res->gameWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, 750, 600, SDL_WINDOW_OPENGL);
	if (res->gameWindow == NULL) {
		spGameWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	res->gameRenderer = SDL_CreateRenderer(res->gameWindow, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->gameRenderer == NULL) {
		spGameWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	//create panel array
	res->numOfPanel = NUM_OF_GAME_BUTTONS;
	const char* activeImages[NUM_OF_GAME_BUTTONS] = { ACT_IMG(restart), ACT_IMG(
			save), ACT_IMG(load), ACT_IMG(undo), ACT_IMG(main_menu), ACT_IMG(
			exit) };

	const char* inactiveImages[NUM_OF_GAME_BUTTONS] = { INACT_IMG(restart),
			INACT_IMG(save), INACT_IMG(load), INACT_IMG(undo), INACT_IMG(
					main_menu), INACT_IMG(exit) };

	int xBtns[NUM_OF_GAME_BUTTONS] = { 50, 50, 50, 50, 50, 50 };
	int yBtns[NUM_OF_GAME_BUTTONS] = { 100, 250, 400, 550, 700, 850 };

	bool visible[NUM_OF_GAME_BUTTONS] = { true, true, true, true, true, true };

	bool active[NUM_OF_GAME_BUTTONS] = { true, true, true, false, true, true };

	SPCHESS_BUTTON_TYPE types[NUM_OF_GAME_BUTTONS] = { BUTTON_GAME_RESTART,
			BUTTON_GAME_SAVE, BUTTON_GAME_LOAD, BUTTON_GAME_UNDO,
			BUTTON_GAME_MAIN_MENU, BUTTON_GAME_EXIT };

	res->panel = createButtons(res->gameRenderer, activeImages, inactiveImages,
			xBtns, yBtns, visible, active, types, res->numOfPanel);

	if (res->panel == NULL) {
		SDL_DestroyRenderer(res->gameRenderer);
		SDL_DestroyWindow(res->gameWindow);
		free(res);
	}
	//Create a chess_board texture:
	loadingSurfaceGrid = SDL_LoadBMP(ACT_IMG("chess_grid"));
	if (loadingSurfaceGrid == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	res->chessGrid = SDL_CreateTextureFromSurface(res->gameRenderer,
			loadingSurfaceGrid);
	if (res->chessGrid == NULL) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_DestroyTexture(res->chessGrid);
		SDL_DestroyRenderer(res->gameRenderer);
		SDL_DestroyWindow(res->gameWindow);
		free(res);
		return NULL;
	}
	SDL_FreeSurface(loadingSurfaceGrid); //We finished with the surface -> delete it
	//create white & black pieces
	const char* whiteImages[NUM_OF_DIFF_PIECES] = { ACT_IMG(white_pawn),
			ACT_IMG(white_knight), ACT_IMG(white_bishop), ACT_IMG(white_rook),
			ACT_IMG(white_queen), ACT_IMG(white_king) };

	const char* blackImages[NUM_OF_DIFF_PIECES] = { ACT_IMG(black_pawn),
			ACT_IMG(black_knight), ACT_IMG(black_bishop), ACT_IMG(black_rook),
			ACT_IMG(black_queen), ACT_IMG(black_king) };

	for (int i = 0; i < NUM_OF_DIFF_PIECES; i++) {
		loadingSurfaceWhite = SDL_LoadBMP(whiteImages[i]);
		loadingSurfaceBlack = SDL_LoadBMP(blackImages[i]);
		if (loadingSurfaceWhite == NULL || loadingSurfaceBlack == NULL) {
			printf("Could not create a surface: %s\n", SDL_GetError());
			SDL_FreeSurface(loadingSurfaceWhite);
			SDL_FreeSurface(loadingSurfaceBlack);
			for (int k = 0; k < i; k++) {
				SDL_DestroyTexture(res->whitePieces[k]);
				SDL_DestroyTexture(res->blackPieces[k]);
			}
			SDL_DestroyTexture(res->chessGrid);
			destroyButtons(res->panel, res->numOfPanel);
			SDL_DestroyRender(res->gameRenderer);
			SDL_DestroyWindow(res->gameWindow);
			free(res);
			return NULL;
		}
		res->whitePieces[i] = SDL_CreateTextureFromSurface(res->gameRenderer,
				loadingSurfaceWhite);
		res->blackPieces[i] = SDL_CreateTextureFromSurface(res->gameRenderer,
				loadingSurfaceBlack);
		if (res->whitePieces[i] == NULL || res->blackPieces[i] == NULL) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			SDL_FreeTexture(res->whitePieces[i]);
			SDL_FreeTexture(res->blackPieces[i]);
			for (int k = 0; k < i; k++) {
				SDL_DestroyTexture(res->whitePieces[k]);
				SDL_DestroyTexture(res->blackPieces[k]);
			}
			SDL_DestroyTexture(res->chessGrid);
			destroyButtons(res->panel, res->numOfPanel);
			SDL_DestroyRender(res->gameRenderer);
			SDL_DestroyWindow(res->gameWindow);
			free(res);
			return NULL;
		}
		SDL_FreeSurface(loadingSurfaceWhite);
		SDL_FreeSurface(loadingSurfaceBlack);
	}
	res->game = spChessGameCopy(gameCopy); //copy the of the game sent
	res->isSaved = false; //the game is not saved yet
	return res;
}

void spGameWindowDestroy(SPCHESSGameWin* src) {
	if (!src)
		return;

	if (src->game != NULL)
		spChessGameDestroy(src->game);

	if (src->panel != NULL)
		destroyButtons(src->panel);

	if (src->chessGrid != NULL)
		SDL_DestroyTexture(src->chessGrid);

	for (int i = 0; i < NUM_OF_DIFF_PIECES; i++) {
		if (src->whitePieces[i] != NULL && src->blackPieces[i] != NULL) {
			SDL_DestroyTexture(src->whitePieces[i]);
			SDL_DestroyTexture(src->blackPieces[i]);
		}
	}

	if (src->gameRenderer != NULL)
		SDL_DestroyRenderer(src->gameRenderer);

	if (src->gameWindow != NULL)
		SDL_DestroyWindow(src->gameWindow);

	free(src);
}

void spGameWindowDraw(SPCHESSGameWin* src) {
	if (src == NULL)
		return;

	SDL_SetRenderDrawColor(src->gameRenderer, 255, 255, 255, 255);
	SDL_RenderClear(src->gameRenderer);

	for (int i = 0; i < src->numOfPanel; i++)
		drawButton(src->panel[i]);

	SDL_Rect rec = { .x = 150, .y = 0, .w = 600, .h = 600 }; //rect of chess_grid
	SDL_RenderCopy(src->gameRenderer, src->chessGrid, NULL, &rec);

	//fill the board acoording to pieces
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			rec.x = 150 + j * (600 / BOARD_SIZE);
			rec.y = (600 / BOARD_SIZE) * (BOARD_SIZE - 1 - i);
			rec.h = (600 / BOARD_SIZE);
			rec.w = (600 / BOARD_SIZE);
			if (src->game->gameBoard[i][j] != EMPTY)
				drawPieceByEntry(SPCHESSGameWin * src, rec, i, j);
		}
	}
	SDL_RenderPresent(src->gameRenderer);
}

void drawPieceByEntry(SPCHESSGameWin* src, SDL_Rect rec, int i, int j) {
	if (!src)
		return;

	char piece = src->game->gameBoard[i][j];
	switch (piece) {
	case WHITE_P:
		SDL_RenderCopy(src->gameRenderer, src->whitePieces[0], NULL, &rec);
		break;
	case BLACK_P:
		SDL_RenderCopy(src->gameRenderer, src->blackPieces[0], NULL, &rec);
		break;
	case WHITE_B:
		SDL_RenderCopy(src->gameRenderer, src->whitePieces[2], NULL, &rec);
		break;
	case BLACK_B:
		SDL_RenderCopy(src->gameRenderer, src->blackPieces[2], NULL, &rec);
		break;
	case WHITE_R:
		SDL_RenderCopy(src->gameRenderer, src->whitePieces[3], NULL, &rec);
		break;
	case BLACK_R:
		SDL_RenderCopy(src->gameRenderer, src->blackPieces[3], NULL, &rec);
		break;
	case WHITE_N:
		SDL_RenderCopy(src->gameRenderer, src->whitePieces[1], NULL, &rec);
		break;
	case BLACK_N:
		SDL_RenderCopy(src->gameRenderer, src->blackPieces[1], NULL, &rec);
		break;
	case WHITE_Q:
		SDL_RenderCopy(src->gameRenderer, src->whitePieces[4], NULL, &rec);
		break;
	case BLACK_Q:
		SDL_RenderCopy(src->gameRenderer, src->blackPieces[4], NULL, &rec);
		break;
	case WHITE_K:
		SDL_RenderCopy(src->gameRenderer, src->whitePieces[5], NULL, &rec);
		break;
	case BLACK_K:
		SDL_RenderCopy(src->gameRenderer, src->blackPieces[5], NULL, &rec);
		break;
	}
}

SPCHESS_GAME_EVENT spGameWindowHandleEvent(SPCHESSGameWin* src,
		SDL_Event* event) {
	if (!src || !event)
		return SPCHESS_GAME_INVALID_ARG; //check to return invalid argument

	//check game state for undo btn
	if(src->game->gameMode == 2)
		src->panel->active[3] = false; //game mode is 2, de-activate undo btn
	else if(!spArrayListIsEmpty(src->game->movesPlayer1))
		src->panel->active[3] = true; //there is history, activate undo btn

	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		SPCHESS_BUTTON_TYPE btn = getButtonClicked(src->panel, src->numOfPanel,
				event, true);

		if (btn == BUTTON_GAME_RESTART) {
			spChessGameRestart(src->game); //restart the game with current settings
			src->panel->active[3] = false; //de-activate undo btn
			src->isSaved = false;
			return SPCHESS_GAME_RESTART;
		} else if (btn == BUTTON_GAME_SAVE) {
			promoteSlots();
			if(saveGameToFile(saved_files[0], src->game) == -1)
				// show error message ?
			src->isSaved = true;
			return SPCHESS_GAME_SAVE;
		} else if (btn == BUTTON_GAME_LOAD) {
			return SPCHESS_GAME_LOAD;

		} else if (btn == BUTTON_GAME_UNDO) {

			spChessGameUndoPrevMove(src->game);
			spChessGameUndoPrevMove(src->game);
			//if there is no history, de-activate undo btn
			if(spArrayListIsEmpty(src->game->movesPlayer1))
				src->panel->active[3] = false;
			src->isSaved = false;
			return SPCHESS_GAME_UNDO;
		} else if (btn == BUTTON_GAME_MAIN_MENU) {
			if(src->isSaved == false)
				//show SDL_ShowMessageBox asking the user if he wants to save
			return SPCHESS_GAME_MAIN_MENU;
		} else if (btn == BUTTON_GAME_EXIT) {
			if(src->isSaved == false)
				//show SDL_ShowMessageBox asking the user if he wants to save
			return SPCHESS_GAME_EXIT;
		}
			break;

	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE)
			return SPCHESS_SET_QUIT;
		break;
	default:
		return SPCHESS_GAME_NONE;
	}
	return SPCHESS_SET_NONE;
}

void spGameWindowHide(SPCHESSGameWin* src) {
	SDL_HideWindow(src->gameWindow);
}

void spGameWindowShow(SPCHESSGameWin* src) {
	SDL_ShowWindow(src->gameWindow);
}

