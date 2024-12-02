#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"
#include "login.h"

// Функция для поиска команды в массиве
int find(char *word, char *mass[]) {
    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], word) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    char login[MAX_LEN_STR];
    char password[MAX_LEN_STR];
    static char *commands[] = {"exit", "test1", "test2", NULL};

    // Запрос логина
    printf("login: ");
    scanf("%s", login);

    // Запрос пароля
    printf("password for %s: ", login);
    scanf("%s", password);

    // Попытка входа
    bool access = log_in(login, password);
    getchar();
    // Цикл команд
    while (access) {
        char input[MAX_LEN_STR];

        // Запрос команды
        printf("[%s] ", login);
        fgets(input, MAX_LEN_STR, stdin);


        int length = strlen(input);    
        if (input[length - 1] == '\n') {
            input[length - 1] = '\0';  // Убираем символ новой строки в конце строки        
            length--;  // Уменьшаем длину на 1, если убрали символ новой строки
        }


        // Поиск команды
        int command_index = find(input, commands);

        // Обработка команд
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
            default: // Неизвестная команда
                printf("unknown command\n");
        }
    }

    return 0;
}
