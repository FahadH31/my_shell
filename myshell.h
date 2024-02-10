// myshell.h
/* This is the header file where you include standard libraries and declare functions used across your shell program. */
// By Fahad Hussain (100816265), Kevaun Harris (100822219), Ayush Patel (100823602), and Rajiv Lomada (100823689)

#ifndef MYSHELL_H  // Prevents double inclusion of this header file
#define MYSHELL_H

#include <stdio.h>   // Standard I/O functions
#include <stdlib.h>  // Standard library for functions like malloc
#include <string.h>  // String handling functions
#include <unistd.h>  // Provides access to the POSIX operating system API
#include <stdbool.h>
#include <sys/wait.h> // For wait function, to wait for child process
// Function declaration for changing directories (cd)
void change_directory(char *path);

// All additional function declarations
void clearscn();
void list_dir_contents(char *path);
void list_environment_strings();
void echo_shell(char *comment);
void display_help();
void pause_shell();
void quit_shell();
#endif
