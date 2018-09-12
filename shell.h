#include <stdio.h>
#include <stdlib.h>
#define SHELL_RL_BUFFSIZE 1024

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

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
    int bufferSize = SHELL_RL_BUFFSIZE;

    char* buffer = malloc (sizeof(char) * bufferSize);

    int c;

    while(1){
        c = getchar();

        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
        }else{
            buffer[position] = c;
        }
        position++;

        if(position >= SHELL_RL_BUFFSIZE){
            bufferSize += SHELL_RL_BUFFSIZE;

            buffer = realloc(buffer, bufferSize);

            //allocation error
            if(!buffer){
                fprintf(stderr, "shell: reallocation error")
                exit(EXIT_FAILURE);
            }
            
        }

    }

}
char** shell_split_line(){

}