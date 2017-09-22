#include <iostream>
#include "Test.h"

int main() {
	using namespace std;
	using namespace toy;
	cerr << "!!" << endl;
	cerr << Test::coloredText("hello world", TextColor::RED, BackgroundColor::GREEN) << endl;
	cerr << "!!" << endl;
	return 0;
}