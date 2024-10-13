#ifndef UI_H
#define UI_H

/*
UI components for the terminal's stdout. Also input processors and buffer cleaner.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void print_lines(int mode){
      /*
      Prints lines to simulate different sections
      */
      switch (mode)
      {
      case 1:
            printf("\n----------------------------------\n");
            break;
      case 2: // No \n at the beginning
            printf("----------------------------------\n");
            break;
      
      default:
            break;
      }
}

void header(char mode){
      /*
      Header for the subpages
      */
      system("clear");
      print_lines(2);
      printf("HOSPITAL's Database");
      switch (mode)
      {
      case 'h':
            printf("/ HOMEPAGE");
            print_lines(1);
            break;
      case 'a':
            printf("/ ADDING RECORD");
            print_lines(1);
            break;
      case 'r':
            printf("/ READING RECORDS");
            print_lines(1);
            break;
      case 'u':
            printf("/ UPDATING RECORD");
            print_lines(1);
            break;
      case 'd':
            printf("/ DELETING RECORD");
            print_lines(1);
            break;
      default:
            printf("Mode could not be found");
            break;
      }

}

void clear_input_buffer() {
      /*
      Clean buffer 
      */
    int c; 
    while ((c = getchar()) != '\n' && c != EOF);
}

void bye_screen(){
      printf("\n\n");
      //system("figlet BYE"); // In case you  have figlet, uncommet this statement out
}

void welcome_screen(){
      //system("figlet 'WELCOME, HOSPITAL DATABASE'"); // In case you have figlet, uncommet this statement out and the one below
      //sleep(3);
}

void cont_or_exit(){
      /*
      Before the while loop (that holds the application) ask for new instruction, 
      prompt the user if he wants to leave. 
      */
      print_lines(1);

      short int user_selection;
      printf("Continue (0) or exit (1)\n");
      printf("=> ");
      scanf("%hi", &user_selection);
      if (user_selection == 1){
            exit(0);
      }
}

short int process_input(){

      /*
      Get numerical user choice on what action
      the user wants to take
      */

      header('h');

      printf("\nSelection an option: ");
      printf("\n\t 1: Add a new record \n\t 2: Read all records \n\t 3: Update a record \n\t 4: Delete a record \n\t 5: Exit\n");
      printf("=> ");
      short int user_choice;
      scanf("%hi", &user_choice);
          
      clear_input_buffer(); // This is crutial. If the buffer is not clean the next read from stdin will be already consumed with the prior content.
      
      return user_choice;

      
}

#endif