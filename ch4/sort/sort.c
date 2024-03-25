# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/wait.h>

# define SIZE

typedef struct data{
    int left;
    int mid;
    int right;
    int arr[];
}data;

int main(int argc, char *argv[]){
    int i;
    int index = 0;
    char c;
    char buffer[SIZE];
    
    FILE *input, *output;
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    
    pthread_t = left, right, merge;
    data
    
    while((c = fgetc(input)) != EOF){
        if(c == ' '){
            i = 0;
            .arr[] = atoi(buffer);
            memset(buffer, '\0', SIZE * sizeof(char));           
            index++;
        }
        else if(c == '\n'){
            i = 0;
            [] = atoi(buffer);
            memset(buffer, '\0', SIZE * sizeof(char));           
            
            .left = 0;
            .mid = index / 2;
            .right = index;
            
            pthread_create(&left, NULL, left, (void*)&);
            pthread_create(&right, NULL, right, (void*)&);
            pthread_create(&merge, NULL, merge, (void*)&);
            pthread_join(left, NULL);
            pthread_join(right, NULL);
            pthread)join(merge, NULL);
            
            for(){
            
            }
        }
        else{
        
        }
    }
    
    
    
    
    /* child process */
    if(pid == 0){
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, NULL);
        pthread_join(tid, NULL);
        printf("CHILD: value = %d", value);
    }
    /* parent process */
    else if(pid > 0){
        wait(NULL);
        printf("PARENT: value = %d", value);
    }
}

void *left(){

}

void *right(){
    data * = (data*);
    merge_sort();
    pthread_exit(NULL);
}

void *merge(void *arg){
    data * = (data*) arg;
    
    pthread_exit(NULL);
}

void merge_sort(int arr[], int left, int mid, int right){
    int l = mid - left + 1;
    int r = right - mid;
    int 
}
