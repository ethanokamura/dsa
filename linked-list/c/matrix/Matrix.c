/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file Matrix.c
 * @brief Implementation of Matrix ADT
 * @status: in progress
 */

#include "Matrix.h"

#include <stdlib.h>

//#############################################//
//############## ERROR HANDLING ###############//
//#############################################//

/**
 * @brief Handles errors related to NULL matrix references.
 * @param message The error message to display.
 */
void handleNullMatrix(const char* message) {
  fprintf(stderr, "Matrix Failure: %s on NULL reference\n", message);
  exit(EXIT_FAILURE);
}

/**
 * @brief Handles errors related to empty matrix references.
 * @param message The error message to display.
 */
void handleEmptyMatrix(const char* message) {
  fprintf(stderr, "Matrix Failure: %s on empty Matrix\n", message);
  exit(EXIT_FAILURE);
}

/**
 * @brief Handles errors related to out of bounds matrix references.
 * @param message The error message to display.
 */
void handleBoundsMatrix(const char* message) {
  fprintf(stderr, "Matrix Failure: %s... out of bounds\n", message);
  exit(EXIT_FAILURE);
}

//#############################################//
//############# STRUCTS AND OBJS ##############//
//#############################################//

typedef struct MatrixObj {
  int n;         // n of the square matrix
  int nnz;       // number of non zeros
  List* matrix;  // main matrix structure
} MatrixObj;

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj {
  int key;       // key
  double value;  // value @ key
} EntryObj;

//#############################################//
//######## CONSTRUCTORS & DESTRUCTORS #########//
//#############################################//

/**
 * @implements newEntry()
 * @brief Creates a new Entry object.
 * @param key The index.
 * @param value The value.
 * @return A reference to a new Entry object.
 */
Entry newEntry(int key, double value) {
  Entry e = (Entry)malloc(sizeof(EntryObj));
  if (!e) handleNullMatrix("calling newEntry()");
  e->key = key;
  e->value = value;
  return e;
}

/**
 * @implements freeEntry()
 * @brief Frees all heap memory associated with the entry and sets it to NULL.
 * @param pM Pointer to the Matrix to be freed.
 */
void freeEntry(Entry* eP) {
  if (eP && *eP) {
    free((Entry)*eP);
    *eP = NULL;
  }
}

/**
 * @implements newMatrix()
 * @brief Creates a new nxn matrix.
 * @param n The dimensions for the sqare matrix.
 * @return A reference to a new nxn Matrix object in the zero state.
 */
Matrix newMatrix(int n) {
  Matrix M = (Matrix)malloc(sizeof(MatrixObj));
  if (!M) handleNullMatrix("calling newMatrix()");
  M->n = n;
  M->nnz = 0;
  M->matrix = (List*)malloc(sizeof(List) * n);
  if (!(M->matrix)) {
    handleNullMatrix("calling newMatrix()");
  }
  for (int i = 0; i < n; i++) {
    M->matrix[i] = newList();
  }
  return M;
}

/**
 * @implements freeMatrix()
 * @brief Frees all heap memory associated with the matrix and sets it to NULL.
 * @param pM Pointer to the Matrix to be freed.
 */
void freeMatrix(Matrix* pM) {
  if (!pM || !*pM) return;
  for (int i = 0; i < (*pM)->n; i++) {
    if ((*pM)->matrix[i]) {
      while(!isEmpty((*pM)->matrix[i])) {
        Entry e = front((*pM)->matrix[i]);
        freeEntry(&e);
        deleteFront((*pM)->matrix[i]);
      }
      freeList(&(*pM)->matrix[i]);
      (*pM)->matrix[i] = NULL;
    }
  }
  if ((*pM)->matrix) {
    free((*pM)->matrix);
    (*pM)->matrix = NULL;
  }
  free(*pM);
  *pM = NULL;
}

//#############################################//
//############# Private Helpers ###############//
//#############################################//

