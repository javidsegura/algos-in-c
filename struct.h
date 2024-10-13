#ifndef STRUCT_H
#define STRUCT_H

/*
Contains each node of the linked list and the function to populate it.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "ui.h"

#define NAME_SIZE 50

typedef struct client_instance
{
      int id;
      char name[NAME_SIZE];
      int age;
      char gender;
      char diagnosis[NAME_SIZE*2];
      char treatment[NAME_SIZE*2];
      struct client_instance *next;

} client_instance;

client_instance *head = NULL; //Head of llist => pointer to structure instance
client_instance *tail = NULL; //Tail of llist => pointer to pointer

int counter = 0; // ID assinger

void populate_struct(client_instance *client, int mode){

      /*
      Fill the node for both 'adding' mode and 'updating' mode
      */

      switch (mode)
      {
      case 'a':

            client->id = counter++;

            printf("1) First name | string: ");
            fgets(client->name, NAME_SIZE, stdin); // Read fgets is the safest way to read string input

            printf("2) Age | int: ");
            scanf("%d", &client->age);

            clear_input_buffer();

            printf("3) Gender ('f', 'm' or 'o') | char: ");
            scanf("%c", &client->gender);

            clear_input_buffer();

            printf("4) Diagnosis | string: ");
            fgets(client->diagnosis, NAME_SIZE*2, stdin);

            printf("5) Treatment | string: ");
            fgets(client->treatment, NAME_SIZE*2, stdin);
            break;

      case 'u':
            clear_input_buffer();

            printf("1) First name | string (click 'enter' to leaved not change): ");
            char temp_name[NAME_SIZE]; // Temporary storage for input
            fgets(temp_name, NAME_SIZE, stdin);
            if (temp_name[0] != '\n') { // If input is not just a newline
                strncpy(client->name, temp_name, NAME_SIZE);
            }

            printf("2) Age | int (click 'enter' to leaved not change): ");
            char temp_age[10]; // In array, in order to check for newline char
            fgets(temp_age, sizeof(temp_age), stdin);
            if (temp_age[0] != '\n') { 
                client->age = atoi(temp_age); // Convert input to int (correct datatpye of the field)
            }

            printf("3) Gender ('f', 'm' or 'o') | char (click 'enter' to leaved not change): ");
            char temp_gender[2]; // 2 memebers only due to last one always being null char
            fgets(temp_gender, sizeof(temp_gender), stdin);
            if (temp_gender[0] != '\n') { 
                client->gender = temp_gender[0];
                clear_input_buffer();
            }

            printf("4) Diagnosis | string (click 'enter' to leaved not change): ");
            char temp_diagnosis[NAME_SIZE*2];
            fgets(temp_diagnosis, NAME_SIZE*2, stdin);
            if (temp_diagnosis[0] != '\n') { 
                strncpy(client->diagnosis, temp_diagnosis, NAME_SIZE*2);
            }

            printf("5) Treatment | string (click 'enter' to leaved not change): ");
            char temp_treatment[NAME_SIZE*2];
            fgets(temp_treatment, NAME_SIZE*2, stdin);
            if (temp_treatment[0] != '\n') {
                strncpy(client->treatment, temp_treatment, NAME_SIZE*2);
            }
            break;
            
            default:
                  printf("!> Invalid mode.\n");
            break;

      }
}

#endif 
