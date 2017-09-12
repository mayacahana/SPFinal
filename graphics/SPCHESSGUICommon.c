/*
 * SPCHESSGUICommon.c
 *
 *  Created on: 12 בספט׳ 2017
 *      Author: uri
 */

#include "SPCHESSGUICommon.h"
#include <stdlib.h>

SDL_Rect* spCopyRect(SDL_Rect* src) {
	if (src == NULL)
		return NULL;

	SDL_Rect* res = malloc(sizeof(SDL_Rect));
	if (res == NULL)
		return NULL;

	res->h = src->h;
	res->w = src->w;
	res->x = src->x;
	res->y = src->y;
	return res;
}

SPCHESS_BUTTON_TYPE getButtonClicked(Button** btns, int numOfBtns,
		SDL_Event* event, bool checkActive) {
	for (int i = 0; i < numOfBtns; i++) {
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;
		if (SDL_PointInRect(&point, btns[i]->location) && btns[i]->visible) {
			if (checkActive) {
				if (btns[i]->active)
					return btns[i]->type;
			}
			return btns[i]->type;
		}
	}
	return NO_BUTTON;
}
