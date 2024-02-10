// utility.c
// This file will have the implementation of the commands.

#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

// Function to change the current working directory
void change_directory(char *path) {
    char cwd[1024];
    // Check if the path argument is NULL, which implies no specific directory was provided
    if (path == NULL) {
        // Create a buffer to store the current working directory path.

        // Use getcwd to get the current working directory.
        // getcwd fills the array 'cwd' with the absolute pathname of the current working directory.
        // If the function succeeds, the cwd array contains this pathname and NULL is not returned.
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            // If successful, print the current working directory to the user
            printf("%s\n", cwd);
        } else {
            // If getcwd fails, use perror to print an error message.
            // perror produces a message on standard error describing the last error 
	    // encountered during a call to a system or library function.
            perror("getcwd() error");
        }
    } else {
        // If a path is provided, try changing the directory to the specified path using chdir
        // chdir changes the current working directory of the calling process to the directory 
	// specified in path.

        // If chdir returns a non-zero value, it indicates an error occurred 
	// (like if the directory does not exist).
        if (chdir(path) != 0) {
            // In case of an error, use perror to print the error message.
            perror("myshell");
        }

	// Update the PWD environment variable
    	if (setenv("PWD", getcwd(cwd, sizeof(cwd)), 1) != 0) {
        	perror("setenv() error");
    	}
    }
} 

void clearscn() {
	// ANSI escape codes to clear screen (by printing new-line characters)
	// and move the cursor.
	printf("\033[2J\033[H");
}

void list_dir_contents(char *path) {
    DIR *directory;
    struct dirent *file;

    // Open the specified directory
    if(path==NULL){
    	directory = opendir(".");
    }
    else{
    	directory = opendir(path);
    }

    if (directory == NULL) {
    	perror("Error opening directory");
    	return;
    }

    // Print directory contents
    while ((file=readdir(directory))!=NULL){
    	printf("%s\n", file->d_name);
    }

    closedir(directory);
}

void list_environment_strings() {
    extern char **environ;

    // Iterate through the array of strings
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}

void echo_shell(char *comment) {
	if(comment==NULL){
		printf("Please enter something to print to the screen\n");
	}
	else{
		printf("%s\n",comment);
	}
}

void display_help() {
    	// Display the manual using 'more' filter
	system("more readme.txt");	
}

void pause_shell() {
	printf("The shell is paused. Press Enter to continue...");

    	// Pause the program until the user presses Enter
    	getchar();
}

void quit_shell() {
	exit(0);
}

