//
// Created by Handa Wang on 9/24/17.
//

#ifndef JSON_JSON_H
#define JSON_JSON_H


#include <istream>
#include "JSONImpl.h"

namespace toy {
	enum class JSONType {
		INT, DOUBLE, STRING, OBJECT, ARRAY, NUL
	};

	class JSON {
	public:
		JSON(const JSON &other);

		JSON(JSON &&other) = default;

		JSON &operator=(const JSON &other);

		JSON &operator=(JSON &&other) = default;

		~JSON() = default;

		std::string toString();

	private:
		JSON(JSONImpl *json_impl);

		std::unique_ptr<JSONImpl> json_impl_;
	};

}


#endif //JSON_JSON_H
