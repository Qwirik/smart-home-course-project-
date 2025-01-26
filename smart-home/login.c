#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "login.h"

int log_in(char *login_i, char *password_i) {
    unsigned long login_h = hash(login_i);
    unsigned long password_h = hash(password_i);
    unsigned long long password = 252832602ULL; // Используем ULL для больших чисел
    unsigned long long login = 404414076;       // Используем ULL для больших чисел

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