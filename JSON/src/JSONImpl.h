//
// Created by Handa Wang on 9/24/17.
//

#ifndef JSON_JSONVALUE_H
#define JSON_JSONVALUE_H


#include <vector>
#include <string>
#include <map>
#include <exception>
#include "JSON.h"


// TODO: RE-design!!!!!
namespace toy {
	enum class JSONType {
		NUL, INT, DOUBLE, STRING, ARRAY, OBJECT
	};

	class JSON;
	namespace json_detail {

		class JSONImpl {
		public:
			using string_t = std::wstring;

			virtual ~JSONImpl() = default;

			JSONType type() const {
				return _type;
			}

			virtual int *getInt();

			virtual double *getDouble();

			virtual JSONImpl::string_t *getString();

			virtual std::vector<JSON> *getArray();

			virtual std::map<JSONImpl::string_t, JSON> *getMap();

		protected:
			JSONImpl() : _type(JSONType::NUL) {}

			JSONType _type;
		private:
			void throwTypeErrorException(const std::string &methodName) const;

		};

		class JSONIntImpl : public JSONImpl {
		public:
			JSONIntImpl() { _type = JSONType::INT; }

			JSONIntImpl(int val) : _val(val) { _type = JSONType::INT; }

			int *getInt();

		private:
			int _val;
		};
	}
}


#endif //JSON_JSONVALUE_H
