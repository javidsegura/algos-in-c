#ifndef HOSPITAL_H
#define HOSPITAL_H

/*
Contains each node of the linked list and the function to populate it.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h> // For mkdir
#include "ui.h"

#define NAME_SIZE 50
#define RECORDS_DIR "patient_records"
#define FILE_EXT ".txt"

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

void save_to_file(client_instance *client) {
    // Create directory if it doesn't exist
    mkdir(RECORDS_DIR, 0777);

    // Removing escape seq from readed name str
    char clean_name[NAME_SIZE];
    strncpy(clean_name, client->name, NAME_SIZE);
    clean_name[strcspn(clean_name, "\n")] = 0;  

    // Title of file is: <NAME>_<ID>.txt
    char filename[100];
    snprintf(filename, sizeof(filename), "%s/%s_%d%s", 
             RECORDS_DIR, clean_name, client->id, FILE_EXT); // snprintf used for formatting string and storing in buffer
    
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("!> Error: Could not create file for patient %d\n", client->id);
        return;
    }
    
    fprintf(fp, "ID: %d\n", client->id);
    fprintf(fp, "Name: %s", client->name);
    fprintf(fp, "Age: %d\n", client->age);
    fprintf(fp, "Gender: %c\n", client->gender);
    fprintf(fp, "Diagnosis: %s", client->diagnosis);
    fprintf(fp, "Treatment: %s", client->treatment);
    
    fclose(fp); // Make sure the stream is closed correctly
}

void load_from_file(char *clean_name, int id) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s/%s_%d%s", 
             RECORDS_DIR, clean_name, id, FILE_EXT);
    
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("!> Error: Could not open file for patient %d\n", id);
        return;
    }
    
    // Create new node to add data from files (basically upload files from disk to memory)
    client_instance *new_node = (client_instance *)malloc(sizeof(client_instance));
    if (new_node == NULL) {
        printf("!> Memory allocation failed\n");
        fclose(fp);
        return;
    }
    
    // Read file content
    char line[NAME_SIZE * 2];
    while (fgets(line, sizeof(line), fp)) { // Gets overwrriten at each line of the file!
        if (strncmp(line, "ID: ", 4) == 0) new_node->id = atoi(line + 4); // We specify the str to compare, the comparison and the number of chars to compare
        else if (strncmp(line, "Name: ", 6) == 0) strncpy(new_node->name, line + 6, NAME_SIZE);
        else if (strncmp(line, "Age: ", 5) == 0) new_node->age = atoi(line + 5);
        else if (strncmp(line, "Gender: ", 8) == 0) new_node->gender = line[8];
        else if (strncmp(line, "Diagnosis: ", 11) == 0) strncpy(new_node->diagnosis, line + 11, NAME_SIZE * 2); // We use the line + n in order to ski the prefix
        else if (strncmp(line, "Treatment: ", 11) == 0) strncpy(new_node->treatment, line + 11, NAME_SIZE * 2);
    }
    
    fclose(fp);
    
    // Add to linked list
    new_node->next = NULL;
    if (head == NULL) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

#endif 
