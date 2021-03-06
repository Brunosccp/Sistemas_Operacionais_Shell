int shell_cd(char **args);
int shell_mkdir(char **args);
int shell_help(char **args);
int shell_clear(char **args);
int shell_exit(char **args);

char *builtIn_str[] = {
    "cd",
    "mkdir",
    "help",
    "clear",
    "exit"
};

int (*builtIn_func[]) (char**) = {
    &shell_cd,
    &shell_mkdir,
    &shell_help,
    &shell_clear,
    &shell_exit
};

int shell_num_bultIns(){
    return sizeof(builtIn_str) / sizeof(char*);
}


int shell_cd(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "SHELL ERROR: expected argument for cd\n");
    }else{
        if(chdir(args[1]) != 0){
            perror("shell");
        }
    }
    return 1;
}
int shell_mkdir(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "SHELL ERROR: expected name for mkdir\n");
    }else{
        char path[50] = "./";
        strcat(path, args[1]);

        mkdir(path, 0777);
    }

    return 1;
}

int shell_help(char **args){
    int i;

    printf("Shell created for academic use, by Bruno Rocca, Computer Science - SENAC\n");
    printf("Here's the list of the actually built-ins\n\n");

    for(i=0; i < shell_num_bultIns(); i++){
        printf("    %s\n", builtIn_str[i]);
    }

    printf("\nReference: brennan.io/blog\n");

    return 1;
}
int shell_clear(char **args){
    printf("\033[H\033[J");

    return 1;
}

int shell_exit(char **args){
    return 0;
}