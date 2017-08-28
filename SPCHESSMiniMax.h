/*
 * SPCHESSMiniMax.h
 *
 *  Created on: 15 באוג׳ 2017
 *      Author: uri
 */
#ifndef SPCHESSMINIMAX_H_
#define SPCHESSMINIMAX_H_

#include "SPChessMiniMaxNode.h"

move* spChessMiniMaxSuggestMove(SPCHESSGame* src, unsigned int maxDepth);

#endif /* SPCHESSMINIMAX_H_ */
