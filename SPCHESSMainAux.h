/*
 * SPCHESSMainAux.h
 *
 *  Created on: 29 באוג׳ 2017
 *      Author: uri
 */
#ifndef SPCHESSMAINAUX_H_
#define SPCHESSMAINAUX_H_

#include "SPCHESSParser.h"
#include "SPCHESSFileAux.h"
#include "SPCHESSMiniMax.h"

#define SPCHESS_MAX_LINE_LENGTH 1024
#define DEFAULT_GAME_MODE 1
#define DEFAULT_DIFFICULTY 2
#define DEFAULT_USER_COLOR 1

void setDefaultSetting(SPCHESSGame* src);
void settingState(SPCHESSGame* src);
void setGameMode(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
void setDifficulty(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
void setUserColor(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
void setLoad(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
void printCurrentSetting(SPCHESSGame* src);
void quitGame(SPCHESSGame* src);



#endif /* SPCHESSMAINAUX_H_ */
