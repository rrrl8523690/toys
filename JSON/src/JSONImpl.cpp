//
// Created by Handa Wang on 9/24/17.
//

#include "JSONImpl.h"

namespace toy {
	JSONIntImpl::JSONIntImpl(int value) {
		value_ = value;
	}

	JSONType JSONIntImpl::type() const {
		return JSONType::INT;
	}

	JSONImpl *JSONIntImpl::copy() const {
		return new JSONIntImpl(value_);
	}

	std::string JSONIntImpl::toString() const {
		return std::to_string(value_);
	}

	JSONType JSONStringImpl::type() const {
		return JSONType::STRING;
	}

	JSONImpl *JSONStringImpl::copy() const {
		return new JSONStringImpl(value_);
	}

	JSONStringImpl::JSONStringImpl(std::string value) {
		value_ = std::move(value);
	}

	std::string JSONStringImpl::toString() const {
		return "\"" + value_ + "\"";
	}
}
