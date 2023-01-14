// Diffie Hellman algorithm for generating shared secret through open channel
#include <iostream>

using namespace std;

struct PublicSpace {
public:
	uint64_t MOD = 1000000007; // big prime
	uint64_t BASE = 7787917; // base point
	uint32_t binPow(uint64_t exp, uint64_t base){ // (base ** exp) % MOD
		uint64_t result = 1;
		while(exp) {
			if(exp & 1) {
				result *= base;
				result %= MOD;
			}
			base *= base;
			base %= MOD;
			exp >>= 1;
		}
		return result;
	}

};


struct Alice {
private:
	uint32_t secret = 3999282767;
	uint32_t sharedSecret; // secret that only Alice and Bob can generate
public:
	uint32_t publicKey; // key can be exchanged with Bob via open channel

	void generatePublicKey(PublicSpace& publicSpace) {
		publicKey = publicSpace.binPow(secret, publicSpace.BASE);
	}
	void generateSharedSecret(PublicSpace& publicSpace, uint32_t publicKeyBob) {
		sharedSecret = publicSpace.binPow(secret, publicKeyBob);
	}
	uint32_t getSharedSecret(){
		return sharedSecret;
	}
};

struct Bob {
private:
	uint32_t secret = 2036456287;
	uint32_t sharedSecret; // secret that only Alice and Bob can generate
public:
	uint32_t publicKey; // key can be exchanged with Alice via open channel
	void generatePublicKey(PublicSpace& publicSpace) {
		publicKey = publicSpace.binPow(secret, publicSpace.BASE);
	}
	void generateSharedSecret(PublicSpace& publicSpace, uint32_t publicKeyAlice) {
		sharedSecret = publicSpace.binPow(secret, publicKeyAlice);
	}
	uint32_t getSharedSecret(){
		return sharedSecret;
	}
};



int main(){
	PublicSpace publicSpace;
	Alice alice;
	Bob bob;

	// secrets cannot be exctracted in polinomial time from public keys
	alice.generatePublicKey(publicSpace);
	bob.generatePublicKey(publicSpace);

	cout << alice.publicKey << ' ' << bob.publicKey << endl;

	alice.generateSharedSecret(publicSpace, bob.publicKey);
	bob.generateSharedSecret(publicSpace, alice.publicKey);
	// Alice has key: BobPublicKey ** AliceSecret = (BASE ** BobSecret) ** AliceSecret
	// Bob has key:   AlicePublicKey ** BobSecret = (BASE ** AliceSecret) ** BobSecret
	// Alice`s shared secret == Bob shared secret

	cout << alice.getSharedSecret() << ' ' << bob.getSharedSecret() << endl; // equal
}