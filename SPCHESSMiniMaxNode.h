/*
 * SPCHESSMiniMaxNode.h
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */
#ifndef SPCHESSMINIMAXNODE_H_
#define SPCHESSMINIMAXNODE_H_

#include "SPCHESSGame.h"

#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

int scoringFunc(SPCHESSGame* src, char currentPlayer);
int getPieceValue(char piece, char currentPlayer);

#endif /* SPCHESSMINIMAXNODE_H_ */
