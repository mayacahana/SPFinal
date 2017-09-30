#ifndef SPCHESSMINIMAX_H_
#define SPCHESSMINIMAX_H_

#include "SPCHESSMiniMaxNode.h"
/**
 * Given a game state, this function evaluates the best move according to
 * the current player. The function initiates a MiniMax algorithm up to a
 * specified length given by maxDepth. The current game state doesn't change
 * by this function including the history of previous moves.
 *
 * @param currentGame - The current game state
 * @param maxDepth - The maximum depth of the miniMax algorithm
 * @return
 * -1 if either currentGame is NULL or maxDepth <= 0.
 * On success the function returns a move object
 * which is the best move for the current player.
 */
move* spChessMiniMaxSuggestMove(SPCHESSGame* src, unsigned int maxDepth);

#endif /* SPCHESSMINIMAX_H_ */