double vectorDot(List P, List Q) {
  double sum = 0;
  // Move to the front of both lists
  moveFront(P);
  moveFront(Q);
  // Iterate through both lists
  while (index(P) != -1 && index(Q) != -1) {
    Entry e1 = get(P);
    Entry e2 = get(Q);
    if (e1->key == e2->key) {
      // If keys match, multiply and add to sum
      sum += e1->value * e2->value;
      moveNext(P);
      moveNext(Q);
    } else if (e1->key < e2->key) {
      // Move P forward
      moveNext(P);
    } else {
      // Move Q forward
      moveNext(Q);
    }
  }
  return sum;
}


//#############################################//
//############# ACCESS FUNCTIONS ##############//
//#############################################//

/**
 * @implements size()
 * @brief Public getter for the size of the matrix.
 * @param M The Matrix ADT.
 */
int size(Matrix M) {
  if (!M) handleNullMatrix("calling size()");
  return M->n;
}

/**
 * @implements NNZ()
 * @brief Public getter for the number of non-zero entries.
 * @param M The Matrix ADT.
 */
int NNZ(Matrix M) {
  if (!M) handleNullMatrix("calling NNZ()");
  return M->nnz;
}

/**
 * @implements equals()
 * @brief Compares two matrices for equality.
 * @param A The first Matrix ADT.
 * @param B The second Matrix ADT.
 * @return (1) if true and (0) if false
 */
int equals(Matrix A, Matrix B) {
  if (!A || !B) handleNullMatrix("calling equals()");
  if (A->n != B->n || A->nnz != B->nnz) return 0;

  for (int i = 0; i < A->n; i++) {
    moveFront(A->matrix[i]);
    moveFront(B->matrix[i]);

    // Compare entries in the current row of both matrices
    while (index(A->matrix[i]) != -1 || index(B->matrix[i]) != -1) {
      Entry eA = (index(A->matrix[i]) != -1) ? get(A->matrix[i]) : NULL;
      Entry eB = (index(B->matrix[i]) != -1) ? get(B->matrix[i]) : NULL;

      // If one matrix has an entry and the other does not
      if ((eA && !eB) || (!eA && eB)) return 0;

      // If both have entries, compare them
      if (eA && eB) {
        if (eA->key != eB->key || eA->value != eB->value) return 0;
        moveNext(A->matrix[i]);
        moveNext(B->matrix[i]);
      }
    }
  }

  return 1;  // Matrices are equal
}

//#############################################//
//########## MANIPULATION PROCEDURES ##########//
//#############################################//

/**
 * @implements makeZero()
 * @brief Re-sets M to the zero Matrix state.
 * @param M The Matrix ADT.
 */
void makeZero(Matrix M) {
  if (!M) handleNullMatrix("calling makeZero()");
  if (M->n == 0) handleEmptyMatrix("calling makeZero()");
  for (int i = 0; i < M->n; i++) {
    while(!isEmpty(M->matrix[i])) {
      Entry e = front(M->matrix[i]);
      freeEntry(&e);
      deleteFront(M->matrix[i]);
    }
  }
  M->nnz = 0;
}

/**
 * @implements changeEntry()
 * @complexity: O(a)
 * @brief Changes the ith row, jth column of M to the value x.
 * @pre 1<=i<=size(M), 1<=j<=size(M)
 * @param M The Matrix ADT.
 * @param i row.
 * @param j column.
 * @param x value to set.
 */
void changeEntry(Matrix M, int i, int j, double x) {
  if (!M) handleNullMatrix("calling changeEntry()");
  if (M->n < i || i < 1 || M->n < j || j < 1) {
    handleBoundsMatrix("calling changeEntry()");
  }
  i--;
  moveFront(M->matrix[i]);
  while (index(M->matrix[i]) >= 0) {
    Entry old = get(M->matrix[i]);
    if (old->key == j) {
      if (x == 0) {
        freeEntry(&old);
        delete(M->matrix[i]);
        M->nnz--;
        return;
      }
      old->value = x;
      return;
    } 
    if (old->key > j) break;
    moveNext(M->matrix[i]);
  }
  if (x == 0) return;
  Entry e = newEntry(j, x);
  (index(M->matrix[i]) == -1) ? append(M->matrix[i], e) : insertBefore(M->matrix[i], e);
  M->nnz++;
}


//#############################################//
//########### ARITHMETIC PROCEDURES ###########//
//#############################################//

