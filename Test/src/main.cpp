#include <iostream>
#include "Test.h"

TEST(Test1) {
	int a = 1, b = 2;
	EXPECT(a != b);
	EXPECT(a < 2);
	EXPECT(a < b);
}

TEST(Test2) {
	EXPECT(2 == 2);
}

class A {
public:
	static void p() {
		std::cerr << "!" << std::endl;
	}
};

int main() {
	using namespace std;
	using namespace toy;
//	cerr << "!!" << endl;
//	cerr << Test::coloredText("hello world", TextColor::RED, BackgroundColor::GREEN) << endl;
//	cerr << "!!" << endl;

	RUN_ALL_TESTS();
	return 0;
}