#include <stdio.h>
#include <stdlib.h>
#include "q1.h"

int main() {
    //pointers to structuers of type car
    struct car *available = NULL;
    struct car *rented = NULL;
    struct car *in_repair = NULL;

    //variables for user input
    int choice, mileage, return_date;
    char plate[7];
    double profit;

    // fill lists from files
    load_list_from_file(&available, "available.txt");
    load_list_from_file(&rented, "rented.txt");
    load_list_from_file(&in_repair, "repair.txt");

    do {
        prompt();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter car plate number and mileage: ");
                scanf("%6s %d", plate, &mileage);  // Limit plates input to 6 charecters
                insert_to_list(&available, plate, mileage, -1);
                printf("Car added to available for rent.\n");
                break;

            case 2:
                printf("Enter car plate number and final mileage: ");
                scanf("%6s %d", plate, &mileage);
                if (is_plate_in_list(rented, plate)) {
                    struct car *returned_car = remove_car_from_list(&rented, plate);
                    profit = profit_calculator(returned_car->mileage, mileage);
                    printf("Return has been processed. Charge is: $%.2f\n", profit);
                    insert_to_list(&available, plate, mileage, -1);
                    free(returned_car);
                } else {
                    printf("Car is not in rented list.\n");
                }
                break;

            case 3:
                printf("Enter the car plate number and the final mileage: ");
                scanf("%6s %d", plate, &mileage);
                if (is_plate_in_list(rented, plate)) {
                    struct car *returned_car = remove_car_from_list(&rented, plate);
                    profit = profit_calculator(returned_car->mileage, mileage);
                    printf("Return has been processed. Charge is: $%.2f\n", profit);
                    insert_to_list(&in_repair, plate, mileage, -1);
                    free(returned_car);
                } else {
                    printf("Car is not in the rented list.\n");
                }
                break;

            case 4:
                printf("Enter car plate number: ");
                scanf("%6s", plate);
                if (is_plate_in_list(in_repair, plate)) {
                    struct car *repaired_car = remove_car_from_list(&in_repair, plate);
                    insert_to_list(&available, plate, repaired_car->mileage, -1);
                    free(repaired_car);
                    printf("Car has been transferred from repair to available for rent.\n");
                } else {
                    printf("Car is not in repair.\n");
                }
                break;

            case 5:
                printf("Enter the return date (yymmdd): ");
                scanf("%d", &return_date);
                if (available != NULL) {
                    struct car *rented_car = remove_car_from_list(&available, available->plate);
                    insert_to_list(&rented, rented_car->plate, rented_car->mileage, return_date);
                    free(rented_car);
                    printf("Car has been rented with return date of: %d\n", return_date);
                } else {
                    printf("No cars are available for rent.\n");
                }
                break;

            case 6:
                printf("Cars available for rent:\n");
                print_list(available);
                printf("Rented cars:\n");
                print_list(rented);
                printf("Cars in repair cars:\n");
                print_list(in_repair);
                break;

            case 7:
                printf("ending\n");
                // Save the lists to files
                save_list_to_file(available, "available.txt");
                save_list_to_file(rented, "rented.txt");
                save_list_to_file(in_repair, "repair.txt");
                break;

            // If user enters invalid input
            default:
                printf("Invalid choice. Please re-enter a valid choice\n");
        }
    } while (choice != 7);

    // Free every list
    free_list(&available);
    free_list(&rented);
    free_list(&in_repair);

    return 0;
}
