//
// Created by Handa Wang on 9/24/17.
//

#include "JSON.h"

namespace toy {
	JSON JSON::createInt(int value) {
		return JSON(new JSONIntImpl(value));
	}

	JSON::JSON(const JSON &other) {
		json_impl_.reset(other.json_impl_->copy());
	}

	JSON &JSON::operator=(const JSON &other) {
		json_impl_.reset(other.json_impl_->copy());
		return *this;
	}

	JSON::JSON(JSONImpl *json_impl) {
		json_impl_.reset(json_impl);
	}

	JSONType JSON::type() const {
		return json_impl_->type();
	}

	std::string JSON::toString() {
		return json_impl_->toString();
	}
}