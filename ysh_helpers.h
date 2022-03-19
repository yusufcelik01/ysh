#ifndef __YSH_HELPERS__
#define __YSH_HELPERS__

#define WAIT_TRUE  1
#define WAIT_FALSE 0

#include <sys/types.h>

char** get_tokens(char* str, const char* delims);
/*
        int i=0;
   this functions returns an array of null terminated strings end of the array is inditaced by a NULL terminator this array is allocated by the function but MUST be freed by the user

    Warnings:
        Also note that this function modifies the given string  by overwriting the delimeters with NULL characters 


 */

char* str_copy(const char* src);
char* str_concat(char* dst, char* src);
pid_t exec_prog(char* path, char** tokens);
pid_t exec_progp(char** paths, char** tokens);

#endif
