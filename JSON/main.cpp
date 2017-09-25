#include <iostream>
#include "src/JSONValue.h"

int main() {
	std::cout << "Hello, World!" << std::endl;
	toy::JSONString a(L"sdfa");
	toy::JSONString b("sdfa");
	toy::JSONString c(std::string("sdfa"));
	return 0;
}