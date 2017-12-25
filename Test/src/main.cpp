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

class Fixture1 : public toy::TestFixture {
public:
	void init() {
		x = 5;
	}

	int x;
private:
};

TEST(Test3, Fixture1) {
	EXPECT(_fixture->x == 5);
	EXPECT(_fixture->x != 6);
}

TEST(Test4, Fixture1) {
	EXPECT(_fixture->x == 6);
	EXPECT(_fixture->x != 6);
}

int main() {
	using namespace std;
	using namespace toy;
//	cerr << "!!" << endl;
//	cerr << Test::coloredText("hello world", TextColor::RED, BackgroundColor::GREEN) << endl;
//	cerr << "!!" << endl;

	RUN_ALL_TESTS();
	return 0;
}