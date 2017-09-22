//
// Created by Handa Wang on 9/22/17.
//

#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <functional>

namespace toy {
	enum class TextColor {
		RED = 31, GREEN = 32, BLUE = 34, YELLOW = 33, BLACK = 30, WHITE = 37, RESET = 0
	};

	enum class BackgroundColor {
		RED = 41, GREEN = 42, BLUE = 44, YELLOW = 43, BLACK = 40, WHITE = 47, RESET = 0
	};

	class Test {
	public:
		// Colors only supported in UNIX

		static std::string coloredText(const std::string &text, TextColor textColor = TextColor::RESET,
		                               BackgroundColor backgroundColor = BackgroundColor::RESET);

		static void expect(bool condition);

	private:
//		std::string get
		static int _nTestCase, _nPassedCase;
	};

}


#endif //TEST_TEST_H
