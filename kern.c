#include <u.h>
#include <defs.h>

/* TODO(wgr): get rid of these gcc extensions */
/* GO AWAY, DO NOT MESS WITH SPACE ABOVE!!!! */
uint8 stack[_STACKSIZE] __attribute__ ((aligned (4)));

/* not safe, str size may overlap available memory */
void print(byte *s) {
	volatile uint16 *v;
	v = (volatile uint16*)0xb8000;
	while(*s){
		*v = (0x7 << 8) | *s;
		v++;
		s++;
	}
}

void main(void) {
	for(;;);
}
