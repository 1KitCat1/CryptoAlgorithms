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
// a * a**(-1) = 1
int64_t inversed_mod(int64_t a, int64_t mod){
	int64_t x, y;
	gcdex(a, mod, x, y);
	x = (x % mod + mod) % mod;
	return x;
}

uint64_t binpow(uint64_t a, uint64_t exp, uint64_t mod){
	uint64_t res = 1;
	while(exp){
		if(exp & 1){
			res *= a;
			res %= mod;
		}
		a *= (a % mod);
		a %= mod;
		exp >>= 1;
	}
	return res % mod;
}

std::pair<key, key> generate_keys(uint64_t p, uint64_t q){
	uint64_t temp = (p-1) * (q-1);
	uint64_t n = p * q;
	uint64_t mersen = 65537;
	uint64_t d = inversed_mod(mersen, temp);
	return {{mersen, n}, {d, n}};
}

int main(){


}