#ifndef Q2_H
#define Q2_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for stack nodes
typedef struct Operand {
    double value;            // Value of the operand
    struct Operand *next;    // Pointer to the next node
} Operand;

// Function prototypes
void push(Operand **stack, double value);
double pop(Operand **stack);
bool is_empty(Operand *stack);
double evaluate_postfix(const char *expression);
void free_stack(Operand **stack);

#endif // Q2_H