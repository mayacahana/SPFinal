/*
 * main.c
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: uri
 */
#include "consolemode.h"
#include "./graphics/guimode.h"

int main(int argc, char* argv[]) {

	if(argc == 2 && strcmp(argv[1], "-c") == 0)  //CONSOLE MODE
		return activeconsole();
	else if(argc == 2 && strcmp(argv[1], "-g") == 0) //GUI MODE
		return activegui();
	else if(argc == 1) //DEFAULT MODE - CONSOLE
		return activeconsole();

	return 0;
}

