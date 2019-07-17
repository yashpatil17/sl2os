#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 10

int A[SIZE][SIZE], B[SIZE][SIZE];

long int C[SIZE][SIZE];

int t=1;


void *mul_thread(void *arg) 
{
// *ARGS POINTS TO THE ARRAY OF ROW-COLUMN ARGUMENTS
	int i, k, row, col, *rcArgs, z;
	long int return_val=0; 
// RCARGS POINTS TO ARG	
	rcArgs = (int *) arg;
	row = rcArgs[0]; // ROW NUMBER
	col = rcArgs[1]; // COLUMN NUMBER
	k	= rcArgs[2]; // ITERATIONS
	
	// WAIT FOR PARENT
	printf("\nTHREAD NUMBER %d-%d JOINED",row+1,col+1);
	for(i=0;i<k;i++)
	{
		return_val = return_val + A[row][i] * B[i][col];
		printf("\n - THREAD NUMBER %d-%d - CALCULATED\n %d x %d = %d = %ld",row+1,col+1,A[row][i],B[i][col],A[row][i]*B[i][col],return_val\n);
		printf("\n - THREAD NUMBER %d-%d PAUSED FOR 5 UNITS",row+1,col+1);
		sleep(5);
		printf("\n - THREAD NUMBER %d-%d RESUMED",row+1,col+1);
	}
	//return ((void *) return_val);
	//EXITS WITH THE WAITING PARENT
	
	
	printf("\nTHREAD NUMBER %d-%d EXITS", row+1,col+1);
	pthread_exit((void *) return_val);
}


/* INPUT FUNCTION */
void accept_matrix(int M[SIZE][SIZE], int rows, int cols) {
	int i, j;
	printf("\n");
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++) 
		{
			printf("VALUES AT [%d][%d]: ",i+1,j+1);
			scanf("%d",&M[i][j]);
		}
	}
}

/* DISPLAY FUNCTION */
void display_matrix(int M[SIZE][SIZE], int rows, int cols) 
{
	int i, j;
	printf("\n");	
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			printf("%d  ",M[i][j]);
		}
		printf("\n");
	}
}


int main() {

	do
	{
		switch(ch)
		{
			case
		}
	}while(ch!=3);



	int rows_A, cols_A, rows_B, cols_B;
	int rcArgs[3];
	int i, j, k, *status;
	
	// DEFINING A 2-D ARRAY FOR THREADS
	pthread_t P[SIZE][SIZE];
	
	printf("\nENTER NUMBER OF ROWS OF MATRIX A: ");
	scanf("%d",&rows_A);
	printf("ENTER NUMBER OF COLUMNS OF MATRIX A: ");
	scanf("%d",&cols_A);


    printf("\nENTER NUMBER OF ROWS OF MATRIX B: ");
	scanf("%d",&rows_B);
	printf("ENTER NUMBER OF COLUMNS OF MATRIX B: ");
	scanf("%d",&cols_B);

    // CHECK FOR ROWS AND COLUMNS 
	if(cols_A != rows_B) {
		
		printf("\nINVALID OPERATION, COLUMNS AND ROWS DO NOT MATCH!!");
        
        // TAKING VALID INPUT
        printf("\nENTER NUMBER OF ROWS OF MATRIX A: ");
		scanf("%d",&rows_A);
		printf("ENTER NUMBER OF COLUMNS OF MATRIX A: ");
		scanf("%d",&cols_A);


		printf("\nENTER NUMBER OF ROWS OF MATRIX B: ");
		scanf("%d",&rows_B);
		printf("ENTER NUMBER OF COLUMNS OF MATRIX B: ");
		scanf("%d",&cols_B);
	}
       

	accept_matrix(A, rows_A, cols_A);
	accept_matrix(B, rows_B, cols_B);
	
	
		for(i=0;i<rows_A;i++) 
		{
			for(j=0;j<cols_B;j++) 
			{
				rcArgs[0] = i;
				rcArgs[1] = j;
				rcArgs[2] = cols_A;
					
					
				/* 1. SYNTAX OF CREATE: int pthread_create(pthread_t *thread, pthread_attr_t *attr, void
				                     *(*start_routine)(void *), void *arg);	
				   2. WHEN CREATING SEND THE ADDRESS OF THE THREAD FOR CREATION.
				   3. ATTRIBUTE = NULL
				   4. FUNCTION MULTIPLICATION
				   5. A void pointer is a pointer that has no associated data type with it. A void pointer can hold address of any type and can be typcasted to any type. 
				   6. HENCE SENDING INT ARGS
				 */	
				if(pthread_create(&P[i][j], NULL, mul_thread, rcArgs) != 0)
					printf("\nCANNOT CREATE THREAD.\n");
				else
				{
					printf("\nTHREAD NO %d-%d CREATED",i+1,j+1);
					sleep(2);
				}
				
			}
		}
	
		
	printf("\n\nMATRIX A : \n");
	display_matrix(A, rows_A, cols_A);
	printf("\nMATRIX B : \n");
	display_matrix(B, rows_B, cols_B);
	
	for(i=0;i<rows_A;i++) {
		for(j=0;j<cols_B;j++) 
		{
            {
				if(pthread_join(P[i][j],(void **) &status) != 0)
					perror("\nTHREAD JOIN FAILED.\n");
				// RETURNS WITH THE JOIN STATEMENT NOT THE EXIT STATEMENT!!!!
				C[i][j] = (long int)status;
			}
		}
	}
	
	printf("\n\nRESULTANT MATRIX:\n");
	for(i=0;i<rows_A;i++){
		for(j=0;j<cols_B;j++){
			printf("%ld  ",C[i][j]);
		}
		printf("\n");
	}
	printf("\n----------------------------\n\n");
	exit(EXIT_SUCCESS);
}
