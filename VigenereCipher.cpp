#include <iostream>

std::string vigenereCipherEncode(std::string text, std::string key){
	int keyLength = key.size();
	std::string encodedText(text.size(), ' ');
	for(int index = 0; index < text.size(); ++index){
		if(text[index] - 'a' <= 0 || text[index] - 'a' >= 26){
			encodedText[index] = text[index];
			continue;
		}
		encodedText[index] = 'a' + ((text[index] - 'a') + (key[index % keyLength] - 'a')) % 26;
		// std::cout << index << ' ' << encodedText[index] << '\n';
	}
	return encodedText;
} 

int main(){
	std::string str;
	getline(std::cin, str);
	std::cout << vigenereCipherEncode(str, "abc");

}