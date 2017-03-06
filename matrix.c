#include "matrix.h"

Matrix* create_matrix_from_file(FILE* file){
  if(!file)
    return NULL;

  int row;
  int col;
  if(fscanf(file, "%d\n%d\n", &row, &col) != 2)
    return NULL;

  Matrix* matrix = create_matrix(row, col);
  if(!matrix)
    return NULL;

  double temp;
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      if(fscanf(file, "%lf", &temp) != 1){
        free_matrix(matrix);
        return NULL;
      }
      set_elem(matrix, i, j, temp);
    }
  }

  return matrix;
}

Matrix* create_matrix(int row, int col){
  if(row <= 0 || col <= 0)
    return NULL;

  Matrix* matrix = malloc(sizeof(Matrix));
  if(!matrix)
    return NULL;

  matrix->arr = malloc(sizeof(double*) * col);
  if(!matrix->arr){
    free(matrix);
    return NULL;
  }

  for(int i = 0; i < row; i++){
    matrix->arr[i] = malloc(sizeof(double) * col);
    if(matrix->arr[i] == NULL){
      free_matrix(matrix);
      return NULL;
    }
  }

  matrix->row = row;
  matrix->col = col;
  return matrix;
}

void free_matrix(Matrix* matrix){
  if(!matrix)
    return;

  for(int i = 0; i < matrix->row; i++){
    free(matrix->arr[i]);
  }
  free(matrix->arr);

  free(matrix);
}

double get_elem(Matrix* matrix, int row, int col){
  // Не могу ничего не вернуть, но чтоб не упала программа в случае обращения
  // в далекие уголки памяти нужно вернуть что-то наиболее нейтральное
  if(row < 0 || col < 0 || row >= get_rows(matrix) || col >= get_cols(matrix)){
    fprintf(stderr, "E%d|%d", row, col);
    return 0.0;
  }
  return matrix->arr[row][col];
}

void set_elem(Matrix* matrix, int row, int col, double val){
  if(!matrix || get_rows(matrix) <= row || get_cols(matrix) <= col
    || row < 0 || col < 0)
    return;
  if(!matrix->arr || !matrix->arr[row])
    return;
  matrix->arr[row][col] = val;
}

int get_rows(Matrix* matrix){
  return matrix ? matrix->row : 0;
}

int get_cols(Matrix* matrix){
  return matrix ? matrix->col : 0;
}
