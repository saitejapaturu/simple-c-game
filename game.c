/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Sri arrowHiti Teja Paturu
 * Student number: s3644335
 */
#include "game.h"

/* Used in tokeniarrowHittion. */

/*
 * 6 is the maximum space possible as a valid input for loading.
 * Ex: "load 1"
 */
#define INPUT_MAX_LENGTH_FOR_LOADING 6

/*
 * 8 is the maximum space possible as a valid input for 
 * initialiarrowHittion.
 * Ex: "init 1,1"
 */
#define INPUT_MAX_LENGTH_FOR_INIT 8

/*
 * 11 is the maximum space possible as a valid input for moving
 * the player or shooting arrows.
 * Ex: "shoot north"
 */
#define INPUT_MAX_LENGTH_FOR_MOVE_OR_SHOOT 11

/*
 * Used in strol to convert text to the base 10..
 */
#define DEFAULT_BASE 10

/*
 * Used to play game play game and this method ends when 
 * either the player chooses to quit or is killed by wumpus/pit 
 * or kills the the wumpus and wins the game.
 */
void game_PlayGame()
{
	Board board;
	Player player;
	/*
	 * For randomising player's position for transporting by bats.
	 * Called here to get random value each time it's called.
	 */
	srand(0);
	
	printf("You can use the following commands to play the game:\n");

        printf("\nload <g>\n");
        printf(" g: number of the game board to load (either 1 or 2)\n");
        printf("init <x>,<y>\n");
        printf(" x: horizontal position of the player on the board (between"
				" 0 & 4)\n");
        printf(" y: vertical position of the player on the board (between "
				"0 & 4)\n");
        printf("north (or n)\n");
        printf("south (or s)\n");
        printf("east (or e)\n");
        printf("west (or w)\n");
        printf("quit\n");

        printf("\nPress enter to continue...");

        readRestOfLine();

		/*
    	 * This loop is exited when the player chooses quit, which returns
		 * FALSE or if the player is killed, or player kills the wumpus.
		 * If player chooses quit either in loadGame or initialisePlayer,
		 * the method returns FALSE and the loop is ended.
    	 */
        if(loadGame(board))
		{
			printf("Board successfully loaded\n");
			if(initialisePlayer(board, &player))
			{
				moveAndShootPlayer(board, &player);
			}
		}
}

/*
 * This function loads the baord specified by the 
 * user, using a helper method, or quit if the user
 * chooses to quit.
 */
Boolean loadGame(Board board)
{
	char load [INPUT_MAX_LENGTH_FOR_LOADING + EXTRA_SPACES];
	char *token;

    while(TRUE)
	{
        getInput("At this stage of the program only two commands are "
				"acceptable:\nload <g>\nquit\n\n", load, sizeof(load));

		token = strtok(load, " ");

		if(token == NULL){
			printInvalidInput();
			continue;
		}

		if(strcmp(token, COMMAND_QUIT) == 0){
			return FALSE;
		}

		else if(strcmp(token, COMMAND_LOAD) == 0){
			
			/* If the number is neither 1 or 2 or any any error.*/
			if(!getBoardNumber(token, load, board))	{
				printInvalidInput();
				continue;
			}

			else
				return TRUE;
		}

		else{
			printInvalidInput();
				continue;
		}
    }
}

/*
 * Initialises the player onto the board based on user input
 * using helper method.
 */
Boolean initialisePlayer(Board board, Player *player)
{
 	char init [INPUT_MAX_LENGTH_FOR_INIT + EXTRA_SPACES];
	char *token;

	while(TRUE)
	{
		getInput("\nAt this stage of the program, only two commands are "
				"acceptable:\ninit <x>,<y>\nquit\n\n", init, sizeof(init));

		token = strtok(init, " ");
		if(token == NULL){
			printInvalidInput();
			continue;
		}

		/*
		 * If the first word the user types is quit returns FALSE,
		 * if it's init with appropeiate cooardinates then it
		 * initialises the player and returns TRUE.
		 * If it's anything the loop continues.
		 */
		if(strcmp(token, COMMAND_QUIT) == 0){
			return FALSE;
		}
		
		else if(strcmp(token, COMMAND_INIT) == 0){
			if(!getInitialPosition(token, init, player)){
				printInvalidInput();
				continue;
			}

			if(board_PlacePlayer(board, player->position) == FALSE){
				printf("Unable to place player at that position.\n");
				continue;
			}
			else{
				player_Initialise(player, player->position);
				break;
			}
		}

		else{
			printInvalidInput();
				continue;
		}
	}
	return TRUE;
}

