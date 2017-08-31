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
#define SUCCESS 1
#define FAIL 0

void setDefaultSetting(SPCHESSGame* src);
void settingState(SPCHESSGame* src);
void setGameMode(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
void setDifficulty(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
void setUserColor(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
int setLoad(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
void printCurrentSetting(SPCHESSGame* src);
void quitGame(SPCHESSGame* src);

void userTurn(SPCHESSGame* src);
int setUserMove(SPCHESSGame* src, SPCHESS_GAME_MODE_Command act);
void checkGameStatusForUser(SPCHESSGame* src);
int saveGame(SPCHESSGame* src, SPCHESS_GAME_MODE_Command act);
int undoMove(SPCHESSGame* src);
void resetGame(SPCHESSGame* src);

void computerTurn(SPCHESSGame* src);
void checkGameStatusForComputer(SPCHESSGame* src);
char* getNameFromPiece(char piece);



#endif /* SPCHESSMAINAUX_H_ */
