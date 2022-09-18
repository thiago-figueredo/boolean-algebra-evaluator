#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./tokenizer.h"
#include "./linked_list.h"
#include "./string_utils.h"

bool boolean_algebra_evaluator(char* expression) 
{
    if (!expression) {
        fprintf(stderr, "Could not evaluate null expression!\n");
    }

    LinkedList* tokens = tokenize(expression);
    print_tokens(tokens);

    return true;
}

int main(void) 
{
    char expression[MAX_EXPRESSION_SIZE];

    do {
        printf("boolean-algebra-evaluator> ");

        if (!fgets(expression, MAX_EXPRESSION_SIZE, stdin)) {
            fprintf(stderr, "Could not evaluate expression\n");
            continue;
        } 
        
        expression[strlen(expression) - 1] = '\0';
        char* expr = string_to_upper(expression);

        if (string_equals(expr, "QUIT") || string_equals(expr, "EXIT")) {
            exit(EXIT_SUCCESS);
        }

        printf("expression: %s\n", expr);
        boolean_algebra_evaluator(expression);
    } while (true);
    
    return 0;
}