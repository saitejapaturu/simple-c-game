/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Sri Sai Teja Paturu
 * Student number: s3644335
 */
#ifndef GAME_H
#define GAME_H

#include "helpers.h"
#include "board.h"
#include "player.h"

#define COMMAND_LOAD "load"
#define COMMAND_INIT "init"
#define COMMAND_NORTH "north"
#define COMMAND_NORTH_SHORTCUT "n"
#define COMMAND_SOUTH "south"
#define COMMAND_SOUTH_SHORTCUT "s"
#define COMMAND_EAST "east"
#define COMMAND_EAST_SHORTCUT "e"
#define COMMAND_WEST "west"
#define COMMAND_WEST_SHORTCUT "w"
#define COMMAND_SHOOT "shoot"
#define COMMAND_QUIT "quit"

/**
 * Main menu option 1 - play the game as per the specification.
 *
 * This function makes all the calls to board & player and handles interaction
 * with the user (reading input from the console, error checking, etc...).
 *
 * It should be possible to break this function down into smaller functions -
 * but this is up to you to decide and is entirely your own design. You can
 * place the additional functions in this header file if you want.
 *
 * Note that if you don't break this function up it could become pretty big...
 * and marks are allocated to good coding practices.
 */

void game_PlayGame();

/*
 * Function: loadGame
 * 
 *   This function takes board as a parameter
 *   
 *   Loads the baord specified by the user's input
 *
 *   returns: TRUE  if board loads successfully.
 *            FALSE if player chooses to quit.
 */
Boolean loadGame(Board board);

/*
 * Function: initialisePlayer
 * 
 *   This function takes board and pointer to player
 *   as parameters.
 *   
 *   Initialises the player's position on the given board
 *   to a location specified by the user's input.
 *
 *   returns: TRUE  if initialised successfully.
 *            FALSE if player chooses to quit.
 */
Boolean initialisePlayer(Board board, Player *player);

/*
 * Function: moveAndShootPlayer
 * 
 *   This function takes board and pointer to player
 *   as parameters.
 *   
 *   Moves the player's position to a location or
 *   shoots an arrow to a location on the
 *   given board based on the user's input.
 *
 *   Function ends when player is killed or
 *   player wins the game or
 *   user chooses to quit. 
 */
void moveAndShootPlayer(Board board, Player *player);

/*
 * Function: getBoardNumber
 * 
 *   This function takes board and pointers to 
 *   token and load as parameters.
 *   
 *   This function gets board number and loads it.
 *
 *   returns: TRUE  if board is loaded successfully.
 *            FALSE if user input is not valid.
 */
Boolean getBoardNumber(char * token, char * load, Board board);

/*
 * Function: getInitialPosition
 * 
 *   This function pointers to player,
 *   token and init as parameters.
 *   
 *   This function gets position specified by the user
 *   and assigns it to player if the position is valid.
 *
 *   returns: TRUE  if player position is initialised successfully.
 *            FALSE if player position is not valid.
 */
Boolean getInitialPosition(char * token, char * init, Player *player);

/*
 * Function: movePlayer
 * 
 *   This function takes board, direction and pointer to player
 *   as parameters.
 *   
 *   It moves the player to the specified direction
 *
 *   returns: TRUE  for landing on bats, player moving or if movng
 *                  outside bounds.
 *            FALSE if player is killed by either a wumpus or pit.
 *            
 */
Boolean movePlayer(Board board, Player *player, Direction direction);

/*
 * Function: shootArrow
 * 
 *   This function takes board, direction and pointer to player
 *   as parameters.
 *   
 *   It shoots the arrow in the specified direction
 *
 *   returns: TRUE if player kills the wumpus.
 *            TRUE for missing the arrows, player has no arrows
 *                 left to shoot, or shooting outside the board.
 */
Boolean shootArrow(Board board, Player *player, Direction direction);

/*
 * Function: getDirection
 * 
 *   This function takes pointers to token and direction
 *   as parameters.
 *   
 *   This function compares the user input for direction
 *   to the direction commands an dchanges the direction..
 *
 *   returns: TRUE  if direction is valid.
 *            FALSE if direction is not valid.
 */
Boolean getDirection (char * token, Direction * direction);

/*
 * Function: batTransportation
 * 
 *   This function takes board and pointer to player
 *   as parameters.
 *   
 *   Moves the player to a random position on the map,
 *   as long as that position is empty or traversed.
 *
 *   This function ends when the random position is valid
 *   and the player is moved.
 */
void batTransportation(Board board, Player *player);


#endif
