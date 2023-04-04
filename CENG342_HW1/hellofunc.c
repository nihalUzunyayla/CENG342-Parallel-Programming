//Nihal Uzunyayla 19050111018

#include <stdio.h>
#include <stdlib.h>  
#include <hellomake.h>

void fileWritingMake(char* fileName, double* result, int rows){
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
    printf("File created successfully.\n");
    return;
}
