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
		auto nameText = boldText(coloredText("[" + _name + "]", TextColor::WHITE, BackgroundColor::BLUE));
		std::cerr << nameText << " ";
		auto msg = std::to_string(_nPassedCase) + "/" + std::to_string(_nTestCase) + " cases passed.";
		auto textColor = (_nTestCase == _nPassedCase) ? TextColor::GREEN : TextColor::RED;
		auto styledMsg = boldText(coloredText(msg, textColor));
		std::cerr << styledMsg << std::endl;
	}

	void Test::fail(const std::string &filePath, int lineNumber, const std::string &msg) {
		auto nameText = boldText(coloredText("[" + _name + "]", TextColor::WHITE, BackgroundColor::BLUE));
		std::cerr << nameText << " ";
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

	void TestFixture::init() {}

	void TestFixture::cleanUp() {}

	std::vector<std::function<void()>> &allTests() {
		static std::vector<std::function<void()>> allTests_;
		return allTests_;
	}
}

