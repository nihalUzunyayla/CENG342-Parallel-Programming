
//Nihal UZUNYAYLA 19050111018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <hellomake.h>

void multiplyMatrixAndVector(double**, double*, double*, int, int);

int main(int argc, char *argv[]) {

    int rows = atoi(argv[1]);
    int columns = atoi(argv[2]);
    char *fileName = argv[3];

    srand48(19050111018);

    double **randomMatrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        randomMatrix[i] = (double *)malloc(columns * sizeof(double));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            randomMatrix[i][j] = 1.0 + (double)rand() / RAND_MAX * 99.0;
        }
    }

    double *randomVector = (double *)malloc(columns * sizeof(double));
    double *result = (double *)malloc(rows * sizeof(double));

    for (int i = 0; i < columns; i++) {
        randomVector[i] = 1.0 + (double)rand() / RAND_MAX * 50.0;
    }

    multiplyMatrixAndVector(randomMatrix, randomVector, result, rows, columns);

    // call a function in another file
    fileWritingMake(fileName, result, rows);
    
    for (int i = 0; i < rows; i++) {
        free(randomMatrix[i]);
    }
    free(randomMatrix);
    free(randomVector);
    free(result);

    return 0;
}

void multiplyMatrixAndVector(double **matrix, double *vector, double *result, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < columns; j++) {
            sum += matrix[i][j] * vector[j];
        }
        result[i] = sum;
    }
}
