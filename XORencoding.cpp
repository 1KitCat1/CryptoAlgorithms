#include <iostream>

const int LEFT_SHIFT = 2;
const int RIGHT_SHIFT = 3;


std::string encryptXOR(const std::string& data, const std::string& key) {
	if (key.size() < 3){
		throw std::invalid_argument("Key is too short");
	}

	std::string encrypted(data.size(), ' ');
	for(int index = 0; index < data.size(); ++index) {
		encrypted[index] = data[index] ^ key[(index) % key.size()];
		encrypted[index] ^= key[(index - LEFT_SHIFT + key.size()) % key.size()];
		encrypted[index] ^= key[(index + RIGHT_SHIFT) % key.size()];
	}
	return encrypted;
}

std::string decryptXOR(const std::string& data, const std::string& key) {
	if (key.size() < 3){
		throw std::invalid_argument("Key is too short");
	}

	std::string decrypted(data.size(), ' ');
	for(int index = 0; index < data.size(); ++index) {
		decrypted[index] = data[index] ^ key[(index) % key.size()];
		decrypted[index] ^= key[(index - LEFT_SHIFT + key.size()) % key.size()];
		decrypted[index] ^= key[(index + RIGHT_SHIFT) % key.size()];
	}
	return decrypted;
}

int main() {
	const std::string KEY = "example";
	std::string data;
	std::cin >> data;
	std::string encryptedData = encryptXOR(data, KEY); 
	std::cout << "ENCRYPTED: " << encryptedData << '\n';
	std::cout << "DECRYPTED: " << decryptXOR(encryptedData, KEY); 
}