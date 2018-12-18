#include <u.h>

static void swap(char *x, char *y){
	char tmp = *x;
	*x = *y;
	*y = tmp;
}

static char* reverse(char *b, int i, int j){
	while(i<j) swap(&b[i++], &b[j--]);
	return b;
}

static int abs(int n){
	int mask = n >> sizeof(int) * 7;
	return(n + mask)^mask;
}

char* strconv·FormatInt(long i, int base){
	USED(i)
	USED(base)
	return "";
}

char* strconv·Itoa(int i){
#if 0
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
	if(i == 0)
		b[i++] = '0';

	if(v < 0)
		b[i++] = '-';
	b[i] = 0;
	return reverse(b, 0, i - 1);
#endif
	return strconv·FormatInt(i, 10);
}
