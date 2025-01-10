#include "q2.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <postfix_expression>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *expression = argv[1];
    double result = evaluate_postfix(expression);

    printf("%.2f\n", result); // Print result with 2 decimal places
    return EXIT_SUCCESS;
}