/**
 * @implements copy()
 * @complexity: O(n + a)
 * @brief Copy a given matrix into a new matrix.
 * @param A The Matrix ADT.
 * @return a reference to a new Matrix object having the same entries as A.
 */
Matrix copy(Matrix A) {
  if (!A) handleNullMatrix("calling copy()");
  Matrix M = newMatrix(A->n);
  for (int i = 0; i < A->n; i++) {
    moveFront(A->matrix[i]);
    while (index(A->matrix[i]) != -1) {
      Entry e = get(A->matrix[i]);
      Entry new = newEntry(e->key, e->value);
      append(M->matrix[i], new);
      M->nnz++;
      moveNext(A->matrix[i]);
    }
  }
  return M;
}

/**
 * @implements transpose()
 * @complexity: O(n + a)
 * @brief Swaps i (rows) with j (col) -- Aij -> Tji
 * @param A The Matrix ADT.
 * @return a reference to a new Matrix object representing the transpose of A.
 */
Matrix transpose(Matrix A) {
  if (!A) handleNullMatrix("calling transpose()");
  Matrix M = newMatrix(A->n);
  for (int i = 0; i < A->n; i++) {
    moveFront(A->matrix[i]);
    while (index(A->matrix[i]) != -1) {
      Entry e = get(A->matrix[i]);
      changeEntry(M, e->key, i+1, e->value);
      moveNext(A->matrix[i]);
    }
  }
  M->nnz = A->nnz;
  return M;
}

/**
 * @implements scalarMult()
 * @complexity: O(n + a)
 * @brief Scalar multiplication on matrix A
 * @param A The Matrix ADT.
 * @param x The scalar multiple.
 * @return a reference to a new Matrix object representing xA.
 */
Matrix scalarMult(double x, Matrix A) {
  if (!A) handleNullMatrix("calling scalarMult()");
  Matrix M = newMatrix(A->n);
  if (x == 0) return M;
  for (int i = 0; i < A->n; i++) {
    moveFront(A->matrix[i]);
    while (index(A->matrix[i]) != -1) {
      Entry e = get(A->matrix[i]);
      double prod = e->value * x;
      append(M->matrix[i], newEntry(e->key, prod));
      M->nnz++;
      moveNext(A->matrix[i]);
    }
  }
  return M;
}

/**
 * @implements sum()
 * @complexity: O(n + a + b)
 * @brief Matrix addition with A and B
 * @pre size(A) == size(B)
 * @param A The first Matrix ADT.
 * @param B The second Matrix ADT.
 * @return a reference to a new Matrix object representing A+B.
 */
Matrix sum(Matrix A, Matrix B) {
  if (!A || !B) handleNullMatrix("calling sum()");
  if (A->n != B->n) handleBoundsMatrix("calling sum()");
  if (equals(A, B) == 1) {
    return scalarMult(2, A);
  }
  Matrix M = newMatrix(A->n);

  for (int i = 0; i < A->n; i++) {
    moveFront(A->matrix[i]);
    moveFront(B->matrix[i]);

    while (index(A->matrix[i]) != -1 || index(B->matrix[i]) != -1) {
      Entry eA = (index(A->matrix[i]) != -1) ? get(A->matrix[i]) : NULL;
      Entry eB = (index(B->matrix[i]) != -1) ? get(B->matrix[i]) : NULL;
      Entry e = NULL;

      if (eA && (!eB || eA->key < eB->key)) { 
        // A has an entry that B does not
        e = newEntry(eA->key, eA->value);
        moveNext(A->matrix[i]);
      } else if (eB && (!eA || eB->key < eA->key)) { 
        // B has an entry that A does not
        e = newEntry(eB->key, eB->value);
        moveNext(B->matrix[i]);
      } else if (eA && eB) { 
        // Both A and B have the same key
        double sumValue = eA->value + eB->value;
        if (sumValue != 0) {  
          e = newEntry(eA->key, sumValue);
        }
        moveNext(A->matrix[i]);
        moveNext(B->matrix[i]);
      }
      if (e && e->value != 0) {
        append(M->matrix[i], e);
        M->nnz++;
      } else {
        freeEntry(&e);
      }
    }
  }
  return M;
}


