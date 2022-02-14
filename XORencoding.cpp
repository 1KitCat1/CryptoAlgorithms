#include <iostream>

const int LEFT_SHIFT = 2;
const int RIGHT_SHIFT = 3;
const std::string SALT = "someSalt";

std::string proceedKey(const std::string& key) {
	std::string newKey(key.size() * 2, key[0]);
	for(int repeat = 0; repeat < 19; ++repeat) {
		for(int index = 0; index < newKey.size(); index++){
			int left = key[(index - LEFT_SHIFT + key.size()) % key.size()];
			int right = key[(index + RIGHT_SHIFT) % key.size()];
			newKey[index] = 
			    (newKey[index] + left % 26 + (left ^ right) + right % 12) % 256;
			newKey[(index + RIGHT_SHIFT) % newKey.size()] += 
			    (left ^ right) + (left + right) % 15;
			newKey[(index + 2 * RIGHT_SHIFT) % newKey.size()] += 
			    (left ^ right) % 7 + (left + right) % 13;
		}
	}
	return newKey;
}

std::string encryptXOR(const std::string& data, const std::string& key) {
	if (key.size() < 3) {
		throw std::invalid_argument("Key is too short");
	}

	std::string oneRoundKey = proceedKey(key);
	std::string k = proceedKey(oneRoundKey + SALT);


	std::string encrypted(data.size(), ' ');
	for (int index = 0; index < data.size(); ++index) {
		encrypted[index] = data[index] ^ k[(index) % k.size()];
		encrypted[index] ^= k[(index - LEFT_SHIFT + k.size()) % k.size()];
		encrypted[index] ^= k[(index + RIGHT_SHIFT) % k.size()];
		if (index > 0) {
			encrypted[index] ^= encrypted[index - 1];
		}
	}
	return encrypted;
}

std::string decryptXOR(const std::string& data, const std::string& key) {
	if (key.size() < 3) {
		throw std::invalid_argument("Key is too short");
	}

	std::string oneRoundKey = proceedKey(key);
	std::string k = proceedKey(oneRoundKey + SALT);

	std::string decrypted(data.size(), ' ');
	for (int index = 0; index < data.size(); ++index) {
		decrypted[index] = data[index] ^ k[(index) % k.size()];
		decrypted[index] ^= k[(index - LEFT_SHIFT + k.size()) % k.size()];
		decrypted[index] ^= k[(index + RIGHT_SHIFT) % k.size()];
		if (index > 0) {
			decrypted[index] ^= data[index - 1];
		}
	}
	return decrypted;
}

int main() {
	std::string key = "example";
	std::string data;
	getline(std::cin, data);
	std::cout << "Enter key: \n";
	getline(std::cin, key);
	std::string encryptedData = encryptXOR(data, key); 
	std::cout << "ENCRYPTED: " << encryptedData << '\n';
	key = "example";
	std::cout << "Enter key to decrypt: \n";
	getline(std::cin, key);
	std::cout << "DECRYPTED: " << decryptXOR(encryptedData, key); 
}