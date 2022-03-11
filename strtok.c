#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char white_spaces[] = {' ', '\t', '\n', '\0'};

int main() {
        
    char* buff = NULL;
    char* buff_start = NULL;
    char* token = NULL;
    char** tokens;

    size_t n;
    n = 1;

    tokens = calloc(sizeof(char*), 512);

    
    getline(&buff, &n, stdin);
    buff_start = buff;

    printf("READ: %s", buff);
    printf("pointer to the buffer %p\n", buff);
    
    int token_no = 0;
    token = strtok(buff, white_spaces);
    tokens[token_no++] = token;
    while(token){
        
        //printf("%dth token: %s\n", token_no, token);
        //printf("pointer to the token%p diff: %ld\n", token, token - buff);
        token = strtok(NULL, white_spaces);
        tokens[token_no++] = token;
    }
    tokens[token_no] = NULL;

    int i=0;
    while(tokens[i] != NULL){
        printf("%dth token: %s\n", i, tokens[i]);
        i++;
    }

    
    //printf("rest of the string: %s\n", buff);

    free(buff_start);

    return 0;
}
