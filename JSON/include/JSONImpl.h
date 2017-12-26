//
// Created by Handa Wang on 9/24/17.
//

#ifndef JSON_JSONVALUE_H
#define JSON_JSONVALUE_H


#include <vector>
#include <string>
#include <map>
#include <exception>


namespace toy {
	enum class JSONType {
		INT, DOUBLE, STRING, OBJECT, ARRAY, NUL
	};

	class JSONImpl {
	public:
		~JSONImpl() = default;

		virtual JSONType type() const = 0;

		virtual JSONImpl *copy() const = 0;

		virtual std::string toString() const = 0;
	};

	class JSONIntImpl : public JSONImpl {
	public:
		JSONIntImpl() = default;

		explicit JSONIntImpl(int value);

		JSONType type() const override;

		JSONImpl *copy() const override;

		std::string toString() const override;

	private:
		int value_;
	};

	class JSONStringImpl : public JSONImpl {
	public:
		JSONStringImpl() = default;

		JSONType type() const override;

		JSONImpl *copy() const override;

		explicit JSONStringImpl(std::string value);

		std::string toString() const override;

	private:
		std::string value_;
	};
}


#endif //JSON_JSONVALUE_H
