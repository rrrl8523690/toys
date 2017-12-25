//
// Created by Handa Wang on 9/24/17.
//

#ifndef JSON_JSON_H
#define JSON_JSON_H


#include <istream>
#include "JSONImpl.h"

namespace toy {
	namespace json_detail {
		class JSONImpl;
	}
	class JSON {
	public:
	private:
		// TODO: do we need this?
//		void typeCheck(toy::JSONType expectedType) const;

		std::unique_ptr<json_detail::JSONImpl> _impl;

	};
}


#endif //JSON_JSON_H
