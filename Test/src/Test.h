//
// Created by Handa Wang on 9/22/17.
//

#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <functional>

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
		Test() = delete;

		static std::string boldText(const std::string &text);

		static std::string coloredText(const std::string &text, TextColor textColor = TextColor::DEFAULT,
		                               BackgroundColor backgroundColor = BackgroundColor::DEFAULT);


		static void fail(const std::string &filePath, int lineNumber, const std::string &msg);

		static void expect(bool condition, const std::string &fileName, int lineNumber, const std::string &msg);

	private:
//		std::string get
	protected:
		static int _nTestCase, _nPassedCase;
	};

}

#define EXPECT(condition) \
  do {\
    expect(condition, __FILE__, __LINE__, std::string(#condition) + " not satisfied.");\
  } while (0)


#endif //TEST_TEST_H
