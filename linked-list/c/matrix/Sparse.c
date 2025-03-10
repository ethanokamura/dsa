/**
 * @author Ethan Okamura
 * @file Sparce.c
 * @brief Performs tests on the defined methods in the Matrix ADT.
 */

#include <stdlib.h>
#include <stdio.h>

#include "Matrix.h"

// Operation Enum
enum operation {
  INIT,
  SUM,
  DIFF,
  PROD,
  SCALE,
  COPY,
  TRANSPOSE,
};

/**
 * @brief Generic function to handle failures.
 * @param message The error message to display.
 */
void handleFailure(const char* message) {
  fprintf(stderr, "ERROR: %s\n", message);
  exit(EXIT_FAILURE);
}

/**
 * @brief Handles operation failures.
 * @param code The id of the failed operation.
 */
void handleOperationFailure(int code) {
  const char* codeName[7] = {
    "init", "sum()", "diff()", "product()", 
    "scalarMult()", "copy()", "transpose()"
  };
  fprintf(stderr, "ERROR: Failure performing operation: %s\n", codeName[code]);
  exit(EXIT_FAILURE);
}

/**
 * @brief Validates file existance.
 * @param file The file to inspect.
 */
void validateFile(FILE* file) {
  if (!file) handleFailure("FILE DOES NOT EXIST");
}

/**
 * @brief Builds the Matrix ADT.
 * @param FILE The input file to be read from.
 * @param n The dimensions of the Matrix ADT.
 * @param nnz The number of non-zero entries.
 * @returns A new Matrix ADT.
 */
Matrix initMatrix(FILE* file, int n, int nnz) {
  Matrix M = newMatrix(n);
  if (size(M) != n) {
    handleFailure("Incorrect sizing.");
  }
  int i = -1, j = -1;
  double x = -1;
  int e = 0;
  while (nnz-- > 0) {
    if (NNZ(M) != e) {
      handleFailure("Incorrect NNZ count.");
    }
    if (fscanf(file, "%d %d %lf", &i, &j, &x) != 3) {
      handleFailure("Invalid matrix input format.");
    }
    if (i < 1 || i > n || j < 1 || j > n) {
      handleFailure("Matrix index out of bounds.");
    }
    changeEntry(M, i, j, x);
    e++;
  }

  return M;
}

/**
 * @brief Handles operations between 2 matrices
 * @param FILE The output file to write to.
 * @param A The first Matrix ADT.
 * @param B The second Matrix ADT.
 * @param code The operation code (from enum).
 */
void handleOperations(FILE* file, Matrix A, Matrix B, int code) {
  Matrix M = NULL;
  switch (code) {
  case SUM:
    M = sum(A,B);
    break;
  case DIFF:
    M = diff(A,B);
    break;
  case PROD:
    M = product(A,B);
    break;
  default:
    handleOperationFailure(code);
    break;
  }
  if (!M) handleFailure("NULL operation.");
  printMatrix(file, M);
  fprintf(file, "\n");
  freeMatrix(&M);
}

/**
 * @brief Handles operations between 2 matrices
 * @param FILE The output file to write to.
 * @param A The Matrix ADT to perform the operation on.
 * @param code The operation code (from enum).
 * @param scalar The optional scalar to perform scalarMult.
 */
void handleOperationsOnSingle(FILE* file, Matrix A, int code, double scalar) {
  Matrix M = NULL;
  switch (code) {
  case COPY:
    M = copy(A);
    break;
  case TRANSPOSE:
    M = transpose(A);
    break;
  case SCALE:
    M = scalarMult(scalar, A);
    break;
  default:
    handleOperationFailure(code);
    break;
  }
  if (!M) handleFailure("NULL operation.");
  printMatrix(file, M);
  fprintf(file, "\n");
  freeMatrix(&M);
}

/**
 * @brief Oversees all operations.
 * @param FILE The output file to write to.
 * @param A The first Matrix ADT.
 * @param B The second Matrix ADT.
 */
void operationGauntlet(FILE* file, Matrix A, Matrix B) {
  fprintf(file, "A has %d non-zero entries:\n", NNZ(A));
  printMatrix(file, A);
  fprintf(file, "\n");
  fprintf(file, "B has %d non-zero entries:\n", NNZ(B));
  printMatrix(file, B);
  fprintf(file, "\n");
  double scalar = 1.5;
  fprintf(file, "(%.1f)*A =\n", scalar);
  handleOperationsOnSingle(file, A, SCALE, scalar);
  fprintf(file, "A+B =\n");
  handleOperations(file, A, B, SUM);
  fprintf(file, "A+A =\n");
  handleOperations(file, A, A, SUM);
  fprintf(file, "B-A =\n");
  handleOperations(file, B, A, DIFF);
  fprintf(file, "A-A =\n");
  handleOperations(file, A, A, DIFF);
  fprintf(file, "Transpose(A) =\n");
  handleOperationsOnSingle(file, A, TRANSPOSE, 0);
  fprintf(file, "A*B =\n");
  handleOperations(file, A, B, PROD);
  fprintf(file, "B*B =\n");
  handleOperations(file, B, B, PROD);
}

/**
 * @brief The main logic of the program that executes the following:
 *    1. Assembles the Matrix ADTs.
 *    2. Runs Elementary Operations on Matrices.
 *    3. Outputs the Calculations.
 *
 * @param argc The number of arguments.
 * @param argv An array of arguments.
 *
 * @note This takes 2 arguments:
 *    1. An input file
 *    2. An output file
 */
int main(int argc, char** argv) {
  // Get files
  if (argc != 3) handleFailure("Requires two arguements.");
  char* inputFileName = argv[1];
  char* outputFileName = argv[2];

  // Open and validate files
  FILE* inputFile = fopen(inputFileName, "r");
  validateFile(inputFile);
  FILE* outputFile = fopen(outputFileName, "w");
  validateFile(outputFile);

  // Get size
  int n = -1, nnzA = -1, nnzB = -1;
  if(fscanf(inputFile, "%d %d %d", &n, &nnzA, &nnzB) != 3) {
    fclose(inputFile);
    handleFailure("Failed to init matrix.");
  }

  // Ensure correct reading
  if (n == -1 || nnzA == -1 || nnzB == -1) {
    fclose(inputFile);
    handleFailure("Failed to get initial values.");
  }

  // Init matrices
  Matrix A = initMatrix(inputFile, n, nnzA);
  Matrix B = initMatrix(inputFile, n, nnzB);

  // Run the operations
  operationGauntlet(outputFile, A, B);

  // Close files
  fclose(inputFile);
  fclose(outputFile);

  // Free alocated memory
  freeMatrix(&A);
  freeMatrix(&B);
  return 0;
}
