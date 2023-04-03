
//Nihal UZUNYAYLA 19050111018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <hellomake.h> ---> I change the Makefile file 
#include "mpi.h"

#define MASTER_RANK 0

void matrixGeneration(int, int, double**);
void vectorGeneration(int, double*);
void multiplyMatrixAndVector(double**, double*, double*, int, int, int, int);
void fileCreation(char*, double*, int); 

int main(int argc, char *argv[]) {

    int pRank, pCount;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &pCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &pRank);
      
    if (argc != 4) {
        if (pRank == MASTER_RANK) {
            printf("Usage: mpirun -n <num_processes> ./%s <rows> <columns> <output_file>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    char *fileName = argv[3];

    double **randomMatrix;
    double *randomVector;
    double *finResult;

    randomMatrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        randomMatrix[i] = (double *)malloc(cols * sizeof(double));
    }
    matrixGeneration(rows, cols, randomMatrix);

    randomVector = (double *)malloc(cols * sizeof(double));
    vectorGeneration(cols, randomVector);

    finResult = (double *)malloc(rows * sizeof(double));
    multiplyMatrixAndVector(randomMatrix, randomVector, finResult, rows, cols, pRank, pCount);
    
    if (pRank == MASTER_RANK) {
        fileCreation(fileName, finResult, rows);
    }

    MPI_Finalize();

    //call a function in another file
    //myPrintHelloMake();

    return 0;

}

void matrixGeneration(int rows, int cols, double **matrix)
{
    srand48(19050111018);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 1.0 + (double)rand() / RAND_MAX * 99.0;
        }
    }
}

void vectorGeneration(int cols, double *vector)
{
    srand48(19050111018);

    for (int i = 0; i < cols; i++) {
        vector[i] = 1.0 + (double)rand() / RAND_MAX * 99.0;
    }

}

void multiplyMatrixAndVector(double **matrix, double *vector, double *finResult, int rows, int cols, int pRank, int pCount) 
{
    double *locResult = (double *)malloc(rows * sizeof(double));

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    for (int i = pRank; i < rows; i += pCount) {
        double sum = 0.0;
        for (int j = 0; j < cols; j++) {
            sum += matrix[i][j] * vector[j];
        }
        locResult[i] = sum;
    }

    if (pRank == MASTER_RANK) {
        
        for(int i = 0; i < rows; i++){
            finResult[i] = 0;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(locResult, finResult, rows, MPI_DOUBLE, MPI_SUM, MASTER_RANK, MPI_COMM_WORLD);
    
    if (pRank == MASTER_RANK) {
        double end_time = MPI_Wtime();
        printf("\nElapsed time is %f seconds for parallel mxv with %d processes\n", end_time - start_time, pCount);
    }
    
}

void fileCreation(char *fileName, double *result, int rows) 
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error: cannot open output file.\n");
        return;
    }

    fprintf(file, "%s\n", "Result:\n");
    for (int i = 0; i < rows; i++) {
        fprintf(file, "%.2lf\n", result[i]);
    }
    fclose(file);
    printf("File created successfully.\n\n");
}
