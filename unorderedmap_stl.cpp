#include <iostream>
#include <string>
#include <unordered_map>

int main() {

	std::unordered_map<int, std::string> mapaso;

	mapaso[0] = "a";
	mapaso[0] = "b"; // revisar como stl trata las colisiones (se esta sobreescribiendo)
	mapaso[1] = "c";
	mapaso[3] = "d";
	
	std::cout << mapaso.count(0) << std::endl;
	return 0;
}