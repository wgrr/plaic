void* memset(void *src, int v, long n){
	int tmp = n;
	while(n--)
		*((uchar*)src++) = v;
	return src-tmp;
}
