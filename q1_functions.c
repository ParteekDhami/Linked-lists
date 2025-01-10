#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q1.h"

// Inserting a car into the list and sorting it
struct car *insert_to_list(struct car **head, char plate[], int mileage, int return_date) {
    // Allocate memory for struct car
    struct car *new_car = (struct car *)malloc(sizeof(struct car));
    if (new_car == NULL) {
        printf("Memory allocation failed\n");
        exit(1); // Exit the program if memory allocation fails
    }

    // Use strncpy to safely copy plate
    strncpy(new_car->plate, plate, sizeof(new_car->plate) - 1);
    new_car->plate[sizeof(new_car->plate) - 1] = '\0';  // Ensure null termination

    new_car->mileage = mileage;
    new_car->return_date = return_date;
    new_car->next = NULL;

    // If list is empty or new car's mileage is less than head's, insert at the head
    if (*head == NULL || ((*head)->mileage > mileage && return_date == -1)) {
        new_car->next = *head;
        *head = new_car;
    } else {
        struct car *current = *head;
        while (current->next != NULL && current->next->mileage < mileage) {
            current = current->next;
        }
        new_car->next = current->next;
        current->next = new_car;
    }

    return new_car;
}

// Function to print the list
void print_list(struct car *head) {
    struct car *current = head;
    while (current != NULL) {
        printf("Plate: %s, Mileage: %d, Return Date: %d\n", current->plate, current->mileage, current->return_date);
        current = current->next;
    }
}

// Check to see if the plate is in list
bool is_plate_in_list(struct car *head, char plate[]) {
    struct car *current = head;
    while (current != NULL) {
        if (strcmp(current->plate, plate) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Function for removing a car from the list
struct car *remove_car_from_list(struct car **head, char plate[]) {
    struct car *current = *head;
    struct car *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->plate, plate) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            current->next = NULL;
            return current;
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}

// Calculating profit
double profit_calculator(int initial_mileage, int final_mileage) {
    int km_driven = final_mileage - initial_mileage;
    if (km_driven <= 200) {
        return 80.0;
    }
    return 80.0 + (km_driven - 200) * 0.15;
}

// Free the memory of linked list
void free_list(struct car **head) {
    struct car *current = *head;
    struct car *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL; // Set head to NULL to avoid dangling pointer
}

// Function to save a car list to a file
void save_list_to_file(struct car *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }

    struct car *current = head;
    while (current != NULL) {
        fprintf(file, "%s %d %d\n", current->plate, current->mileage, current->return_date);
        current = current->next;
    }

    fclose(file);
}

// Function to load a car list from a file
void load_list_from_file(struct car **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s for reading.\n", filename);
        return;
    }

    char plate[7];
    int mileage, return_date;

    while (fscanf(file, "%6s %d %d", plate, &mileage, &return_date) == 3) {
        insert_to_list(head, plate, mileage, return_date);
    }

    fclose(file);
}

// Function to print the menu
void prompt() {
    printf("\nEnter a transaction code (1-7):\n");
    printf("1) Add new car to available for rent\n");
    printf("2) Return car to available for rent\n");
    printf("3) Return car to in repair\n");
    printf("4) Move from in repair to available for rent\n");
    printf("5) Rent first available car\n");
    printf("6) Print all lists\n");
    printf("7) Quit\n");
}
