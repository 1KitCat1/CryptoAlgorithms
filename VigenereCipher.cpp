#include <iostream>

std::string vigenereCipherEncode(const std::string& text, const std::string& key){
	const int keyLength = key.size();
	std::string encodedText(text.size(), ' ');
	for(int index = 0; index < text.size(); ++index){
		if(text[index] - 'a' < 0 || text[index] - 'a' >= 26){
			encodedText[index] = text[index];
			continue;
		}
		encodedText[index] = 'a' + ((text[index] - 'a') + (key[index % keyLength] - 'a')) % 26;
	}
	return encodedText;
}

std::string vigenereCipherDecode(const std::string& encodedText, const std::string& key){
	const int keyLength = key.size();
	std::string decodedText(encodedText.size(), ' ');
	for(int index = 0; index < encodedText.size(); ++index){
		if(encodedText[index] - 'a' < 0 || encodedText[index] - 'a' >= 26){
			decodedText[index] = encodedText[index];
			continue;
		}
		decodedText[index] = 'a' + (26 + (encodedText[index] - key[index % keyLength])) % 26;
	} 
	return decodedText;
}

int main(){
	std::string str;
	getline(std::cin, str);
	const std::string key = "abc";
	std::string encodedText = vigenereCipherEncode(str, key);
	std::cout << vigenereCipherDecode(encodedText, key);

}