int fib(int);
char* itoa(int, char*);
void print(char*, int);
void *memset(void*, int, int);
void swap(char*, char*);
char *reverse(char*, int, int);

int fib(int n){
	if (n >= 1) return n*fib(n-1);
	return 1;
}

void swap(char *x, char *y){
	char tmp = *x;
	*x = *y;
	*y = tmp;
}

char* reverse(char *b, int i, int j){
	while (i<j) swap(&b[i++], &b[j--]);
	return b;
}

int abs(int n){
	int mask = n >> sizeof(int) * 7;
	return (n + mask) ^ mask;
}

char* itoa(int v, char* b){
	int i, n;

	n = abs(v);
	i = 0;
	while(n){
		int r;
		r = n % 10;

		if (r >= 10) 
			b[i++] = 65 + (r - 10);
		else
			b[i++] = 48 + r;

		n /= 10;
	}
	if (i == 0)
		b[i++] = '0';

	if (v < 0)
		b[i++] = '-';
	b[i] = 0;
	return reverse(b, 0, i - 1);
}

void* memset(void *src, int v, int n){
	int tmp = n;
	while(n--)
		*((unsigned char*)src++) = v;
	return src-tmp;
}

void print(char *s, int color){
	volatile char *v = (volatile char*)0xB8000;
	while(*s){
		*v++ = *s++;
		*v++ = color;
	}
}

char stack[4096];

void main(void){
	char b[13];
	print(itoa(123123, b), 5);
	for(;;);
}

