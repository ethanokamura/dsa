/**
 * @author Ethan Okamura
 * @file Matrix.h
 * @brief Header file for Matrix ADT
 * @status: in progress
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>

#include "List.h"

typedef struct MatrixObj* Matrix;

/*** Constructors-Destructors ***/
Matrix newMatrix(int n);
void freeMatrix(Matrix* pM);
/*** Access Functions ***/
int size(Matrix M);
int NNZ(Matrix M);
int equals(Matrix A, Matrix B);
/*** Manipulation Procedures ***/
void makeZero(Matrix M);
void changeEntry(Matrix M, int i, int j, double x);
/*** Arithmetic Procedures ***/
Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);
/*** Extra Procedures ***/
void printMatrix(FILE* out, Matrix M);

#endif
