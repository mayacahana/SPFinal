/*
 * SPCHESSGUILoadWin.h
 *
 *  Created on: 8 בספט׳ 2017
 *      Author: uri
 */

#ifndef GRAPHICS_SPCHESSGUILOADWIN_H_
#define GRAPHICS_SPCHESSGUILOADWIN_H_
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_SLOTS 5
#define slot_num(i) "./graphics/images/slot_num#i.bmp"

const char* saved_files[NUM_SLOTS] = { "./graphics/saved_games/save0.xml",
		"./graphics/saved_games/save1.xml", "./graphics/saved_games/save2.xml",
		"./graphics/saved_games/save3.xml", "./graphics/saved_games/save4.xml" };

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
	SDL_Texture* backTexture;
	SDL_Texture* loadTexture;
	SDL_Texture* inactiveLoadTexture;
	SDL_Texture* slotsTexture[NUM_SLOTS];
	bool slotWasClicked;
} SPCHESSLoadWin;

SPCHESSLoadWin* spLoadWindowCreate();
void spLoadWindowDestroy(SPCHESSLoadWin* src);
void spLoadWindowDraw(SPCHESSLoadWin* src);
SPCHESS_LOAD_EVENT spLoadWindowHandleEvent(SPCHESSLoadWin* src, SDL_Event* event);
void spLoadWindowHide(SPCHESSLoadWin* src);
void spLoadWindowShow(SPCHESSLoadWin* src);

int countSavedFiles();
int isClickOnLoad(int x, int y);
int isClickOnBack(int x, int y);
int isClickOnSlot(int x, int y);

#endif /* GRAPHICS_SPCHESSGUILOADWIN_H_ */
