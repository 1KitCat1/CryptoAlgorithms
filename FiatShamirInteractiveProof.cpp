// Fiat-Shamir interactive proof of knowlage
// allows to prove knowlage about some number without revealing it

#include <iostream>

using namespace std;

// Task: Alice knows the solution X for Y = G ** X. She want to prove that 
// she know this X without revealing it

struct PublicSpace {
public:
	uint64_t MOD = 1000000007; // big prime
	uint64_t G = 5; // base (generator) point
	uint64_t Y = 25; // Y = G ** X, task is to find X
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
	uint32_t getRandom() {
		return binPow(rand() + rand(), rand() + rand()) + rand();
	}

} publicSpace;



struct Alice {
private:
	// Alice needs to prove that she knows this number without revealing it
	uint64_t secretX = 2;
	uint64_t randomV; 
public:
	uint64_t publicT; // publicT = G ** randomV
	void generateT() {
		randomV = 7;//publicSpace.getRandom();
		publicT = publicSpace.binPow(randomV, publicSpace.G);
	}
	uint64_t getAnswer(uint64_t randomC) { // answer = V - C*X  (mod MOD)
		return ((randomV - randomC * secretX) + publicSpace.MOD) % publicSpace.MOD;
	}

} alice;

struct Bob {
private:

public:
	uint64_t randomC;
	void generateC() {
		randomC = 2;//publicSpace.getRandom();
	}
	bool checkAnswer(uint64_t answer, uint64_t publicT) {
		return publicT == (publicSpace.binPow(answer, publicSpace.G) * 
			publicSpace.binPow(randomC, publicSpace.Y)) % publicSpace.MOD;
	}
} bob;



int main(){
	srand(474783993); // seed for random generator

	// Alice generates some random (secret) value V and public T = G ** V; 
	alice.generateT();
	cout << alice.publicT << endl;
	// Bob generate random value C
	bob.generateC();
	cout << bob.randomC << endl;
	// Alice returns answer R = V - C * X
	uint64_t answer = alice.getAnswer(bob.randomC);
	cout << answer << endl;
	cout << ((publicSpace.binPow(answer, publicSpace.G) * 
			publicSpace.binPow(bob.randomC, publicSpace.Y)) % publicSpace.MOD) << endl;

	bool checkAnswer = bob.checkAnswer(answer, alice.publicT);
	cout << checkAnswer << endl;
	// Math: 
	// check T == G**R * Y**C
	// R = V - C * X  |  Y = G**X  |  T = G**V
	// G**V == G**(V - C * X) * G**(C * X)
	// G**V == G**(V - C * X + C * X)
	// G**V == G**V
}