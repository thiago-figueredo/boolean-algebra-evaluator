#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h> 
#include <assert.h>
#include "./tokenizer.h"
#include "./linked_list.h"
#include "./string_utils.h"

static char* tokens_content[] = {
    [AND] = ".",
    [OR] = "+",
    [NOT] = "~",
    [XOR] = "(+)",
    [XAND] = "(.)",
    [LEFT_PARENTHESIS] = "(",
    [RIGHT_PARENTHESIS] = ")",
};

static char* tokens_type[] = {
    [AND] = "AND_OPERATOR",
    [OR] = "OR_OPERATOR",
    [NOT] = "NOT_OPERATOR",
    [XOR] = "XOR_OPERATOR",
    [XAND] = "XAND_OPERATOR",
    [VARIABLE] = "VARIABLE",
    [LEFT_PARENTHESIS] = "LEFT_PARENTHESIS",
    [RIGHT_PARENTHESIS] = "RIGHT_PARENTHESIS",
};

Token* init_token(TokenType type, char* content) 
{
    assert(content && "Could not init token with null content");

    Token* token = malloc(sizeof(Token));
    
    token->type = type;
    token->content = calloc(strlen(content), sizeof(char));
    strcpy(token->content, content);

    return token;
}

LinkedList* tokenize(char* expression) 
{
    assert(expression && "Could not tokenize null expression");

    size_t expression_length = strlen(expression);
    LinkedList* tokens = new_linked_list();

    for (size_t i = 0; i < expression_length; i++) {
        char content[MAX_EXPRESSION_SIZE] = { 0 };
        size_t k = 0;

        if (expression[i] == ' ') {
            continue;
        }

        if (
            i + 2 < expression_length && 
            expression[i] == '(' && 
            (
                expression[i+1] == '+' || 
                expression[i+1] == '.' 
            ) &&
            expression[i+2] == ')'
        ) {
            size_t z, j = i;

            for (z = 0; z < 3; z++) {
                content[k++] = expression[j++];
            }
        }  else if (
            i + 1 < expression_length && 
            expression[i] == '~' && 
            (
                expression[i+1] == '.' ||
                expression[i+1] == '+'
            ) 
        ) {
            size_t z,  j = i;

            for (z = 0; z < 2; z++) {
                content[k++] = expression[j++];
            }
        } else {
            content[k++] = expression[i];
        }
        
        if (string_equals(content, tokens_content[AND])) {
            Token* token = init_token(AND, content);
            linked_list_insert(tokens, token);
        }  else if (string_equals(content, tokens_content[OR])) {
            Token* token = init_token(OR, content);
            linked_list_insert(tokens, token);
        } else if (string_equals(content, tokens_content[NOT])) {
            Token* token = init_token(NOT, content);
            linked_list_insert(tokens, token);
        } else if (string_equals(content, tokens_content[XOR])) {
            Token* token = init_token(XOR, content);
            linked_list_insert(tokens, token);
            i += 2;
        } else if (string_equals(content, tokens_content[XAND])) {
            Token* token = init_token(XAND, content);
            linked_list_insert(tokens, token);
            i += 2;
        } else if (string_equals(content, tokens_content[LEFT_PARENTHESIS])) {
            Token* token = init_token(LEFT_PARENTHESIS, content);
            linked_list_insert(tokens, token);
        } else if (string_equals(content, tokens_content[RIGHT_PARENTHESIS])) {
            Token* token = init_token(RIGHT_PARENTHESIS, content);
            linked_list_insert(tokens, token);
        } else {
            Token* token = init_token(VARIABLE, content);
            linked_list_insert(tokens, token);
        }
    }

    return tokens;
}

void print_token(Token token) 
{
    printf("{ TOKEN_TYPE: %s, TOKEN_CONTENT: %s }\n", tokens_type[token.type], token.content);
}

void print_tokens(LinkedList* tokens)
{
    assert(tokens && "Cannot print a null tokens linked list");

    LinkedListNode* token = tokens->head;

    while (token) {
        print_token(*((Token*)token->data));
        token = token->next;
    }
}