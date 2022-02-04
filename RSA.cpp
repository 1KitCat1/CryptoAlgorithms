#include <iostream>
#include <vector>

struct key{
	uint64_t e;
	uint64_t m;
};

const uint64_t def_prime1 = 3779;
const uint64_t def_prime2 = 2833;

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

uint8_t get_chunk_size(key k){
	return 32 - __builtin_clz(k.m); // Count Leading Zeros
}

std::vector<uint64_t> resize(const std::vector<uint64_t>& data, uint8_t in_size, uint8_t out_size){
	std::vector<uint64_t> res;
	uint8_t done = 0;
	uint8_t current = 0;
	for(uint64_t byte : data){
		for(uint8_t i = 0; i < in_size; ++i){
			current <<= 1u;
			current += (((uint64_t) byte & (1U << (uint64_t) (in_size - 1 - i))) != 0);
			done++;
			if(done == out_size){
				done = 0;
				res.push_back(current);
				current = 0;
			}
		}
	}
	if(done != 0){
		current <<= (uint64_t) (out_size - done);
		res.push_back(current);
	}
	return res;
}

std::vector<uint8_t> process_RSA(const std::vector<uint8_t>& data, key k, bool encrypt){
	std::vector<uint64_t> data_64t(data.size());
	for(int i = 0; i < data.size(); ++i){
		data_64t[i] = (uint64_t) data[i];
	}
	std::vector<uint64_t> resized_data = resize(data_64t, 8, get_chunk_size(k) - encrypt);
	std::vector<uint64_t> encrypted(resized_data.size());
	for(int i = 0; i < resized_data.size(); ++i){
		encrypted[i] = binpow(resized_data[i], k.e, k.m);
	}
	std::vector<uint64_t> result_64t = resize(encrypted, get_chunk_size(k) - !encrypt, 8);
	std::vector<uint8_t> result_8t(result_64t.size());
    for (int i = 0; i < result_64t.size(); i++)
        result_8t[i] = (uint8_t) result_64t[i];
    return result_8t;
}


int main(){
	auto key_pair = generate_keys(def_prime1, def_prime2);
	std::cout << std::hex;
    std::cout << "open key: " << key_pair.first.e << key_pair.first.m << std::endl;
	std::cout << "secret key:" << key_pair.second.e << key_pair.second.m << std::endl;

}