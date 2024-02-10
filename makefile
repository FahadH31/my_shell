# Makefile
# Fahad Hussain, Rajiv Lomada, Ayush Patel, Kevaun Harris. Operating Systems Lab 2.
all: myshell

myshell: myshell.c utility.c
	gcc -o myshell myshell.c utility.c -I.

# Note: The command under 'myshell:' must be preceded by a tab, not spaces.

