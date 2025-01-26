#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/time.h>
#include "hash.h"
#include "login.h"

#define ARDUINOIP "http://192.168.1.34"  // Исправлено на правильный URL

// Функция для поиска команды в массиве
int find(char *word, char *mass[]) {
    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], word) == 0) {
            return i;
        }
    }
    return -1;
}

// Функция для отправки HTTP-запроса и получения ответа
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char *)userp)[size * nmemb] = '\0';
    strncat(userp, contents, size * nmemb);
    return size * nmemb;
}

char* send_http_request(const char *url) {
    CURL *curl;
    CURLcode res;
    char *response = malloc(1024);
    memset(response, 0, 1024);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "[JARVIS] curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            free(response);
            return NULL;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return response;
}

// Функция для управления светодиодами
void control_led(int led_num, int state) {
    const char *led_pins[] = {"14", "12", "13", "15"};
    const char *states[] = {"0", "1"};
    char url[1024];
    snprintf(url, sizeof(url), "%s/led?pin=%s&state=%s", ARDUINOIP, led_pins[led_num - 1], states[state]);
    if (send_http_request(url)) {
        printf("led %d %s\n", led_num, state ? COLOR_GREEN "on" COLOR_RESET : COLOR_RED "off" COLOR_RESET);
    } else {
        printf("Failed to control LED %d\n", led_num);
    }
}

// Функция для получения статуса светодиодов
void get_led_status() {
    char *response = send_http_request(ARDUINOIP "/status");
    if (response) {
        printf("Status: %s\n", response);
        free(response);
    } else {
        printf("Failed to get LED status\n");
    }
}

// Функция для измерения времени в миллисекундах
long millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// Функция для проверки соединения с сервером и возврата задержки
void ping() {
    char url[1024];
    snprintf(url, sizeof(url), "%s/ping", ARDUINOIP);

    CURL *curl;
    CURLcode res;
    char *response = malloc(1024);
    memset(response, 0, 1024);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Засекаем время начала запроса
        long start_time = millis();

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        res = curl_easy_perform(curl);

        // Засекаем время окончания запроса
        long end_time = millis();

        if (res != CURLE_OK) {
            fprintf(stderr, "[JARVIS] curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Вычисляем задержку в миллисекундах
            long latency = end_time - start_time;
            printf("%ld ms\n", latency);
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    free(response);
}
int main() {
    int led_status[] = {0, 0, 0, 0};
    char login[MAX_LEN_STR];
    char password[MAX_LEN_STR];
    static char *commands[] = {"exit", "help", "status", "led_1 0", "led_1 1", "led_2 0", "led_2 1", "led_3 0", "led_3 1", "led_4 0", "led_4 1", "clear", "ping", NULL};
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
        if (a){
            printf("For a short summary of all commands, run 'help'\n");
            a = false;
        }
        char prompt[MAX_LEN_STR];
        snprintf(prompt, sizeof(prompt), "[%s] ", login);
        char *input = readline(prompt);
        if (input && *input) {
            add_history(input);
        }

        // Поиск команды
        int command_index = find(input, commands);

        // Обработка команд
        printf("[JARVIS] ");
        switch (command_index) {
            case 0: // "exit"
                char temp[MAX_LEN_STR];
                printf("you are sure? (yes or no):");
                scanf("%s",temp);
                if (find(temp, yes) != -1) {
                    printf("exiting... \n");
                    access = false;
                } else {
                    getchar();
                }
                break;
            case 1: // "help"
                printf("\n\
exit                                      for exit from terminal\n\
status                                    for print status pin\n\
led_<num of pin> <status_pin>             for control pin\n\
clear                                     for clear terminal\n\
ping                                      for check connection\n");
                break;
            case 2: // "status"
                get_led_status();
                break;
            case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10 : //control led
                {
                    char *token = strtok(input, " ");
                    int led_num = token[4] - '0';
                    token = strtok(NULL, " ");
                    int state = atoi(token);
                    led_status[led_num - 1] = state;
                    control_led(led_num, state);
                }
                break;
            case 11: // "clear"
                system("clear");
                printf("\n");
                break;
            case 12: //"ping"
                ping();
                break;
            default: // Неизвестная команда
                printf("unknown command\n");
        }

        free(input);
    }

    return 0;
}
