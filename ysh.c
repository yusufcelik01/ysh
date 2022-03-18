#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ysh_helpers.h"
#include <sys/wait.h>

char white_spaces[] = {' ', '\t', '\n', '\0'};

int main(int argc, char** argv) {
    if(argc == 2) {//batch mode
        //TODO
        printf("batch mode with arg: %s\n", argv[1]);
        printf("batch mode is not supported yet\n");
        exit(0);
    }
    else if (argc > 2) {
        fprintf(stderr, "Incorrect usage\n");
        exit(1);
    }
    //else prompt mode


    char** paths = NULL;

    char* line = NULL;
    char* line_begin = NULL;
    size_t line_size = 1;


    paths = malloc(sizeof(char*) *2);
    paths[1] = NULL;
    paths[0] = str_copy("/bin/");


    size_t dir_name_size = 1024;
    char* cwd = calloc(sizeof(char), dir_name_size);
    if(getcwd(cwd, dir_name_size) == NULL) {
        fprintf(stderr, "Error on reading directory name exiting shell\n");
        exit(1);
    }

    while(1){

        printf("ysh:%s$ ", cwd);
        if(getline(&line, &line_size, stdin) == -1 ){
            
            exit(0);
        } 
        line_begin = line;

        char** tokens = get_tokens(line, white_spaces);
        int token_count=0;
        while(tokens[token_count] != NULL){
            //printf("%dth token: %s\n", token_count, tokens[token_count]);
            token_count++;
        }

        //TODO combined commands things like < > | & &&

        //TODO exec command
        //built in commands 
        if(token_count < 1){
            continue;
        }
        if(strcmp(tokens[0], "exit") == 0) {
            free(line_begin);
            exit(0);
        }
        else if(strcmp(tokens[0], "cd") == 0) {
            if(token_count != 2){
                fprintf(stderr, "cd needs exactly one argument\n");
                continue;
            }
            chdir(tokens[1]);
            if(getcwd(cwd, dir_name_size) == NULL) {
                fprintf(stderr, "Error on reading directory name exiting shell\n");
                exit(1);
            }

        }
        else if(strcmp(tokens[0], "path") == 0) {
            int i = 1;
            int number_of_paths=0;
            while(tokens[i] != NULL) {
                i++;
                number_of_paths++;
            }
            //TODO free old paths
            i = 0;
            while(paths[i] != NULL) {
                free(paths[i]); 
                i++;
            }
            free(paths);
            paths = calloc(sizeof(char*), number_of_paths + 1);
            int j = 0;
            i = 1;
            while(tokens[i] != NULL) {
                
                int path_size = 0;
                char prev = '\0';
                while(tokens[i][path_size] != '\0') {
                    prev = tokens[i][path_size];
                    path_size++;
                }
                if(prev != '/') {
                    char* tmp_path = malloc(sizeof(char)*(path_size + 2));
                    tmp_path[0] = '\0';
                    str_concat(tmp_path, tokens[i]);
                    str_concat(tmp_path, "/");
                    paths[j] = tmp_path;
                }
                else {
                    paths[j] = str_copy(tokens[i]);
                }

                j++;
                i++;
            }
            paths[j] = NULL;
                         

        }
        else {//assume only one commnad is given
            //exec_prog(paths, tokens, WAIT_TRUE);
            int i;
            for(i=0; paths[i] != NULL; i++){
                int exe_len = strlen(paths[i]) + strlen(tokens[0]);
                char* exe_path = malloc(sizeof(char) * (exe_len + 2));
                strcpy(exe_path, paths[i]);
                str_concat(exe_path, tokens[0]);
                //printf("path: %s\n", exe_path);

                if(!access(exe_path, X_OK)){
                    pid_t cpid = exec_prog(exe_path, tokens);
                    int wstatus; 
                    waitpid(cpid, &wstatus, 0);
                    free(exe_path);
                    break;
                }

                free(exe_path);
            }
        }

        free(line_begin);
        line = NULL;
        free(tokens);
    }

    free(line_begin);

    return 0;
}

