#include <u.h>
#include <defs.h>

/* TODO(wgr): get rid of these gcc extensions */
uint8 stack[_STACKSIZE] __attribute__ ((aligned (4)));

void main(void) {
	for(;;){}
}