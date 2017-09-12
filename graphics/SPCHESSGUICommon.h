/*
 * SPCHESSGUICommon.h
 *
 *  Created on: 12 בספט׳ 2017
 *      Author: uri
 */

#ifndef GRAPHICS_SPCHESSGUICOMMON_H_
#define GRAPHICS_SPCHESSGUICOMMON_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "../SPCHESSMainAux.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define ACT_IMG(g) "./graphics/images/"#g".bmp"
#define INACT_IMG(g) "./graphics/images/inactive_"#g".bmp"

#define BUTTON_W 250
#define BUTTON_H 100


SDL_Rect* spCopyRect(SDL_Rect* src);

SPCHESS_BUTTON_TYPE getButtonClicked(Button** btns, int numOfBtns, SDL_Event* event, bool checkActive);

#endif /* GRAPHICS_SPCHESSGUICOMMON_H_ */
