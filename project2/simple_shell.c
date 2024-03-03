# include <stdio.h>

/*
 * Function: init_args
 * ----------------------------
 *   Initialize args, i.e., making all of its content NULL
 *
 *   args: the array to initialize
 */
void init_args(char* args[]){
    for(size_t i = 0; i != MAX_LINE / 2 + 1; i++) args[i] = NULL;
}

/*
 * Function: init_command
 * ----------------------------
 *   Initialize command, i.e., making it an empty string
 *
 *   command: the string to initialize
 */
void init_command(char* command){
    strcpy(command, "");
}

/*
 * Function: refresh_args
 * ----------------------------
 *   Refresh the content of args, i.e., free old content and set to NULL
 *
 *   args: the array to refresh
 */
void refresh_args(char* args[]){
    while(*args){
        free(*args);
        *args++ = NULL;
    }
}

/*
 * Function: parse_input
 * ----------------------------
 *   Parse input and store arguments
 *
 *   args: the array to put arguments
 *   command: the input command
 *
 *   returns: the number of arguments
 */
size_t parse_input(char* args[], char* original_command){
    size_t num = 0;
    char command[MAX_LINE + 1];
    strcpy(command, original_command);  // make a copy since `strtok` will modify it
    char* token = strtok(command, DELIMITERS);
    
    while(token != NULL){
        args[num] = malloc(strlen(token) + 1);
        strcpy(args[num], token);
        ++num;
        token = strtok(NULL, DELIMITERS);
    }
    
    return num;
}

/*
 * Function: get_input
 * ----------------------------
 *   Get command from input of history
 *
 *   command: last command
 *
 *   returns: success or not
 */
int get_input(char* command){
    char input_buffer[MAX_LINE + 1];
    if(fgets(input_buffer, MAX_LINE + 1, stdin) == NULL){
        fprintf(stderr, "Failed to read input!\n");
        return 0;
    }
    
    if(strncmp(input_buffer, "!!", 2) == 0){
        if(strlen(command) == 0){  // no history yet
            fprintf(stderr, "No history available yet!\n");
            return 0;
        }
        
        printf("%s", command);    // keep the command unchanged and print it
        return 1;
    }
    
    strcpy(command, input_buffer);  // update the command
    return 1;
}

/*
 * Function: check_ampersand
 * ----------------------------
 *   Check whether an ampersand (&) is in the end of args. If so, remove it
 *   from args and possibly reduce the size of args.
 *
 *   args: the array to check
 *   size: the pointer to array size
 *
 *   returns: whether an ampersand is in the end
 */
int check_ampersand(char** args, size_t* size){
    size_t len = strlen(args[*size - 1]);
    if(args[*size - 1][len - 1] != '&'){
        return 0;
    }
    
    if(len == 1){  // remove this argument if it only contains '&'
        free(args[*size - 1]);
        args[*size - 1] = NULL;
        --(*size);  // reduce its size
    }
    else args[*size - 1][len - 1] = '\0';
    
    return 1;
}
