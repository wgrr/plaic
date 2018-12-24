#include <u.h>
#include <uart.h>
#include <cpu.h>

static void print(char *s, int color){
	volatile char *v = (volatile char*)0xB8000;
	while(*s){
		*v++ = *s++;
		*v++ = color;
	}
}

void main(void){
	cpu·init();
	uart·println("hello world");
	for(;;);
}

