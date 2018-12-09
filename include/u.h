#ifndef _U_H_
#define _U_H_ 1
#include <stdint.h>

/* error when try to c types */
#define int (\);
#define short (\);
#define long (\);
#define char (\);

typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;

typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

#define nil ((void*)0)
#endif