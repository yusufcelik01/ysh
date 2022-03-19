#include "ysh_helpers.h"
#include <stdlib.h>
#include <stdio.h>
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

    if(src == NULL) {
        return NULL;
    }
    
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

pid_t exec_progp(char** paths, char** tokens) {
    if((tokens[0][0] == '.' && tokens[0][1] == '/') 
            || tokens[0][0] == '/') {

        if(!access(tokens[0], X_OK)){
            pid_t cpid = exec_prog(tokens[0], tokens);
            return cpid;
        }    
        else if(!access(tokens[0], F_OK)) {
            fprintf(stderr, "ysh: %s: Permission denied", tokens[0]);
            return -1;
        }
        else {
            fprintf(stderr, "ysh: %s: No such file or directory", tokens[0]);
            return -1;
        }
    }

    int i;
    int found_bin = 0;
    for(i=0; paths[i] != NULL; i++){
        int exe_len = strlen(paths[i]) + strlen(tokens[0]);
        char* exe_path = malloc(sizeof(char) * (exe_len + 2));
        strcpy(exe_path, paths[i]);
        str_concat(exe_path, tokens[0]);
        //printf("path: %s\n", exe_path);

        //TODO input output redirection and PIPE

        if(!access(exe_path, X_OK)){
            pid_t cpid = exec_prog(exe_path, tokens);
            free(exe_path);
            return cpid;
        }


        free(exe_path);
    }
    if(!found_bin) {
        fprintf(stderr, "ysh: %s : command not found\n", tokens[0]);
    }

    return -1;
}
