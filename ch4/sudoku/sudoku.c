# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>

/* structure for passing data to threads */
typedef struct{
    int row;
    int col;
}parameters;

int sudoku[9][9] = {{6, 2, 4, 5, 3, 9, 1, 8, 7},
                    {5, 1, 9, 7, 2, 8, 6, 3, 4},
                    {8, 3, 7, 6, 1, 4, 2, 9, 5},
                    {1, 4, 3, 8, 6, 5, 7, 2, 9},
                    {9, 5, 8, 2, 4, 7, 3, 6, 1},
                    {7, 6, 2, 3, 9, 1, 4, 5, 8},
                    {3, 7, 1, 9, 5, 6, 8, 4, 2},
                    {4, 9, 6, 1, 8, 2, 5, 7, 3},
                    {2, 8, 5, 4, 7, 3, 9, 1, 6}}

int row_valid[9] = {0};
int col_valid[9] = {0};
int subgird_valid[9] = {0};
int cnt = 0;

int  accumulate(){
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
    
    if(sum == 0) row_valid[row] = 1;
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
    
    if(sum == 0) col_valid[col] = 1;
    pthread_exit(NULL);
}

void *subgrid_check(void *data){
    parameters *subgrid_data = (parameters*)data;
    int start_row = subgrid_data->row;
    int start_col = subfrid_data->col;
    int sum = accumulate();
    
    for(int i = start_row; i < start_row + 3; i++){
        for(int j = start_col; j < start_col + 3; j++){
            int val = sudoku[i][j];
            
            if(val < 1 || val > 9 || sum - val < 0){
                pthread_exit(NULL);
                cnt++;
            }
            sum -= val;
        }
    }
    
    if(sum == 0) subgrid_valid[cnt++] = 1;
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[9 * 3];
    int index = 0;
    
    for(int i = 0; i < 9; i++){
        parameters *data = (parameters*)malloc(sizeof(parameters));
        data->row = 1;
        data->col = 1;
        /* Now create the thread passing it data as a parameter */
        pthread_create(&threads[index++], NULL, row_check, data);
        
        parameters *data = (parameters*)malloc(sizeof(parameters));
        data->row = 1;
        data->col = 1;
        /* Now create the thread passing it data as a parameter */
        pthread_create(&threads[index++], NULL, col_check, data);
    }
    
    for(int i = 0; i < 9; i += 3){
        for(int j = 0; j < 9; j += 3){
            parameters *data = (parameters*)malloc(sizeof(parameters));
            data->row = 1;
            data->col = 1;
            /* Now create the thread passing it data as a parameter */
            pthread_create(&threads[index++], NULL, subgrid_check, data);
        }
    }
    
    for(int k = 0; k < index; k++) pthread_join(threads[k], NULL);
    
    return 0;
}
