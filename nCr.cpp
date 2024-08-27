int M = 1e9+7;
int fact[200001]; // populate it in main function.

int modinverse(int a, int M=M) {
	int m = M, y = 0, x = 1;
	while(a>1){int q=a/m; int t=m; m=a%m; a=t; t=y; y=x-q*y; x=t;} 
    if (x < 0) x += M;
	return x;
}

int ncr(int n, int r) {
    int num = fact[n];
    int deno = (fact[r]*fact[n-r]) % M;
    int result = (num * modinverse(deno, M)) % M;
    return result;
}