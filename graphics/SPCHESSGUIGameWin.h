/*
 * SPCHESSGUIGameWin.h
 *
 *  Created on: 13 בספט׳ 2017
 *      Author: uri
 */

#ifndef GRAPHICS_SPCHESSGUIGAMEWIN_H_
#define GRAPHICS_SPCHESSGUIGAMEWIN_H_

#include "SPCHESSGUICommon.h"
#define NUM_OF_GAME_BUTTONS 6
#define NUM_OF_DIFF_PIECES 6
#define PANEL_OFFSET 150
#define GUI_BOARD_SIZE 600

typedef enum {
	SPCHESS_GAME_RESTART,
	SPCHESS_GAME_SAVE,
	SPCHESS_GAME_LOAD,
	SPCHESS_GAME_UNDO,
	SPCHESS_GAME_MAIN_MENU,
	SPCHESS_GAME_EXIT,
	SPCHESS_GAME_QUIT,
	SPCHESS_GAME_MOVE,
	SPCHESS_GAME_PLAYER_1_CHECK,
	SPCHESS_GAME_PLAYER_2_CHECK,
	SPCHESS_GAME_PLAYER_1_CHECKMATE,
	SPCHESS_GAME_PLAYER_2_CHECKMATE,
	SPCHESS_GAME_TIE,
	SPCHESS_GAME_NONE,
	SPCHESS_GAME_INVALID_ARG
} SPCHESS_GAME_EVENT;

typedef struct spchessgamewin_t {
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	int numOfPanel;
	Button** panel;
	SDL_Texture* whitePieces[NUM_OF_DIFF_PIECES];
	SDL_Texture* blackPieces[NUM_OF_DIFF_PIECES];
	SDL_Texture* chessGrid;
	SPCHESSGame* game;
	bool isSaved;
	int chosenPiece[DIM];
} SPCHESSGameWin;


SPCHESSGameWin* spGameWindowCreate(SPCHESSGame* gameCopy);
void drawPieceByEntry(SPCHESSGameWin* src, SDL_Rect rec, int i, int j);
bool popUpSave();
bool isClickOnBoard(int x);
void computeLocFromGui(int from[DIM]);



void spGameWindowDraw(SPCHESSGameWin* src, SDL_Event* event);
void spGameWindowDestroy(SPCHESSGameWin* src);
void spGameWindowHide(SPCHESSGameWin* src);
void spGameWindowShow(SPCHESSGameWin* src);
SPCHESS_GAME_EVENT spGameWindowHandleEvent(SPCHESSGameWin* src, SDL_Event* event);
SPCHESS_GAME_EVENT checkStatusForUserGui(SPCHESSGameWin* src);
SPCHESS_GAME_EVENT spPanelHandleEvent(SPCHESSGameWin* src, SDL_Event* event);
SPCHESS_GAME_EVENT spStatusAfterMove(SPCHESS_GAME_EVENT msg);


#endif /* GRAPHICS_SPCHESSGUIGAMEWIN_H_ */