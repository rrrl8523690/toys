//
// Created by Handa Wang on 9/22/17.
//

#include <sstream>
#include "Test.h"

namespace toy {
	std::string Test::coloredText(const std::string &text, TextColor textColor, BackgroundColor backgroundColor) {
		std::ostringstream ss;
		ss << "\033[" << static_cast<int>(textColor) << "m";
		ss << "\033[" << static_cast<int>(backgroundColor) << "m";
		ss << text;
		ss << "\033[" << static_cast<int>(TextColor::RESET) << "m";
		ss << "\033[" << static_cast<int>(BackgroundColor::RESET) << "m";
		return ss.str();
	}

	void Test::expect(bool condition) {
		++_nTestCase;
		if (condition) { // ok
			++_nPassedCase;
		} else { // fail

		}
	}

	int Test::_nTestCase = 0, Test::_nPassedCase = 0;
}