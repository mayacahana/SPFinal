#ifndef SPCHESSFILEAUX_H_
#define SPCHESSFILEAUX_H_

#include "SPCHESSGame.h"

SPCHESSGame* getStateFromFile(char* path);
int saveGameToFile(char* path, SPCHESSGame* game);

void fillGameInfoParserLine(char* cleanLine, SPCHESSGame* src);

#endif /* SPCHESSFILEAUX_H_ */
