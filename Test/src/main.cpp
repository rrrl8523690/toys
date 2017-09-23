#include <iostream>
#include "Test.h"

TEST(Test1) {
	int a = 1, b = 2;
	EXPECT(1 == 3);
	EXPECT(a != b);
}

TEST(Test2) {
	EXPECT(2 == 2);
}

int main() {
	using namespace std;
	using namespace toy;
//	cerr << "!!" << endl;
//	cerr << Test::coloredText("hello world", TextColor::RED, BackgroundColor::GREEN) << endl;
//	cerr << "!!" << endl;
	RUN_TEST(Test1);
	RUN_TEST(Test2);
	return 0;
}