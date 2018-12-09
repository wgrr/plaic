#include <u.h>
#include <defs.h>

#define CGA_ADDR 0xb8000

/* TODO(wgr): get rid of these gcc extensions */
/* GO AWAY, DO NOT MESS WITH SPACE ABOVE!!!! */
uint8 stack[4096] __attribute__ ((aligned (4)));

extern void print(void);
void main(void) {
	print();
	for(;;);
}