char stack[4096];
typedef short uint16;

int test(int);
char* itoa(int, char*, int);

void print(char *s){
	volatile uint16 *v;
	v = (volatile uint16*)0xb8000;
	while(*s){
		*v = (0x7 << 8) | *s;
		v++;
		s++;
	}
}

int test(int n){
	if (n >= 1)
		return n*test(n-1);
	else
		return 1;
}

void swap(char *x, char *y){
	char t = *x; *x = *y; *y = t;
}

char* reverse(char *b, int i, int j){
	while (i < j)
		swap(&b[i++], &b[j--]);
	return b;
}

int abs(int n){
	int r;
	int mask = n >> sizeof(int) * 8 - 1;
	r = (n + mask) ^ mask;
	return r;
}

char* itoa(int v, char* b, int base){
	int i, n;

	if (base < 2 || base > 32)
		return b;

	n = abs(v);
	i = 0;
	while (n){
		int r;
		r = n % base;

		if (r >= 10) 
			b[i++] = 65 + (r - 10);
		else
			b[i++] = 48 + r;

		n = n / base;
	}
	if (i == 0)
		b[i++] = '0';

	if (v < 0 && base == 10)
		b[i++] = '-';
	b[i] = '\0';
	return reverse(b, 0, i - 1);
}

void main(void){
	char b[20];
	print(itoa(test(12), &b[0], 10));
	for(;;);
}

