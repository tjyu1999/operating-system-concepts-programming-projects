# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

/* structure for passing data to threads */
typedef struct{
    int row;
    int col;
}parameters;

int valid = 0;
int sudoku[9][9];

int accumulate(){
    int sum = 0;
    for(int n = 1; n <= 9; n++) sum += n;
    
    return sum;
}

void *row_check(void *data){
    parameters *row_data = (parameters*)data;
    int row = row_data->row;
    int sum = accumulate();
    
    for(int i = 0; i < 9; i++){
        int val = sudoku[row][i];
        
        if(val < 1 || val > 9 || sum - val < 0) pthread_exit(NULL);
        sum -= val;
    }
    
    if(sum == 0) valid++;
    pthread_exit(NULL);
}

void *col_check(void *data){
    parameters *col_data = (parameters*)data;
    int col = col_data->col;
    int sum = accumulate();
    
    for(int i = 0; i < 9; i++){
        int val = sudoku[i][col];
        
        if(val < 1 || val > 9 || sum - val < 0) pthread_exit(NULL);
        sum -= val;
    }
    
    if(sum == 0) valid++;
    pthread_exit(NULL);
}

void *subgrid_check(void *data){
    parameters *subgrid_data = (parameters*)data;
    int start_row = subgrid_data->row;
    int start_col = subgrid_data->col;
    int sum = accumulate();
    
    for(int i = start_row; i < start_row + 3; i++){
        for(int j = start_col; j < start_col + 3; j++){
            int val = sudoku[i][j];
            
            if(val < 1 || val > 9 || sum - val < 0) pthread_exit(NULL);
            sum -= val;
        }
    }
    
    if(sum == 0) valid++;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    if(argc < 2) return 1;
    
    FILE *file = fopen(argv[1], "r");
    if(!file) return 1;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++) fscanf(file, "%d", &sudoku[i][j]);
    }
    
    int i;
    int j;
    int index = 0;
    pthread_t threads[3 * 9];
    
    for(i = 0; i < 9; i++){
        parameters *data = (parameters*)malloc(sizeof(parameters));
        data->row = i;
        /* Now create the thread passing it data as a parameter */
        pthread_create(&threads[index++], NULL, row_check, data);
    }
    
    for(i = 0; i < 9; i++){
        parameters *data = (parameters*)malloc(sizeof(parameters));
        data->col = i;
        /* Now create the thread passing it data as a parameter */
        pthread_create(&threads[index++], NULL, col_check, data);
    }
    
    for(i = 0; i < 9; i += 3){
        for(j = 0; j < 9; j += 3){
            parameters *data = (parameters*)malloc(sizeof(parameters));
            data->row = i;
            data->col = j;
            /* Now create the thread passing it data as a parameter */
            pthread_create(&threads[index++], NULL, subgrid_check, data);
        }
    }
    
    for(int k = 0; k < index; k++) pthread_join(threads[k], NULL);
    if(valid == 3 * 9) printf("valid\n");
    else printf("invalid\n");
    
    fclose(file);
    return 0;
}
