/*
 * SPCHESSMiniMaxNode.h
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */
#ifndef SPCHESSMINIMAXNODE_H_
#define SPCHESSMINIMAXNODE_H_

#include "SPCHESSGame.h"
#include <limits.h>

#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))
/**
 *
 */
int scoringFunc(SPCHESSGame* src, char currentPlayer);
/**
 * This function return the score of a specific soldier, given the char
 * that represent it, and the current player of the game.
 * @param piece - the char
 * @param currentPlayer - the current player
 * @return
 * The score of the soldier. defined by the instructions.
 */
int getPieceValue(char piece, char currentPlayer);
/**
 * This function computes the node's score, meaning given the current game,
 * the max recursion depth, the alpha and the color represent the current player
 * function evaluates the score of the game.
 * The function initiates a MiniMax algorithm up to a specified length given by the maxRecLvl param.
 * @param src - the game
 * @param maxRecLvl - the depth for the minimax. the maximum recursion level
 * @param alpha - alpha parameter for the minimax
 * @param beta - beta parameter for the minimax
 * @param flag - if the flag equals TRUE, take a MAX between elems
 * @param colorForFunc - represent the color of the current player the minimax is calculated for
 * @return
 *  -4000 if the current player is losing
 *  4000 if the current player is the winner of this game state
 *  0 if there is a tie
 *  Otherwise, the function returns the board's score of the current player.
 */
int computeValueRec(SPCHESSGame* src, int maxRecLvl, int alpha, int beta, bool flag, char colorForFunc);
/**
 * Helper function. decide whether to take the max or min
 * between the value and curr
 * @param value
 * @param curr
 * @param flag
 * @return
 * if the flag is True, return MAX(curr,value), otherwise return MIN(curr,value)
 */
int decider(int value, int curr, bool flag);


#endif /* SPCHESSMINIMAXNODE_H_ */