/*
 * Moves the player or shoots arrows in specified direction.
 * This method keeps on looping until player is killed or
 * kills the wumpus or if the player chooses to quits.
 */
void moveAndShootPlayer(Board board, Player *player)
{
	char command [INPUT_MAX_LENGTH_FOR_MOVE_OR_SHOOT + EXTRA_SPACES];
	char *token;
	Direction newDirection;
	while(TRUE){
	board_Display(board);
	board_DisplayWarnings(board, player->position);
	getInput("\nAt this stage of the program, only three commands are "
			"acceptable:\n <direction>\n shoot <direction>\n quit\nWhere "
			"<direction> is one of: north,n,south,s,east,e,west,w\n\nPlease "
			"enter your choice: ", command, sizeof(command));

	token = strtok(command, " ");
		if(token == NULL){
			printInvalidInput();
			continue;
		}

		if(strcmp(token, COMMAND_QUIT) == 0)
			return;

		else if( getDirection (token, &newDirection) ){
			if(!movePlayer(board, player, newDirection))
				break;
		}
		
		else if(strcmp(token, COMMAND_SHOOT) == 0){
			token = strtok(NULL, "");
			if(token == NULL){
				printInvalidInput();
				continue;
			}

			else if( getDirection (token, &newDirection) ){
				if(shootArrow(board, player, newDirection))
					return;
			}

			else{
				printInvalidInput();
				continue;
			}
		}

		else{
			printInvalidInput();
			continue;
		}
	}
}

/*
 * This method is a helper method to loadBoard, it checks the board
 * number given by user and loads it.
 * If the user chooses to something other than 1 or 2 returns FALSE,
 * else if user chooses 1 or 2 returns TRUE.
 */
Boolean getBoardNumber(char * token, char * load, Board board)
{
	int l;
	char * end;

	token = strtok(NULL, "");
	if(token == NULL)
		return FALSE;
	
	l = strtol(token, &end, DEFAULT_BASE);
	if(token == end || *end != '\0')
		return FALSE;

	else if (l == 1 ){
		board_Load(board, BOARD_1);
		return TRUE;
	}

	else if (l == 2){
		board_Load(board, BOARD_2);
		return TRUE;
	}

	/* If l is not 1 or 2. */
	else
		return FALSE;
}

/*
 * This method is a helper method to  initialisePlayer.
 * This method is called when user chooses init and
 * his coordinates.
 * It checks the cooardinates sepcified by user and
 * returrns TRUE if the location is valid or
 * returns FALSE if it's not valid.
 */
Boolean getInitialPosition(char * token, char * init, Player *player)
{
	int x, y;
	char * end;

	token = strtok(NULL, ",");
	if(token == NULL){
		return FALSE;
	}

	x = strtol(token, &end, DEFAULT_BASE);
	if(token == end || *end != '\0' || x<0 || x>= BOARD_WIDTH){
		return FALSE;
	}

	token = strtok(NULL, "");
	if(token == NULL){
		return FALSE;
	}

	y = strtol(token, &end, DEFAULT_BASE);
	if(token == end || *end != '\0' || y<0 || y>= BOARD_HEIGHT){
		return FALSE;
	}

	player->position.x = x;
	player->position.y = y;

	/* Tells above function position is valid by returning TRUE*/
	return TRUE;
}

