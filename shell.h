#include <stdio.h>
#include <stdlib.h>
#define SHELL_RL_BUFFSIZE 1024


void shell_loop(){
    char *line;
    char **args;
    
    int status;
    
    do{
        printf("> ");
        line = shell_read_line();
        args = shell_split_line(line);


    }while(status);

}
char* shell_read_line(){
    int position = 0;

    char* buffer = malloc (sizeof(char) * SHELL_RL_BUFFSIZE);

    int c;

    while(1){
        c = getchar();

        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
        }else{
            buffer[position] = c;
        }
        
    }

}
char** shell_split_line(){

}