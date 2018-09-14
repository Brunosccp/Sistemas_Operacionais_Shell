#include "shell_system.h"
#include "shell_builtIn.h"

void shell_loop();
char* shell_read_line();
char** shell_split_line(char *line);
int shell_launch(char **args);
int shell_execute(char **args);

void shell_loop(){
    char *line;
    char **args;
    
    int status;
    
    do{
        printf("> ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);
        
        free(line);
        free(args);

    }while(status);
}
char* shell_read_line(void){
    int position = 0;
    int bufferSize = SHELL_RL_BUFFSIZE;

    char* buffer = malloc (sizeof(char) * bufferSize);

    if(!buffer){
        fprintf(stderr, "SHELL ERROR: allocation error\n");
        exit(EXIT_FAILURE);
    }

    int c;

    while(1){
        c = getchar();

        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }else{
            buffer[position] = c;
        }
        position++;

        //reallocation
        if(position >= bufferSize){
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

    
    token = strtok(line, SHELL_TOK_DELIM);
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

        token = strtok(NULL, SHELL_TOK_DELIM);
    }
    tokens[position] = NULL;
    
    return tokens;
}
int shell_launch(char **args){
    pid_t pid, wpid;

    int status;

    pid = fork();
    if(pid == 0){
        if(execvp(args[0], args) == -1){
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }else if(pid < 0){
        //error forking
        perror("shell");
    }else{
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
int shell_execute(char **args){
    int i;
    
    if(args[0] == NULL){
        return 1;
    }

    for(i = 0; i < shell_num_bultIns(); i++){
        if(strcmp(args[0], builtIn_str[i]) == 0){
            return (*builtIn_func[i]) (args);
        }
    }

    return shell_launch(args);
}