//
// Created by Handa Wang on 9/24/17.
//

#include "JSONImpl.h"

namespace toy {
	JSONIntImpl::JSONIntImpl(int value) {
		value_ = value;
	}

	JSONImpl *JSONIntImpl::copy() const {
		return new JSONIntImpl(value_);
	}

	std::string JSONIntImpl::toString() {
		return std::to_string(value_);
	}

}
