#include <iostream>
#include "JSONValue.h"
#include "JSONValueTest.h"

int main() {
	RUN_ALL_TESTS();
	toy::JSONString a(L"sdfa");
	toy::JSONString b("sdfa");
	toy::JSONString c(std::string("sdfa"));
	return 0;
}