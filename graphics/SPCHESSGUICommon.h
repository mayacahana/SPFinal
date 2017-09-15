/*
 * SPCHESSGUICommon.h
 *
 *  Created on: 12 בספט׳ 2017
 *      Author: uri
 */

#ifndef GRAPHICS_SPCHESSGUICOMMON_H_
#define GRAPHICS_SPCHESSGUICOMMON_H_

#include "SPCHESSGUIButton.h"
#include "../SPCHESSMainAux.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ACT_IMG(g) "./graphics/images/"#g".bmp"
#define INACT_IMG(g) "./graphics/images/inactive_"#g".bmp"
#define BUTTON_W 150
#define BUTTON_H 50
#define NUM_SLOTS 5

const char* saved_files[NUM_SLOTS] = {
		"./graphics/saved_games/save0.xml", "./graphics/saved_games/save1.xml",
		"./graphics/saved_games/save2.xml", "./graphics/saved_games/save3.xml",
		"./graphics/saved_games/save4.xml" };


int countSavedFiles();
void promoteSlots();

SDL_Rect* spCopyRect(SDL_Rect* src);

SPCHESS_BUTTON_TYPE getButtonClicked(Button** btns, int numOfBtns,
		SDL_Event* event, bool checkActive);

#endif /* GRAPHICS_SPCHESSGUICOMMON_H_ */
