#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <hellomake.h>

void multiplyMatrixAndVector(double**, double*, double*, int, int);

int main(int argc, char *argv[]) {

    //parse the arguments
    int rows = atoi(argv[1]);
    int columns = atoi(argv[2]);
    char *fileName = argv[3];
    
    //srand48 for seed number
    srand48(19050111018);
    
    //allocate memory for matrix
    double **randomMatrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        randomMatrix[i] = (double *)malloc(columns * sizeof(double));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            randomMatrix[i][j] = 1.0 + (double)rand() / RAND_MAX * 99.0;
        }
    }

    //allocate memory for vector and result array
    double *randomVector = (double *)malloc(columns * sizeof(double));
    double *result = (double *)malloc(rows * sizeof(double));

    for (int i = 0; i < columns; i++) {
        randomVector[i] = 1.0 + (double)rand() / RAND_MAX * 50.0;
    }

    multiplyMatrixAndVector(randomMatrix, randomVector, result, rows, columns);


    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error: cannot open output file.\n");
        return 1;
    }

    fprintf(file, "%s\n", "Result:\n");
    for (int i = 0; i < rows; i++) {
        fprintf(file, "%.2lf\n", result[i]);
    }
    fclose(file);
    printf("File created successfully.\n");

    //free memory
    for (int i = 0; i < rows; i++) {
        free(randomMatrix[i]);
    }
    free(randomMatrix);
    free(randomVector);
    free(result);

    // call a function in another file
    myPrintHelloMake();

    return 0;
}

//Multiply matrix and vector.
void multiplyMatrixAndVector(double **matrix, double *vector, double *result, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < columns; j++) {
            sum += matrix[i][j] * vector[j];
        }
        result[i] = sum;
    }
}

