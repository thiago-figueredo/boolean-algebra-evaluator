CC=gcc
CFLAGS=-g -Wall -std=c99 -O2

main: 
	$(CC) $(CFLAGS) ./src/main.c ./src/tokenizer.c ./src/linked_list.c ./src/string_utils.c ./src/lexer.c -o ./src/main

tokenizer: src/tokenizer
	$(CC) $(CFLAGS) src/tokenizer.c ./src/linked_list.c ./src/string_utils.c -o src/tokenizer

linked_list: src/linked_list
	$(CC) $(CFLAGS) ./src/linked_list.c -o linked_list

string_utils: src/string_utils
	$(CC) $(CFLAGS) ./src/string_utils.c -o string_utils

lexer: src/lexer
	$(CC) $(CFLAGS) ./src/lexer.c ./src/tokenizer.c -o lexer

clean:
	rm **/main