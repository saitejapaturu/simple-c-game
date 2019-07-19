/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Sri Sai Teja Paturu
 * Student number: s3644335
 */
#include "board.h"

Board BOARD_1 =
{
   	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_PIT,    board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY},
	{ board_BATS,   board_EMPTY,  board_EMPTY,  board_WUMPUS, board_EMPTY},
	{ board_EMPTY,  board_PIT,    board_EMPTY,  board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_BATS,   board_EMPTY,  board_EMPTY}
};

Board BOARD_2 =
{
	{ board_PIT,    board_EMPTY,  board_PIT,    board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_BATS,   board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY,  board_BATS },
	{ board_EMPTY,  board_WUMPUS, board_EMPTY,  board_EMPTY,  board_EMPTY},
};

/*
 * Loads the board to the specified board, either BOARD_1 or BOARD_2.
 */
void board_Load(Board board, Board boardToLoad) 
{
    /*
     * The for loops loop through each cell changing it based upon the
     * specified board to load.
     */
    int i,j;
    for (i=0; i<BOARD_HEIGHT; i++)
    {
        for (j=0; j<BOARD_WIDTH; j++)
        {
            board[i][j] = boardToLoad[i][j];
        }
    }
}

/*
 * Places the player on the board.
 */
Boolean board_PlacePlayer(Board board, Position position) 
{
    /*
     * Returns true only if the board cell of the specified 
     * location is empty.
     */

    if (board[position.y][position.x] == board_EMPTY){
        board[position.y][position.x] = board_PLAYER;
        return TRUE;
    }
    else
        return FALSE;
}

/*
 * Moves the specified player from current position to the 
 * specified nextPostion on the given board.
 */
PlayerMove board_MovePlayer(Board board, Position playerPosition, 
                            Position nextPosition)
{
    /*
     * Checks the board cell of the next position and
     * checks for bats, cells, wumpus, pit and out of bounds.
     * then returns the appropriate PlayerMove.
     */
    if(nextPosition.x < 0 || nextPosition.x >= BOARD_WIDTH || 
       nextPosition.y < 0 || nextPosition.x >= BOARD_HEIGHT)
        return board_OUTSIDE_BOUNDS;

    else if (board[nextPosition.y][nextPosition.x] == board_BATS)
        return board_BAT_CELL;

    else if (board[nextPosition.y][nextPosition.x] == board_PIT)
        return board_PLAYER_KILLED;

    else if (board[nextPosition.y][nextPosition.x] == board_WUMPUS)
        return board_PLAYER_KILLED;

    /*
     * Used in batTransportation method to make sure player doesn't 
     * get transported to the same position.
     */
    else if (board[nextPosition.y][nextPosition.x] == board_PLAYER)
        return board_OUTSIDE_BOUNDS;

    else{
        board[playerPosition.y][playerPosition.x] = board_TRAVERSED;
        board[nextPosition.y][nextPosition.x] = board_PLAYER;

        return board_PLAYER_MOVED;
    }
}

/*
 * Fire's arrows on the given board at the specified position 
 * and returns if the wumpus was killed or missed or if arrow 
 * was fired out of bounds.
 */
ArrowHit board_FireArrow(Board board, Position position) 
{
   if(position.x < 0 || position.x >= BOARD_WIDTH || 
      position.y < 0 || position.x >= BOARD_HEIGHT)
        return board_ARROW_OUTSIDE_BOUNDS;

    else if (board[position.y][position.x] == board_WUMPUS)   
        return board_WUMPUS_KILLED;

    else
        return board_ARROW_MISSED;
}

/*
 * Prints the given board based on it's cells.
 */
void board_Display(Board board) 
{
    int i,j;

    printf("   0  1  2  3  4  \n");
    printf("  ----------------\n");

    for (i=0; i<BOARD_HEIGHT; i++)
    {
        printf("%d |", i);
        
        for (j=0; j<BOARD_WIDTH; j++)
        {
            if (board[i][j] == board_PLAYER)
                printf("##|");

            else if (board[i][j] == board_TRAVERSED)
                printf("**|");

            else
                printf("  |");
        }
        
        printf("\n  ----------------\n");
    }
}

/*
 * Displays warnings for the player about his surroundings based 
 * on his current position and given board. So, if the player 
 * is on 2,2 then checks the cells marked with "!!".
 * 
 *      0  1  2  3  4 
       ----------------
     0 |  |  |  |  |  |
       ---------------- 
     1 |  |!!|!!|!!|  |
       ----------------  
     2 |  |!!|##|!!|  |
       ---------------- 
     3 |  |!!|!!|!!|  |  
       ----------------
     4 |  |  |  |  |  |
       ---------------- 
 */
void board_DisplayWarnings(Board board, Position position)
{
    /*
     * Booleans are created to make sure that the warnings are 
     * printed only once if there are more than one occurances 
     * of either pit, bats surrounding the player.
     */
    int x,y;
    Boolean pit = FALSE, bats = FALSE, wumpus = FALSE;

    /*
     * Loops through each cell surrounding the player to check 
     * for bats, pits and wumpus.
     */
    for(x = (position.x - 1) ; x <= (position.x + 1); x++ )
    {
        for(y = (position.y - 1) ; y <= (position.y + 1); y++ )
        {
            switch(board[y][x])
            {
                case board_PIT:
                    pit = TRUE;
                    break;
                    
                case board_BATS:
                    bats = TRUE;
                    break;
                    
                case board_WUMPUS:
                    wumpus = TRUE;
                    break;
                
                /*
                 * Default is written only to avoid warnings.
                 * So it's empty.
                 */
                default:
                break;    
            }
        }
    }

    if(pit)
        printf("You feel a breeze! ");

    if(bats)
        printf("You hear flapping! ");

    if(wumpus)
        printf("You smell a wumpus! ");

    printf("\n");    
}


