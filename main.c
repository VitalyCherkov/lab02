#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

Matrix* readMatrix(char* fileName);
void printMatrixT(Matrix* matrix);

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("1 argument - name of file\n");
    return EXIT_FAILURE;
  }

  Matrix* matrix = readMatrix(argv[1]);
  if(!matrix){
    printf("Can not read file\n");
    return EXIT_FAILURE;
  }
  printMatrixT(matrix);

  free_matrix(matrix);
  return EXIT_SUCCESS;
}

Matrix* readMatrix(char* fileName){
  if(!fileName || strlen(fileName) == 0){
    fprintf(stderr, "Incorrect fileName\n");
    return NULL;
  }

  FILE* file = fopen(fileName, "r");
  if(!file){
    fprintf(stderr, "Can not open file\n");
    return NULL;
  }

  Matrix* matrix = create_matrix_from_file(file);
  if(fclose(file) != 0){
    fprintf(stderr, "Something wrong with closing of file\n");
  }
  if(!matrix){
    fprintf(stderr, "Matrix wasn't read from file\n");
    return NULL;
  }

  return matrix;
}
void printMatrixT(Matrix* matrix){
  if(!matrix || !matrix->arr){
    fprintf(stderr, "Empty matrix\n");
    return;
  }

  for(int i = 0; i < get_cols(matrix); i++){
    for(int j = get_rows(matrix) - 1; j >= 0; j--){
      printf("%lf ", get_elem(matrix, j, i));
    }
    printf("\n");
  }
}
