#ifndef SPCHESSMAINAUX_H_
#define SPCHESSMAINAUX_H_

#include "SPCHESSParser.h"
#include "SPCHESSFileAux.h"
#include "SPCHESSMiniMax.h"

#define SUCCESS 1
#define NOSUCCESS 0
/**
 * Sets the game settings to default one.
 * @param src - the source game
 */
void setDefaultSetting(SPCHESSGame* src);
/**
 * This function manage the setting mode according to the given command.
 * Handle with illegal commands or undefined input settings.
 * Sets the given settings params to the desired ones.
 * @param src - the game
 *
 */
void settingState(SPCHESSGame* src);
/**
 * Sets the game mode and prints a message accordingly.
 * @param src - the game
 * @param act - the setting command
 */
void setGameMode(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
/**
 * Sets the game's difficulty and prints a message accordingly.
 * @param src - the game
 * @param act - the setting command
 */
void setDifficulty(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
/**
 * Sets the user color and prints a message accordingly.
 * @param src - the game
 * @param act - the setting command
 */
void setUserColor(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
/**
 * Load into the src game the given game in the file.
 * @param src - the game (the target game)
 * @param act - the load command
 * @return
 * 1 if the command executed successfully, 0 otherwise.
 */
int setLoad(SPCHESSGame* src, SPCHESS_GAME_SETTINGS_Command act);
/**
 * Print the game's settings to console.
 * @param src - the game
 */
void printCurrentSetting(SPCHESSGame* src);
/**
 * Quit the game. free all the memory.
 * @param src - the game
 */
void quitGame(SPCHESSGame* src);
/**
 * Parser the input command and manging the game according to the command.
 * @param src - the game
 * @return
 * number indicate the type of the command.
 */
SPCHESS_COMMAND userTurn(SPCHESSGame* src);
/**
 * Executes the next user move. If not valid - prints a message accordingly.
 * @param src - the game
 * @param act - the command move to execute
 * @return
 * 1 in case of success, 0 otherwise
 */
int setUserMove(SPCHESSGame* src, SPCHESS_GAME_MODE_Command act);
/**
 * Checks if there is a winner, mate or tie in the game
 * following the input command. Prints a message accordingly
 * @param src - the game
 * @param act - the desired command
 */
void checkGameStatusForUser(SPCHESSGame* src, SPCHESS_GAME_MODE_Command act);
/**
 * Saving the game to the desired output file.
 * @param src - the game
 * @param act - the save command to execute
 * @return
 * 1 in case of success, 0 otherwise.
 */
int saveGame(SPCHESSGame* src, SPCHESS_GAME_MODE_Command act);
/**
 * Execute the undo command.
 * If not legal - prints a message accordingly.
 * @param src - the game
 * @return
 * 1 in case of success, 0 otherwise.
 */
int undoMove(SPCHESSGame* src);
/**
 * Reset the game to default settings, delete
 * any parameters of the current game.
 * @param src - the game
 */
void resetGame(SPCHESSGame* src);
/**
 * Helper function. prints a message to the next player
 * to play his move.
 * @param src -the game
 */
void printTurn(SPCHESSGame* src);
/**
 * Calculate the computer next move and print a message
 * according to the move that taken.
 * @param src - the game
 */
void computerTurn(SPCHESSGame* src);
/**
 * Checks if there is a winner, mate or tie in the game
 * Prints a message accordingly
 * @param src - the game
 */
void checkGameStatusForComputer(SPCHESSGame* src);
/**
 * Helper function. return the full name of the piece
 * following its MACRO definition.
 * @param piece - the piece's symbol
 * @return
 * the piece's full name.
 */
char* getNameFromPiece(char piece);

#endif /* SPCHESSMAINAUX_H_ */
