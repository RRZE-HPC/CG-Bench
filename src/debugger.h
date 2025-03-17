#ifndef __DEBUGGER_H_
#define __DEBUGGER_H_

#define DBG_INFO 1
#define DBG_DEV 2

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



#endif
