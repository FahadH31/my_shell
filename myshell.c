// myshell.c
// This file contains the main logic of your shell program.
#include "myshell.h"

// Function to execute the entered command
void execute_command(char *input) {
    char *token;
    char *delim = " \n";
    token = strtok(input, delim); // Tokenize the input

    // If the first token is a recognizable command
    if (token != NULL) {
        // Change Directory
        if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, delim); // Get the next part of the input (directory path)
            change_directory(token); // Call the change_directory function
        } 
        // Clear Screen
        else if (strcmp(token, "clr") == 0) {
            clearscn();
        }
        // List directory contents
        else if (strcmp(token, "dir") == 0) {
            token = strtok(NULL, delim); // Get the next part of the input (directory name)
            list_dir_contents(token);
        }
        // List environment strings
        else if (strcmp(token, "environ") == 0) {
            list_environment_strings();
        }
        // Quit
        else if (strcmp(token, "quit") == 0) {
            quit_shell();
        }
        // Echo
        else if (strcmp(token, "echo") == 0) {
            token = strtok(NULL, delim); // Get the next part of the input (comment)
            echo_shell(token);
        }
        // Help
        else if (strcmp(token, "help") == 0) {
            display_help();
        }
        // Pause
        else if (strcmp(token, "pause") == 0) {
            pause_shell();   
        }   
        // External Command
        else {
            // Fork a child process
            pid_t pid = fork();

            if (pid < 0) {
                // Fork failed
                perror("fork");
            } else if (pid == 0) {
                // Child process
                // Set the parent environment variable
                char parent_env[1024];
                sprintf(parent_env, "parent=%s/myshell", getenv("SHELL"));

                if (putenv(parent_env) != 0) {
                    perror("putenv");
                    exit(EXIT_FAILURE);
                }

                // Execute the command
                if (execlp(token, token, NULL) < 0) {
                    // If execution fails, print message
                    printf("Command not recognized.\n");
		    exit(EXIT_FAILURE);
                }
            } else {
                // Parent process
                // Wait for the child process to finish
                wait(NULL);
            }
        } 
    }
}

int main() {
    char *wd; // Buffer for current working directory 
    char input[1024]; // Buffer for user input
    wd = (char *)malloc(100 * sizeof(char));
    int count = 0; // To ensure SHELL env var is only set on execution
    
    // Main command loop
    while (1) {
        getcwd(wd, 100);
        printf("MyShell%s>> ", wd); // Prompt for input
        if (count < 1) {        
            count++;
            if (setenv("SHELL", strcat(wd, "/myshell"), 1) != 0) {
                perror("setenv() error");
            }
        }   
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exit on EOF
        }
        execute_command(input); // Process the input
    }

    free(wd); // Free memory allocated for wd
    return 0;
}

