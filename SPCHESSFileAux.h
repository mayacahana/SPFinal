/*
 * SPCHESSFileAux.h
 *
 *  Created on: Aug 22, 2017
 *      Author: mayacahana
 */


#ifndef SPCHESSFILEAUX_H_
#define SPCHESSFILEAUX_H_

#include "SPCHESSGame.h"

SPCHESSGame* getStateFromFile(char* path);
int saveGameToFile(char* path, SPCHESSGame* game);

void getNextTag(FILE* in, char nextTag[13]);
void getNextValue(FILE* in, char nextValue[6]);

#endif /* SPCHESSFILEAUX_H_ */
