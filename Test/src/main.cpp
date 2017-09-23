#include <iostream>
#include "Test.h"

class Test1 : public toy::Test {
public:
	virtual void testCases() {
		EXPECT(1 == 1);
//		EXPECT_EQ(1, 2);
	}

	static void run() {
		auto t = new Test1();
		t->testCases();
		summary();
	}
};

TEST(Test2) {
	int a = 1, b = 2;
	EXPECT(1 != 3);
	EXPECT(a != b);
};

int main() {
	using namespace std;
	using namespace toy;
//	cerr << "!!" << endl;
//	cerr << Test::coloredText("hello world", TextColor::RED, BackgroundColor::GREEN) << endl;
//	cerr << "!!" << endl;
	RUN_TEST(Test2);
	return 0;
}