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
#define PANEL_OFFSET 200
#define GUI_BOARD_SIZE 650

/*
 * enum represents the diffrent game window events.
 */
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

/*
 * structure represents a game window. Beside regular params, it contains
 * flag indicates whether the game was saved,
 * and if there is a motion piece.
 */
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

/*
 * Create game window functions.
 */
SPCHESSGameWin* spGameWindowCreate(SPCHESSGame* gameCopy);
/*
 * The function draw the relavent image in rect location according to the
 * piece at the i-th j-th cell on the game board.
 */
void drawPieceByEntry(SPCHESSGameWin* src, SDL_Rect rec, int i, int j);
/*
 * The functions shows a pop-up message box asking the user if he wants to save the game before exiting,
 * and returns the user choice.
 */
int popUpSave();
bool isClickOnBoard(int x);
void computeLocFromGui(int loc[DIM]);

void spGameWindowDraw(SPCHESSGameWin* src, SDL_Event* event);
void spGameWindowDestroy(SPCHESSGameWin* src);
void spGameWindowHide(SPCHESSGameWin* src);
void spGameWindowShow(SPCHESSGameWin* src);
SPCHESS_GAME_EVENT spGameWindowHandleEvent(SPCHESSGameWin* src,
		SDL_Event* event);
SPCHESS_GAME_EVENT checkStatusForUserGui(SPCHESSGameWin* src);
SPCHESS_GAME_EVENT spPanelHandleEvent(SPCHESSGameWin* src, SDL_Event* event);
SPCHESS_GAME_EVENT spStatusAfterMove(SPCHESS_GAME_EVENT msg,
		SPCHESSGameWin* src, SDL_Event* event);

#endif /* GRAPHICS_SPCHESSGUIGAMEWIN_H_ */
