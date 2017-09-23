//
// Created by Handa Wang on 9/22/17.
//

#include <sstream>
#include <iostream>
#include "Test.h"

namespace toy {
	std::string Test::coloredText(const std::string &text, TextColor textColor, BackgroundColor backgroundColor) {
		std::ostringstream ss;
		if (textColor != TextColor::DEFAULT) {
			ss << "\033[" << static_cast<int>(textColor) << "m";
		}
		if (backgroundColor != BackgroundColor::DEFAULT) {
			ss << "\033[" << static_cast<int>(backgroundColor) << "m";
		}
		ss << text;
		// Text and background share the same RESET code.
		ss << "\033[" << static_cast<int>(TextColor::RESET) << "m";
		return ss.str();
	}

	std::string Test::boldText(const std::string &text) {
		return "\033[1m" + text + "\033[21m";
	}

	void Test::summary() {
		auto msg = std::to_string(_nPassedCase) + "/" + std::to_string(_nTestCase) + " cases passed.";
		auto styledMsg = boldText(coloredText(msg, TextColor::GREEN));
		std::cerr << styledMsg << std::endl;
	}

	void Test::fail(const std::string &filePath, int lineNumber, const std::string &msg) {
		auto fileName = filePath.substr(filePath.find_last_of("/") + 1);
		auto resultMsg =
						boldText(coloredText("ERROR at " + fileName + "[" + std::to_string(lineNumber) + "]:", TextColor::RED,
						                     BackgroundColor::GREEN)) + " " + msg;
		std::cerr << resultMsg << std::endl;
	}

	void Test::expect(bool condition, const std::string &fileName, int lineNumber, const std::string &msg) {
		++_nTestCase;
		if (condition) { // ok
			++_nPassedCase;
		} else { // fail
			fail(fileName, lineNumber, msg);
		}
	}

	int Test::_nTestCase = 0, Test::_nPassedCase = 0;
}


