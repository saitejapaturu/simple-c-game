/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Sri Sai Teja Paturu
 * Student number: s3644335
 */
#include "player.h"

/*
 * Initialises the given player's initial to the position provided 
 * and initialises the number of arrows the player has. 
 */
void player_Initialise(Player * player, Position position)
{
   player->position = position;
   player->numArrows = INIT_ARROW_COUNT;
}

/*
 * Returns a position based on the position and direction provided.
 */
Position player_GetNextPosition(Position position, Direction direction)
{
    /*
     * Increments or decrements either the x or the y coordiante 
     * of the given postion based on the given direction.
     */
   if(direction == player_NORTH)
       position.y--;

   else if(direction == player_SOUTH)
       position.y++;

   else if(direction == player_EAST)
       position.x++;

   else if(direction == player_WEST)
       position.x--;

   return position;
}

/*
 * Updates player's location to the given position.
 */
void player_UpdatePosition(Player * player, Position position) 
{
   player->position = position;
}

