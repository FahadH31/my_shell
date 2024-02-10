# Makefile
all: myshell

myshell: myshell.c utility.c
	gcc -o myshell myshell.c utility.c -I.

# Note: The command under 'myshell:' must be preceded by a tab, not spaces.

