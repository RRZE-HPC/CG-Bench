#ifndef __DEBUGGER_H_
#define __DEBUGGER_H_

#define DBG_INFO 1
#define DBG_VINFO 2
#define DBG_DEV 3

#define TEST_RANK 1

#ifdef DEBUG
#define DEBUG_PRINT(level, fmt, ...) \
    do { if (DEBUG_LEVEL >= level) printf(fmt, ##__VA_ARGS__); } while (0)
#else
#define DEBUG_PRINT(level, fmt, ...)
#endif

#ifdef DEBUG
#define CHECK_NEGATIVE(level, num) \
do { \
		if ((DEBUG_LEVEL >= level) && (num) < 0) { \
				printf("Error: unexpected negative (%i) at %s:%d\n", num, __FILE__, __LINE__); \
				exit(EXIT_FAILURE); \
		} \
} while (0)
#else
#define CHECK_NEGATIVE(level, num)
#endif

#ifdef DEBUG
#define CHECK_EXPECTED(level, arg, expected) \
do { \
		if ((DEBUG_LEVEL >= level) && arg != expected) { \
				printf("Error: expected (%i) to be (%i) at %s:%d\n", arg, expected, __FILE__, __LINE__); \
				exit(EXIT_FAILURE); \
		} \
} while (0)
#else
#define CHECK_EXPECTED(level, arg, expected)
#endif


#include <stdbool.h>

#include "solver.h"
#include "comm.h"
#include "matrix.h"

static void validateBeforeComm(Comm *c, CG_FLOAT* x, int nr, int neighborCount, int *recvCount){
  MPI_Barrier(MPI_COMM_WORLD);

  if (c->rank != 0) {
    int dummy;
    MPI_Recv(&dummy, 1, MPI_INT, c->rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

	int buffer_space = nr;
	for (int i = 0; i < neighborCount; i++) {
		buffer_space += recvCount[i];
	}

	printf("rank %i Before communication,\nx = [", c->rank);
	for(int i = 0; i < buffer_space; ++i) {
		printf("%f, ", x[i]);
	}
	printf("]\n");

  if (c->rank != c->size - 1) {
		int dummy = 0;
		MPI_Send(&dummy, 1, MPI_INT, c->rank + 1, 0, MPI_COMM_WORLD);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	printf("\n");
}

static void validateAfterComm(Comm *c, CG_FLOAT* x, int nr, int neighborCount, int *recvCount){
  MPI_Barrier(MPI_COMM_WORLD);

  if (c->rank != 0) {
    int dummy;
    MPI_Recv(&dummy, 1, MPI_INT, c->rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

	int buffer_space = nr;
	for (int i = 0; i < neighborCount; i++) {
		buffer_space += recvCount[i];
	}

	printf("rank %i After communication,\nx = [", c->rank);
	for(int i = 0; i < buffer_space; ++i) {
		printf("%f, ", x[i]);
	}
	printf("]\n");

  if (c->rank != c->size - 1) {
		int dummy = 0;
		MPI_Send(&dummy, 1, MPI_INT, c->rank + 1, 0, MPI_COMM_WORLD);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	printf("\n");
}

static void validateDdot(CG_FLOAT sum, int rank, int size){
  MPI_Barrier(MPI_COMM_WORLD);

  if (rank != 0) {
    int dummy;
    MPI_Recv(&dummy, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

	printf("rank %i sum after ddot, \nsum = %f\n", rank, sum);

  if (rank != size - 1) {
      int dummy = 0;
      MPI_Send(&dummy, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
  }

	MPI_Barrier(MPI_COMM_WORLD);
	printf("\n");
}

static void validateSpMVM(CG_FLOAT* y, int nr, int rank, int size){
  MPI_Barrier(MPI_COMM_WORLD);

  if (rank != 0) {
    int dummy;
    MPI_Recv(&dummy, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

	printf("rank %i y after spmv, \ny = [", rank);
	for(int i = 0; i < nr; ++i) {
		printf("%f, ", y[i]);
	}
	printf("]\n");

  if (rank != size - 1) {
      int dummy = 0;
      MPI_Send(&dummy, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
  }

	MPI_Barrier(MPI_COMM_WORLD);
	printf("\n");
}

static void validateWaxpby(CG_FLOAT* w, int nr, int rank, int size){
  MPI_Barrier(MPI_COMM_WORLD);

  if (rank != 0) {
    int dummy;
    MPI_Recv(&dummy, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

	printf("rank %i w after waxpby, \nw = [", rank);
	for(int i = 0; i < nr; ++i) {
		printf("%f, ", w[i]);
	}
	printf("]\n");

  if (rank != size - 1) {
      int dummy = 0;
      MPI_Send(&dummy, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
  }

	MPI_Barrier(MPI_COMM_WORLD);
	printf("\n");
}

static void validateSubMat(Comm* c, MmMatrix* mLocal){
  if (c->rank != 0) {
    int dummy;
    MPI_Recv(&dummy, 1, MPI_INT, c->rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  printf("On rank %i, after sending:\nrow:  col:  val:\n", c->rank);
  Entry* local_e = mLocal->entries;
  for(int j = 0; j < mLocal->nnz; ++j){
    printf("%i      %i        %f\n", local_e[j].row, local_e[j].col, local_e[j].val);
  }

  if (c->rank != c->size - 1) {
      int dummy = 0;
      MPI_Send(&dummy, 1, MPI_INT, c->rank + 1, 0, MPI_COMM_WORLD);
  }

	MPI_Barrier(MPI_COMM_WORLD);
	printf("\n");
}

// Fenced print
static void validateCRSMat(Matrix* m, Comm* c){
  MPI_Barrier(MPI_COMM_WORLD);

  if (c->rank != 0) {
    int dummy;
    MPI_Recv(&dummy, 1, MPI_INT, c->rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  printf("On rank %i\n", c->rank);
  printf("rowPtr = [");
  for(int row = 0; row < m->nr + 1; ++row){
    printf("%i, ", m->rowPtr[row]);
  }
  printf("]\n");
  printf("colInd = [");
  for(int row = 0; row < m->nr; ++row){
    for(int j = m->rowPtr[row]; j < m->rowPtr[row + 1]; ++j){
      printf("%i, ", m->colInd[j]);
    }
  }
  printf("]\n");
  printf("val = [");
  for(int row = 0; row < m->nr; ++row){
    for(int j = m->rowPtr[row]; j < m->rowPtr[row + 1]; ++j){
      printf("%f, ", m->val[j]);
    }
  }
  printf("]\n");

  if (c->rank != c->size - 1) {
      int dummy = 0;
      MPI_Send(&dummy, 1, MPI_INT, c->rank + 1, 0, MPI_COMM_WORLD);
  }

	MPI_Barrier(MPI_COMM_WORLD);
	printf("\n");
}

static bool validateSymmetry(MmMatrix* m){
	printf("Validating symmetry:\n");

  Entry *e = m->entries;

  for (int i = 0; i < m->nnz; i++) {
    int r1 = e[i].row;
    int c1 = e[i].col;
    double v1 = e[i].val;

    if (r1 != c1) { // Ignore diagonal elements
      bool found = false;
      for (int j = 0; j < m->nnz; j++) {
        if (e[j].row == c1 && e[j].col == r1) {
          if (e[j].val != v1) {
            // If pattern matches, but numerical does not
						printf("Cannot validate symmetry\n");
            return false;
          }
          found = true;
          break;
        }
      }
      if (!found) { // If a single pattern doesn't match
				printf("Cannot validate symmetry\n");
        return false;
      }
    }
  }

	printf("Symmetry validated\n");
  return true;
}

#endif
