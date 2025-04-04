/* Copyright (C) NHR@FAU, University Erlangen-Nuremberg.
 * All rights reserved. This file is part of CG-Bench.
 * Use of this source code is governed by a MIT style
 * license that can be found in the LICENSE file. */
#ifndef __UTIL_H_
#define __UTIL_H_

#define HLINE                                                                  \
  "----------------------------------------------------------------------\n"

#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

#ifndef ABS
#define ABS(a) ((a) >= 0 ? (a) : -(a))
#endif

#define DEBUG_MESSAGE debug_printf

#ifndef MAXLINE
#define MAXLINE 4096
#endif

// #define CG_UINT unsigned long long int
#define CG_UINT int

#if PRECISION == 1
#define CG_FLOAT         float
#define MPI_FLOAT_TYPE   MPI_FLOAT
#define PRECISION_STRING "single"
#else
#define CG_FLOAT         double
#define MPI_FLOAT_TYPE   MPI_DOUBLE
#define PRECISION_STRING "double"
#endif

#endif
