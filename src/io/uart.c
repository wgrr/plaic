#include <u.h>
#include <serport.h>

static int comm = 0x3f8;
static int regdat = 0;

void uart·init(void){
	int clockrate, baudrate, divisor;
	int stop, parity, regdivl;
	int reglcr = 3;
	int lcrdlab = 0x80;
	int regdivh = 1;

	stop = parity = regdivl = 0;
	baudrate = clockrate = 115200;
	divisor = clockrate/baudrate;

	serport·write(comm+reglcr, lcrdlab);
	serport·write(comm+regdivl, divisor);
	serport·write(comm+regdivh, divisor >> 8);
	serport·write(comm+reglcr, reglcr|stop|parity);
	
}

static void uart·write(uchar b){
	serport·write(comm+regdat, b);
}

int uart·println(char *str){
	int n;
	while(*str){
		uart·write(*str++);
		n++;
	}
	uart·write('\n');
	return ++n;
}
