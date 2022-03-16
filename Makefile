CC=gcc
CFLAGS= -Wall -Werror -g
HELPERS= ysh_helpers.o

ysh: ysh.c $(HELPERS)
	$(CC) $(CFLAGS) ysh.c $(HELPERS) -o ysh

