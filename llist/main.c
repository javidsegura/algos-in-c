#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "hospital.h"
#include "ui.h"

#define NAME_SIZE 50

/*
Central part of the program. 
*/

void add_patient(client_instance **tail);
void read_records();
void free_records();
void delete_record(int ID);
void update_record(int ID);
void load_all_records();

int main()
{  
      atexit(free_records); 
      atexit(bye_screen);

      load_all_records();  // Load existing records
      welcome_screen();

      while (1){
            int user_choice = process_input();

            switch (user_choice)
            {
            case 1: // Add
                  add_patient(&tail);
                  break;
            case 2: // Read
                  read_records();
                  break;
            case 3: // Update
                  {
                  header('u');
                  short int user_id;
                  printf("Provide the user ID: ");
                  scanf("%hi", &user_id);
                  update_record(user_id);
                  }
                  break;
            case 4: // Delete 
                  {
                  header('d');
                  short int user_id;
                  printf("Provide the user ID: ");
                  scanf("%hi", &user_id);
                  delete_record(user_id);
                  }
                  break;
            case 5: // Exit
                  exit(0);
            default:
                  printf("!> Option not found. Please try again.");
                  break;
            }
            cont_or_exit();
      }
      return 0;
}

void add_patient(client_instance **tail)  
{
      header('a'); 

      int id;
      if (head == NULL){
            head = (client_instance * )malloc(sizeof(client_instance));
            if (head == NULL){
                  printf("!> An error occured: failed to allocate memory");
                  return;
            }
            populate_struct(&(*head), 'a');
            head->next = NULL;
            *tail = head;
            id = head->id;
      }
      else{
            client_instance *new_node = (client_instance * )malloc(sizeof(client_instance));
            if (new_node == NULL){
                  printf("!> An error occured: failed to allocate memory");
            }
            populate_struct(&(*new_node), 'a');
            new_node->next = NULL; 
            (*tail)->next = new_node;
            *tail = new_node;
            id = new_node->id;
      }
      save_to_file(id == head->id ? head : *tail);
      printf("\nRecord added succesfully. Record ID is '%d'", id);
}


void read_records(){

      header('r');
      client_instance *current_node = head;

      while (current_node != NULL)
      {
            print_lines(1);
            printf("CLIENT:%D",current_node->id);
            print_lines(1);
            printf("Name       = %s", current_node->name);
            printf("Age        = %d\n", current_node->age);
            printf("Gender     = %c\n", current_node->gender);
            printf("Diagnosis  = %s", current_node->diagnosis);
            printf("Treatment  = %s", current_node->treatment);
            printf("ID         = %d\n", current_node->id);
            print_lines(2);
            
            current_node = current_node->next;
      }
      if (current_node == head){
            printf("No record has been affected.");
      }
}

void delete_record(int ID){

      client_instance *current_node = head;
      client_instance *prior_node = NULL;

      while (current_node != NULL && current_node->id !=ID)
      {
            prior_node = current_node;
            current_node = current_node->next;
      }
      if (current_node == NULL){
            printf("!> An error occured: user not in database\n");
            return;
      }
      
      if (current_node == head){
            head = current_node->next;
            if (head == NULL){
                  tail = NULL;
            }
      }
      else if (current_node == tail){
            prior_node->next = NULL;
            tail = prior_node;
      }
      else{
            prior_node->next = current_node->next;
      }
      printf("Record deleted succesfully.");
      free(current_node);
            
}

void update_record(int ID){

      client_instance *current_node = head;

      while (current_node != NULL && current_node->id !=ID)
      {
            current_node = current_node->next;
      }
      if (current_node == NULL){
            printf("!> An error occured: user not in database\n");
            return;
      }
      
      populate_struct(&(*current_node), 'u'); 
      save_to_file(current_node);  // Save updated information

      printf("\nRecord edited successfully. Same record ID: '%d'", current_node->id);
}

void free_records(){
      /*
      Empty database at exit
      */

      client_instance *current_node = head;

      while (current_node != NULL)
      {
            client_instance *temp = current_node;
            current_node = current_node->next;
            free(temp);
      }
}

void load_all_records() {
    DIR *dir;
    struct dirent *ent;
    
    dir = opendir(RECORDS_DIR);
    if (dir == NULL) {
        return;  
    }
    
    while ((ent = readdir(dir)) != NULL) {
        if (strstr(ent->d_name, FILE_EXT) != NULL) {
            // Extract ID from filename
            int id;
            char name[NAME_SIZE];
            sscanf(ent->d_name, "%s_%d.txt", name, &id);
            load_from_file(name, id);
            if (id >= counter) counter = id + 1;  // Update counter for new IDs
        }
    }
    closedir(dir);
}