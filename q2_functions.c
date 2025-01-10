/*
Name:Parteek Dhami
Student ID: 1278438
Assignment 2, Question 2
*/

#include "q2.h"

// Push a value onto the stack
void push(Operand **stack, double value) {
    Operand *new_node = (Operand *)malloc(sizeof(Operand));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = *stack;
    *stack = new_node;
}

// Pop a value from the stack
double pop(Operand **stack) {
    if (is_empty(*stack)) {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    Operand *temp = *stack;
    double value = temp->value;
    *stack = temp->next;
    free(temp);
    return value;
}

// Check if the stack is empty
bool is_empty(Operand *stack) {
    return stack == NULL;
}

// Evaluate the postfix expression
double evaluate_postfix(const char *expression) {
    Operand *stack = NULL;

    for (int i = 0; i < strlen(expression); ++i) {
        char c = expression[i];

        // Check if character is a digit
        if (c >= '0' && c <= '9') {
            push(&stack, c - '0'); // Convert char to int
        } else {
            // Ensure valid operator
            if (is_empty(stack)) {
                fprintf(stderr, "Error: Invalid expression\n");
                free_stack(&stack);
                exit(EXIT_FAILURE);
            }

            double operand2 = pop(&stack);
            double operand1 = pop(&stack);
            double result;

            switch (c) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        fprintf(stderr, "Error: Division by zero\n");
                        free_stack(&stack);
                        exit(EXIT_FAILURE);
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    fprintf(stderr, "Error: Invalid operator %c\n", c);
                    free_stack(&stack);
                    exit(EXIT_FAILURE);
            }
            push(&stack, result);
        }
    }

    // Final result should be the only element in the stack
    if (is_empty(stack)) {
        fprintf(stderr, "Error: Invalid expression\n");
        free_stack(&stack);
        exit(EXIT_FAILURE);
    }
    double final_result = pop(&stack);

    // Ensure the stack is empty after evaluation
    if (!is_empty(stack)) {
        fprintf(stderr, "Error: Invalid expression\n");
        free_stack(&stack);
        exit(EXIT_FAILURE);
    }

    free_stack(&stack);
    return final_result;
}

// Free the stack memory
void free_stack(Operand **stack) {
    while (!is_empty(*stack)) {
        pop(stack);
    }
}