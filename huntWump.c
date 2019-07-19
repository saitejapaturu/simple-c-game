/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Sri Sai Teja Paturu
 * Student number: s3644335
 */

#include "huntWump.h"

#define INPUT_MAX_LENGTH 1

/*
 * This is the main function where the user can 
 * run the game display student information or 
 * quit.
 */
int main()
{
   char input[INPUT_MAX_LENGTH + EXTRA_SPACES];
   /**
    * Here's the main function. You can write the "main menu" loop/code
    * here or you can make separate functions - up to you.
    */

    while(TRUE)
    {
        getInput("Welcome to Hunt the Wumpus\n--------------------------\n"
                 "1. Play game\n2. Show student information\n3. Quit\n"
                 "\nPlease enter your choice: ", input, sizeof(input));

        if( strcmp(input, "1") == 0)
            game_PlayGame();

        else if( strcmp(input, "2") == 0)
            showStudentInformation();

        else if( strcmp(input, "3") == 0)
        {
            printf("Good bye! \n\n");
            return EXIT_SUCCESS;
        }

        else
            printInvalidInput();
    }
}

/*
 * Displays student, i.e. my name, student id and email.
 */
void showStudentInformation() 
{
   printf("----------------------------------\n");
   printf("Name:" STUDENT_NAME "\n");
   printf("Student ID:" STUDENT_ID "\n");
   printf("Email:" STUDENT_EMAIL "\n");
   printf("----------------------------------\n\n");
}



