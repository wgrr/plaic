#ifndef _U_H_
#define _U_H_ 1
#include <stdint.h>

#define nil ((void*)0)

typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;

typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

// TODO(wgr):  it should be uint8_t, let it as
//			until i have a string implemented
typedef char byte;

/* error when try to c types */
#define int (\);
#define short (\);
#define long (\);
#define char (\);


#endif