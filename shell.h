#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHELL_RL_BUFFSIZE 1024

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

void shell_loop();
char* shell_read_line();
char** shell_split_line();

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

    if(!buffer){
        fprintf(stderr, "SHELL ERROR: allocation error");
        exit(EXIT_FAILURE);
    }

    int c;

    while(1){
        c = getchar();

        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
        }else{
            buffer[position] = c;
        }
        position++;

        //reallocation
        if(position >= SHELL_RL_BUFFSIZE){
            bufferSize += SHELL_RL_BUFFSIZE;

            buffer = realloc(buffer, bufferSize);

            //reallocation error
            if(!buffer){
                fprintf(stderr, "SHELL ERROR: reallocation error");
                exit(EXIT_FAILURE);
            }
            
        }

    }

}
char** shell_split_line(char* line){
    int position = 0;
    int bufferSize = SHELL_RL_BUFFSIZE;

    char** tokens = malloc(sizeof(char) * bufferSize);
    char* token;

    
    token = strtok(line, LSH_TOK_DELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;

        //reallocation
        if(position >= bufferSize){
            bufferSize += SHELL_RL_BUFFSIZE;
            tokens = realloc(tokens, bufferSize * sizeof(char*));

            //reallocation error
            if(!tokens){
                fprintf(stderr, "SHELL ERROR: reallocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }
    
    tokens[position] = NULL;
    return tokens;
}
