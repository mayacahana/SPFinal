#ifndef SPCHESSFILEAUX_H_
#define SPCHESSFILEAUX_H_

#include "SPCHESSGame.h"
/**
 * Loading the game from the XML file,
 * according to the given pattern.
 * @param path - the input xml path
 * @return
 * The game object
 */
SPCHESSGame* getStateFromFile(char* path);
/**
 * Saving the game to the XML file.
 * @param path - the path to the output file
 * @param game - the current game to save
 * @return
 * 0 in case of success(the game has been saved), -1 otherwise.
 */
int saveGameToFile(char* path, SPCHESSGame* game);
/**
 * Helper function to the load game.
 * Extracting the info from the file, according to the
 * current label and save the data to the game's specifications.
 * @param cleanLine - the current line to execute
 * @param src - the game
 */
void fillGameDataDueToLine(char* cleanLine, SPCHESSGame* src);

#endif /* SPCHESSFILEAUX_H_ */
