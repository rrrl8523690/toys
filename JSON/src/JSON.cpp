//
// Created by Handa Wang on 9/24/17.
//

#include <iostream>
#include <cassert>
#include "JSON.h"

namespace toy {
	JSON::JSON(int value) {
		json_impl_.reset(new JSONIntImpl(value));
	}

	JSON::JSON(std::string value) {
		json_impl_.reset(new JSONStringImpl(std::move(value)));
	}

	JSON::JSON(JSONType type) {
		switch (type) {
			case JSONType::INT:
				json_impl_.reset(new JSONIntImpl());
				break;
			case JSONType::STRING:
				json_impl_.reset(new JSONStringImpl());
				break;
			case JSONType::OBJECT:
				json_impl_.reset(new JSONObjectImpl());
				break;
			default:
				break;
				// TODO: add
		}
	}

	JSON::JSON(const JSON &other) {
		json_impl_.reset(other.json_impl_->copy());
	}

	JSON::JSON(JSON &&other) noexcept {
		json_impl_ = std::move(other.json_impl_);
	}

	JSON &JSON::operator=(const JSON &other) {
		if (json_impl_ && other.json_impl_ && type() == other.type()) {
			json_impl_->forceAssign(other.json_impl_.get());
		} else {
			json_impl_.reset(other.json_impl_->copy());
		}
		return *this;
	}

	JSON &JSON::operator=(JSON &&other) noexcept {
		json_impl_ = std::move(other.json_impl_);
		return *this;
	}

	JSONType JSON::type() const {
		return json_impl_->type();
	}

	std::string JSON::toString() {
		return json_impl_->toString();
	}

	JSON &JSON::operator[](const std::string &key) {
		if (type() != JSONType::OBJECT) {
			throw std::logic_error("Not a json object");
		}
		auto json_object_impl = dynamic_cast<JSONObjectImpl *>(json_impl_.get());
		if (!json_object_impl->map()[key]) {
			json_object_impl->map()[key].reset(new JSON());
		}
		return *(json_object_impl->map()[key]);
	}

	JSONIntImpl::JSONIntImpl() : value_(0) {
	}

	JSONIntImpl::JSONIntImpl(int value) : value_(value) {
	}

	JSONType JSONImpl::type() const {
		return JSONType::UNDEFINED;
	}

	void JSONIntImpl::init(int value) {
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

	void JSONIntImpl::forceAssign(const JSONImpl *other) {
		init(dynamic_cast<const JSONIntImpl *>(other)->value_);
	}

	void JSONIntImpl::appendAsString(std::string &buffer) const {
		buffer += toString();
	}

	void JSONStringImpl::init(std::string value) {
		value_ = std::move(value);
	}

	JSONType JSONStringImpl::type() const {
		return JSONType::STRING;
	}

	JSONImpl *JSONStringImpl::copy() const {
		return new JSONStringImpl(value_);
	}

	JSONStringImpl::JSONStringImpl(std::string value) {
		init(std::move(value));
	}

	void JSONStringImpl::appendAsString(std::string &buffer) const {
		buffer += toString();
	}

	std::string JSONStringImpl::toString() const {
		return "\"" + value_ + "\"";
	}

	void JSONStringImpl::forceAssign(const JSONImpl *other) {
		init(dynamic_cast<const JSONStringImpl *>(other)->value_);
	}

	void JSONObjectImpl::init(const std::map<std::string, std::unique_ptr<toy::JSON>> &value) {
		value_.clear();
		for (auto &pair : value) {
			value_[pair.first].reset(new JSON(*pair.second));
		}
	}

	JSONObjectImpl::JSONObjectImpl(const std::map<std::string, std::unique_ptr<JSON>> &value) {
		init(value);
	}

	JSONObjectImpl::JSONObjectImpl(std::map<std::string, std::unique_ptr<JSON>> &&value) {
		value_ = std::move(value);
	}

	std::map<std::string, std::unique_ptr<toy::JSON>> &JSONObjectImpl::map() {
		return value_;
	}

	JSONType JSONObjectImpl::type() const {
		return JSONType::OBJECT;
	}

	JSONImpl *JSONObjectImpl::copy() const {
		return new JSONObjectImpl(value_);
	}

	void JSONObjectImpl::appendAsString(std::string &buffer) const {
		buffer += "{";
		bool first = true;
		for (const auto &pair : value_) {
			if (!first) {
				buffer += ",";
			}
			first = false;
			buffer += "\"" + pair.first + "\"";
			buffer += ":";
			pair.second->json_impl_->appendAsString(buffer);
		}
		buffer += "}";
	}

	std::string JSONObjectImpl::toString() const {
		std::string result;
		appendAsString(result);
		return result;
	}

	void JSONObjectImpl::forceAssign(const JSONImpl *other) {
		init(dynamic_cast<const JSONObjectImpl *>(other)->value_);
	}
}