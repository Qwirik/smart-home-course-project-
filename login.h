#ifndef LOGIN_H
#define LOGIN_H

#include <stdbool.h>

// Цвета для вывода в терминал
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// Константы
#define MAX_LEN_STR 255

// Функция для проверки логина и пароля
int log_in(char *login_i, char *password_i);

#endif // LOGIN_H