/*
 * This method is a helper method to moveAndShootPlayer which
 * moves the player based on the direction specified.
 * If the player ends up in a pit or wumpus and dies,
 * returns FALSE to tell the above function player died.
 */
Boolean movePlayer(Board board, Player *player, Direction direction)
{
	Position nextPosition = player_GetNextPosition(player->position, 
							direction);
	PlayerMove playerMove = board_MovePlayer(board, 
							player->position, nextPosition);

	if(playerMove == board_OUTSIDE_BOUNDS){
        printf("\nUnable to move - outside bounds.\n\n");
		return TRUE;
	}

	else if(playerMove == board_BAT_CELL){
	 batTransportation(board, player);
		printf("\nBat cell!\n\n");
		return TRUE;
	}

	else if(playerMove == board_PLAYER_KILLED){
        printf("\nPlayer killed! \n\n");
		/* Tells above function player was killed by returning FALSE*/
		return FALSE;
	}

/*This else is for player moved,i.e if(playerMove == board_PLAYER_MOVED)*/
	else {
		player_UpdatePosition(player, nextPosition);
		printf("\nPlayer moved.\n\n");
		return TRUE;
	}

}

/*
 * This method is a helper method to moveAndShootPlayer which
 * shoots the arrow based on the direction specified.
 * If the player ends up killing wumpus and wins,
 * returns TRUE to tell the above function player won.
 */
Boolean shootArrow(Board board, Player *player, Direction direction)
{
	if(player->numArrows > 0){
		Position shootPosition = player_GetNextPosition(player->position,
								 direction);
		ArrowHit arrowHit = board_FireArrow(board,
								 shootPosition);

		if(arrowHit == board_ARROW_OUTSIDE_BOUNDS){
			printf("Unable to fire arrow in that direction.\n\n");
			return FALSE;
		}

		else if(arrowHit == board_WUMPUS_KILLED){
			player->numArrows--;
			printf("You killed the Wumpus!\n\n");

			/* Tell above function WUMPUS was killed by returning TRUE*/
			return TRUE;
		}

		else{
			player->numArrows--;
			printf("Missed. You now have %d arrows\n\n", player->numArrows);
			return FALSE;
		}
	}

	else{
		printf("You don’t have any arrows to fire.\n\n");
		return FALSE;
	}
}

/*
 * This method is a helper method to moveAndShootPlayer which
 * changes the direction whose address is given as a paramter
 * to the direction specified by the player.
 * If the it doesn't match any direction returns FALSE.
 */
Boolean getDirection(char * token, Direction * direction)
{
	if( (strcmp(token, COMMAND_NORTH) == 0) || 
		(strcmp(token, COMMAND_NORTH_SHORTCUT) == 0) ){
			*direction = player_NORTH;
			return TRUE;
		}
		
	else if( (strcmp(token, COMMAND_SOUTH) == 0) || 
			 (strcmp(token, COMMAND_SOUTH_SHORTCUT) == 0) ){
			*direction = player_SOUTH;
			return TRUE;
		}

	else if( (strcmp(token, COMMAND_EAST) == 0) || 
			 (strcmp(token, COMMAND_EAST_SHORTCUT) == 0) ){
			*direction = player_EAST;
			return TRUE;
		}

	else if( (strcmp(token, COMMAND_WEST) == 0) || 
			 (strcmp(token, COMMAND_WEST_SHORTCUT) == 0) ){
			*direction = player_WEST;
			return TRUE;
		}

	else
		return FALSE;
}

/*
 * This method is used to transport the player to a random location
 * on the board which is either empty or Traversed.
 */
void batTransportation(Board board, Player *player)
{
	Position newPosition;

	/*
	 * Gets a random position until the cell is either empty or
	 * traversed.
	 */
	while(TRUE){	
		newPosition.x = rand() % BOARD_WIDTH;
		newPosition.y = rand() % BOARD_HEIGHT;
 
		if(board_MovePlayer(board, player->position, newPosition) 
			== board_PLAYER_MOVED){
			player_UpdatePosition(player, newPosition);
			break;
		}
	}
}