/**
 * @implements diff()
 * @complexity: O(n + a + b)
 * @brief Matrix subtraction with A and B
 * @pre size(A) == size(B)
 * @param A The first Matrix ADT.
 * @param B The second Matrix ADT.
 * @return a reference to a new Matrix object representing A-B.
 */
Matrix diff(Matrix A, Matrix B) {
  if (!A || !B) handleNullMatrix("calling diff()");
  if (A->n != B->n) handleBoundsMatrix("calling diff()");
  
  Matrix M = newMatrix(A->n);
  if (equals(A,B) == 1) return M;

  if (!M) handleNullMatrix("calling diff()");
  for (int i = 0; i < A->n; i++) {
    moveFront(A->matrix[i]);
    moveFront(B->matrix[i]);

    while (index(A->matrix[i]) != -1 || index(B->matrix[i]) != -1) {
      Entry eA = (index(A->matrix[i]) != -1) ? get(A->matrix[i]) : NULL;
      Entry eB = (index(B->matrix[i]) != -1) ? get(B->matrix[i]) : NULL;
      Entry e = NULL;

      if (eA && (!eB || eA->key < eB->key)) { 
        // A has an entry that B does not
        e = newEntry(eA->key, eA->value);
        moveNext(A->matrix[i]);
      } else if (eB && (!eA || eB->key < eA->key)) { 
        // B has an entry that A does not
        e = newEntry(eB->key, -eB->value);
        moveNext(B->matrix[i]);
      } else if (eA && eB) { 
        // Both A and B have the same key
        double sumValue = eA->value - eB->value;
        if (sumValue != 0) {  
          e = newEntry(eA->key, sumValue);
        }
        moveNext(A->matrix[i]);
        moveNext(B->matrix[i]);
      }
      if (e && e->value != 0) {
        append(M->matrix[i], e);
        M->nnz++;
      } else {
        freeEntry(&e);
      }
    }
  }
  return M;
}

/**
 * @implements product()
 * @complexity: O(n^2 + a + b)
 * @brief Matrix addition with A and B
 * @pre size(A) == size(B)
 * @param A The first Matrix ADT.
 * @param B The second Matrix ADT.
 * @return a reference to a new Matrix object representing AB.
 */
Matrix product(Matrix A, Matrix B) {
  if (!A || !B) handleNullMatrix("calling product()");
  if (A->n != B->n) handleBoundsMatrix("calling product()");
  Matrix C = transpose(B);
  Matrix M = newMatrix(A->n);
  for (int i = 0; i < M->n; i++) {
    if (!isEmpty(A->matrix[i])) {
      for (int j = 0; j < M->n; j++) {
        if (!isEmpty(C->matrix[j])) {
          double dp = vectorDot(A->matrix[i], C->matrix[j]);
          if (dp != 0) {
            append(M->matrix[i], newEntry(j + 1, dp));
            M->nnz++;
          }
        }
      }
    }
  }
  freeMatrix(&C);
  M->n = A->n;
  return M;
}

//#############################################//
//############## MISC PROCEDURES ##############//
//#############################################//

/**
 * @implements printMatrix()
 * @brief Prints a string representation of Matrix M to filestream out.
 *        Zero rows are not printed. Each non-zero row is represented as
 *        one line consisting of the row number, followed by a colon, a space,
 *        then a space separated list of pairs "(col, val)" giving the
 *        column numbers and non-zero values in that row.
 *        The double val will be rounded to 1 decimal point.
 * @param out The output file.
 * @param M The Matrix ADT.
 */
void printMatrix(FILE* out, Matrix M) {
  for (int i = 0; i < M->n; i++) {
    if (!isEmpty(M->matrix[i])) {
      fprintf(out, "%d: ", i+1);
      moveFront(M->matrix[i]);
      while (index(M->matrix[i]) != -1) {
        Entry e = get(M->matrix[i]);
        fprintf(out, "(%d, %.1f) ", e->key, e->value);
        moveNext(M->matrix[i]);
      }
      fprintf(out, "\n");
    }
  }
}
