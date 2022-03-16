#include "ysh_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



char** get_tokens(char* str, const char* delims) {

    int token_no = 0; 
    char** tokens = calloc(sizeof(char*), 1024);
    char* token;
    token = strtok(str, delims);
    tokens[token_no++] = token;

    while(token != NULL) {
        token = strtok(NULL, delims);
        tokens[token_no++] = token;
    }
    tokens[token_no] = NULL;

    return tokens;
}

char* str_copy(const char* src) {
    char* dst; 
    size_t n = 2 << 3;
    int i = 0;
    
    dst = calloc(sizeof(char), n);
    while( (dst[i] = src[i]) != '\0') {
        if(i == n-1) {
            n += n;
            char* tmp = realloc(dst, n);
            if(tmp == NULL){
                free(dst);
                return NULL;//alloc fail
            }
            dst = tmp;
        }
        i++;
    }

    return dst;
}

char* str_concat(char* dst, char* src) {
    int i = 0;
    int j = 0;

    while(dst[i] != '\0') {
        i++;
    }
    while((dst[i] = src[j]) != '\0'){
        i++;
        j++;
    }
    return dst;
}

pid_t exec_prog(char* path, char** tokens) {

    pid_t pid = fork();

    if(pid < 0){
        return -1;
    }
    else if(pid == 0) {
        execv(path, tokens);
    }
    else {
        return pid;//return childs pid
    }



    return 0;
}
