//
// Created by Handa Wang on 9/22/17.
//

#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <functional>
#include <vector>
#include <string>

namespace toy {
	// Colors only supported in UNIX
	enum class TextColor {
		RED = 31, GREEN = 32, BLUE = 34, YELLOW = 33, BLACK = 30, WHITE = 37, RESET = 0, DEFAULT = -1
	};

	enum class BackgroundColor {
		RED = 41, GREEN = 42, BLUE = 44, YELLOW = 43, BLACK = 40, WHITE = 47, RESET = 0, DEFAULT = -1
	};

	class Test {
	public:

		void summary();

		static std::string boldText(const std::string &text);

		static std::string coloredText(const std::string &text, TextColor textColor = TextColor::DEFAULT,
		                               BackgroundColor backgroundColor = BackgroundColor::DEFAULT);

		void fail(const std::string &filePath, int lineNumber, const std::string &msg);

		void expect(bool condition, const std::string &fileName, int lineNumber, const std::string &msg);

	private:

	protected:
		int _nTestCase, _nPassedCase;
		std::string _name;
	};

	std::vector<std::function<void()>> &allTests();
}

#define TEST_CLASS(NAME) TestClass_##NAME

#define TEST(NAME) \
class TEST_CLASS(NAME) : public toy::Test \
{ \
public: \
  TEST_CLASS(NAME) () { \
    _nTestCase = 0; \
    _nPassedCase = 0; \
    _name = #NAME; \
  } \
  void run() { \
    testCases(); \
    summary(); \
  } \
  void testCases(); \
private: \
  static int _hack; \
}; \
int TEST_CLASS(NAME)::_hack = (toy::allTests().push_back([]() { TEST_CLASS(NAME)().run(); }), 0); \
void TEST_CLASS(NAME)::testCases()

#define RUN_TEST(NAME) \
do { \
  TEST_CLASS(NAME)().run(); \
} while (0)

#define RUN_ALL_TESTS() \
do { \
  for (const auto &test : toy::allTests()) { \
    test(); \
  } \
} while (0)


#define EXPECT(condition) \
do { \
  expect(condition, __FILE__, __LINE__, std::string(#condition) + " not satisfied."); \
} while (0)


#endif //TEST_TEST_H
