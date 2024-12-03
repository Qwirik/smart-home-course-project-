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
'''
Вызов приведущих функций через стрелки 
clear
'''
    

int main() {
    int led_1_status = 0, led_2_status = 0, led_3_status = 0, led_4_status = 0;
    char login[MAX_LEN_STR];
    char password[MAX_LEN_STR];
    static char *commands[] = {"exit", "help", "status", "led_1 0", "led_1 1", "led_2 0", "led_2 1", "led_3 0", "led_3 1","led_4 0", "led_4 1",  NULL};
    static char *yes[] = {"yes", "y", "yea", "yup", "yep"};
    bool a = true;
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
        if(a)
            printf("For a short summary of all commands, run 'help'\n");
        a = false;
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
                char temp[MAX_LEN_STR];
                printf("you are sure? (yes or no):");
                scanf("%s", temp); 
                if(find(temp ,yes) != -1){
                    printf("exiting... \n");
                    access = false;
                }
                else{
                    getchar();
                }
                break;
            case 1:
                printf("\n\
exit                                      for exit from terminal\n\
status                                    for print status pin\n\
led_<num of pin> <status_pin>             for control pin\n");
                break;
            case 2:
                printf("status all pins");
                if(led_1_status == 0){
                    printf("\nled_1           status" COLOR_RED   " %d" COLOR_RESET"\n",led_1_status);
                }
                else{
                    printf("\nled_1           status" COLOR_GREEN " %d" COLOR_RESET"\n",led_1_status);
                }
                if(led_2_status == 0){
                    printf("\nled_2           status" COLOR_RED   " %d" COLOR_RESET"\n",led_2_status);
                }
                else{
                    printf("\nled_2           status" COLOR_GREEN " %d" COLOR_RESET"\n",led_2_status);
                }
                if(led_3_status == 0){
                    printf("\nled_3           status" COLOR_RED   " %d" COLOR_RESET"\n",led_3_status);
                }
                else{
                    printf("\nled_3           status" COLOR_GREEN " %d" COLOR_RESET"\n",led_3_status);
                }
                if(led_4_status == 0){
                    printf("\nled_4           status" COLOR_RED   " %d" COLOR_RESET"\n",led_4_status);
                }
                else{
                    printf("\nled_4           status" COLOR_GREEN " %d" COLOR_RESET"\n",led_4_status);
                }
                
                break;
            case 3:
                led_1_status = 0;
                printf("led 1" COLOR_RED   " off" COLOR_RESET"\n");
                break;
            case 4:
                led_1_status = 1;
                printf("led 1" COLOR_GREEN " on"  COLOR_RESET"\n");
                break;
            case 5:
                led_2_status = 0;
                printf("led 2" COLOR_RED   " off" COLOR_RESET"\n");
                break;
            case 6:
                led_2_status = 1;
                printf("led 2" COLOR_GREEN " on"  COLOR_RESET"\n");
                break;
            case 7:
                led_3_status = 0;
                printf("led 3" COLOR_RED   " off" COLOR_RESET"\n");
                break;
            case 8:
                led_3_status = 1;
                printf("led 3" COLOR_GREEN " on"  COLOR_RESET"\n");
                break;
            case 9:
                led_4_status = 0;
                printf("led 4" COLOR_RED " off" COLOR_RESET"\n");
                break;
            case 10:
                led_4_status = 1;
                printf("led 4" COLOR_GREEN " on" COLOR_RESET"\n");
                break;
            default: // Неизвестная команда
                printf("unknown command\n");
        }
    }

    return 0;
}
