#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

/*
Name: Utku Selim Koçoğlu
Date: 15.11.2021
The program: Tic-Tac-Toe with Threads
*/

int terminating = 0;
int winner = 0;
char *** ptr;
int tableSize;
int fill = 0;
pthread_mutex_t lockG = PTHREAD_MUTEX_INITIALIZER;


typedef struct table {
    char ***data;
    int rowN;
} table_t;

void init(table_t *t, int nRow, int nCol) {
    t->data = (char ***) malloc(nRow * sizeof(char**));
    for(int i=0; i<nRow; i++){
        t->data[i] = (char **) malloc(nCol * sizeof(char *));
    }
    t->rowN = nRow;
}


void* game (void * arg){
    pthread_mutex_lock(&lockG);
    char * p = (char *) arg;

    int row = rand() % tableSize;
    int col = rand() % tableSize;
    for(;(ptr[row][col] == "X" || ptr[row][col] == "O") && fill < tableSize*tableSize;){
        row = rand() % tableSize;
        col = rand() % tableSize;
    }
    if (fill >= tableSize*tableSize || terminating == 1){
        terminating = 1;
    }
    else{
        ptr[row][col] = p;
        fill++; 
    

        for (int i = 0; i < tableSize && terminating == 0; i++)
        {
            for (int j = 0; j < tableSize && terminating == 0; j++)
            {
                if (ptr[i][j] == p) 
                {
                    winner++;
                }
                
            }
            if (winner == tableSize)    
            {
                terminating = 1;
            }
            else{
                winner = 0;
            }
            
            
        }
        for (int i = 0; i < tableSize && terminating == 0; i++)
        {
            for (int j = 0; j < tableSize && terminating == 0; j++)
            {
                if (ptr[j][i] == p) 
                {
                    winner++;
                }
                
            }
            if (winner == tableSize)    
            {
                terminating = 1;
            }
            else{
                winner = 0;
            }
            
        }

        for (int i = 0; i < tableSize && terminating == 0; i++)
        {
            if (ptr[i][i] == p)
            {
                winner++;
            }
            
        }
        if (winner == tableSize)
        {
            terminating = 1;
        }
        else {
            winner = 0;
        }

        for (int i = 0, j = tableSize-1; i < tableSize && j > -1 && terminating == 0; i++, j--)
        {
            if (ptr[i][j] == p)
            {
                winner++;
            }
            
        }
        if (winner == tableSize)
        {
            terminating = 1;
        }
        else {
            winner = 0;
        }

        printf("Player %s played on (%d, %d)\n", p, row, col);
        if(terminating == 1){
            printf("Game end\n");
            if (fill == tableSize*tableSize && terminating == 0)
            {
                printf("It is a tie\n");
                for (int i = 0; i < tableSize; i++)
                {
                    for (int j = 0; j < tableSize; j++)
                    {
                        printf("[%s]", ptr[i][j]);
                    }
                    printf("\n");
                }
                terminating = 1;
            }
            else if (fill == tableSize*tableSize && terminating == 1){
                printf("Winner is %s\n", p);
                for (int i = 0; i < tableSize; i++)
                {
                    for (int j = 0; j < tableSize; j++)
                    {   
                        printf("[%s]", ptr[i][j]);
                    }
                    printf("\n");
                }
            }
            else{
                printf("Winner is %s\n", p);
                for (int i = 0; i < tableSize; i++)
                {
                    for (int j = 0; j < tableSize; j++)
                    {   
                        printf("[%s]", ptr[i][j]);
                    }
                    printf("\n");
                }
            }
            
        }
        else if (fill == tableSize*tableSize && terminating == 0){
            printf("It is a tie\n");
            for (int i = 0; i < tableSize; i++)
            {
                for (int j = 0; j < tableSize; j++)
                {
                    printf("[%s]", ptr[i][j]);
                }
                printf("\n");
            }
            terminating = 1;
        }
    }
    pthread_mutex_unlock(&lockG);

    return NULL;   
}


int main(int argc, char **argv){

    srand(time(NULL));
    pthread_t playerX, playerO;
    int N;
    table_t *gameTable;
    if (argc > 1){
        
        N = atoi(argv[1]);
        init(gameTable, N, N);
        ptr = gameTable->data;
        printf("Board Size: %dx%d\n", N, N);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                ptr[i][j] = " ";
            }
        }
        tableSize = N;

        for (int i = 0; i < N*N && terminating == 0; i++)
        {
            pthread_create(&playerX, NULL, game, "X");
            pthread_join(playerX, NULL);
            pthread_create(&playerO, NULL, game, "O");
            pthread_join(playerO, NULL);

        }
        
    }
    else{
        ;
    }
    
    return 0;
}
