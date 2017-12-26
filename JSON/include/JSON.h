//
// Created by Handa Wang on 9/24/17.
//

#ifndef JSON_JSON_H
#define JSON_JSON_H


#include <istream>
#include "JSONImpl.h"

namespace toy {


	class JSON {
	public:
		static JSON createInt(int value);
		static JSON createString(std::string value);

		JSON(const JSON &other);

		JSON(JSON &&other) = default;

		JSON &operator=(const JSON &other);

		JSON &operator=(JSON &&other) = default;

		~JSON() = default;

		JSONType type() const;

		std::string toString();

	private:
		JSON(JSONImpl *json_impl);

		std::unique_ptr<JSONImpl> json_impl_;
	};

}


#endif //JSON_JSON_H
