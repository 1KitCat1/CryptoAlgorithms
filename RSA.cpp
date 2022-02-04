#include <iostream>

struct key{
	uint64_t e;
	uint64_t m;
};

// a*x + b*y = gcd(a, b)
int64_t gcdex(int64_t a, int64_t b, int64_t &x, int64_t &y){
	if(a == 0){  //0*x+b*y=gcd(a,b)
		x = 0;
		y = 1;
		return b;
	}
	int64_t xn, yn;
	int64_t res = gcdex(b % a, a, xn, yn);
	x = yn - (b / a) * xn;
	y = xn;
	return res;	
}

int main(){


}