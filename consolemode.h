#ifndef CONSOLEMODE_H_
#define CONSOLEMODE_H_

#include "SPCHESSMainAux.h"

#define SP_BUFF_SET() { \
	setvbuf(stdout, NULL, _IONBF, 0); \
	setvbuf(stderr, NULL, _IONBF, 0); \
	setvbuf(stdin, NULL, _IONBF, 0); \
}

/*
 * main console mode - run console mode by first
 * showing setting state and then moving to game state.
 */
int activeconsole();

#endif /* CONSOLEMODE_H_ */
