#include <iostream>
#include "Test.h"

class Test1 : public toy::Test {
public:
	static void run() {
		EXPECT(1 == 2);
//		EXPECT_EQ(1, 2);
	}
};

int main() {
	using namespace std;
	using namespace toy;
//	cerr << "!!" << endl;
//	cerr << Test::coloredText("hello world", TextColor::RED, BackgroundColor::GREEN) << endl;
//	cerr << "!!" << endl;
	Test1::run();
	return 0;
}