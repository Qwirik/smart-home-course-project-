#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

//colors (Заимствован)
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"



//constant
#define MAX_LEN_STR 255


int log_in(char *login_i, char *password_i){
    unsigned long login_h = hash(login_i);
    unsigned long password_h = hash(password_i);
    unsigned long password = 210706230106;
    unsigned long login = 6953956466300;
    if(login != login_h){
        printf(COLOR_RED "invalid login" COLOR_RESET "\n");
        return false;
    }
    if(password != password_h){
        printf(COLOR_RED "access denied" COLOR_RESET "\n");
        return false;
    }
    else{
        printf(COLOR_GREEN "access successful" COLOR_RESET "\n");
        return true;
    }
}


int find(char *word, char *mass[]){
    for(int i = 0; mass[i] != NULL; i++){
        if (strcmp(mass[i], word) == 0){
            return i;
        }
    }
    return -1;
}


int main() {
    char login[MAX_LEN_STR];
    char password[MAX_LEN_STR];
    static char *commands[] = {"exit" ,"test1", "test2", NULL};
    printf("login ");
    scanf("%s", login);

    printf("password for %s ", login);
    scanf("%s", password);

    bool acsess = log_in(login, password);
     
    
    while(acsess){      
        char input[MAX_LEN_STR];
                
        printf("[%s] ",login);

        scanf("%s", input);
        
        int command_index = find(input,commands);

        printf("[JARVIS] ");
        switch(command_index){
            case 0:
                printf("exiting... \n");
                acsess = false;
                break;
            case 1:
                printf("test1\n");
                break;
            case 2:
                int input2;
                scanf("%d", &input2);
                printf("test2 %d \n", input2);
                break;
            default:
                printf("unknown command\n");

        }
    }


    return 0;
}



