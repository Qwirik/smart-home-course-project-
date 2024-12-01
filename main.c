#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

// Colors for terminal output
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// Constants
#define MAX_LEN_STR 255

// Login function
int log_in(char *login_i, char *password_i) {
    unsigned long login_h = hash(login_i);
    unsigned long password_h = hash(password_i);
    unsigned long long password = 252832602ULL; // Use ULL for large constants
    unsigned long long login = 404414076;   // Use ULL for large constants

    if (login != login_h) {
        printf(COLOR_RED "invalid login" COLOR_RESET "\n");
        return false;
    }
    if (password != password_h) {
        printf(COLOR_RED "access denied" COLOR_RESET "\n");
        return false;
    } else {
        printf(COLOR_GREEN "access successful" COLOR_RESET "\n");
        return true;
    }
}

// Find function to locate a command in the array
int find(char *word, char *mass[]) {
    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], word) == 0) {
            return i;
        }
    }
    return -1;
}

// Main function
int main() {
    char login[MAX_LEN_STR];
    char password[MAX_LEN_STR];
    static char *commands[] = {"exit", "test1", "test2", NULL};

    // Prompt for login
    printf("login: ");
    scanf("%s", login);

    // Prompt for password
    printf("password for %s: ", login);
    scanf("%s", password);

    // Attempt login
    bool access = log_in(login, password);

    // Command loop
    while (access) {
        char input[MAX_LEN_STR];

        // Prompt for command
        printf("[%s] ", login);
        scanf("%s", input);

        // Find the command index
        int command_index = find(input, commands);

        // Handle commands
        printf("[JARVIS] ");
        switch (command_index) {
            case 0: // "exit"
                printf("exiting... \n");
                access = false;
                break;
            case 1: // "test1"
                printf("test1\n");
                break;
            case 2: // "test2"
                printf("test2\n");
                break;
            default: // Unknown command
                printf("unknown command\n");
        }
    }

    return 0;
}