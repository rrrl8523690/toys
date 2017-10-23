//
// Created by Handa Wang on 9/24/17.
//

#ifndef JSON_JSONVALUE_H
#define JSON_JSONVALUE_H


#include <vector>
#include <string>
#include <map>


// TODO: RE-design!!!!!
namespace toy {
	class JSONImpl {
	public:
		using string_t = std::wstring;

//		JSONValue(const JSONValue &other) = delete;


		// The derived classes are responsible to delete _valuePtr.
		virtual ~JSONValue() = default;

		enum class Type {
			NUL, INT, DOUBLE, STRING, ARRAY, OBJECT
		};

		Type type() const {
			return _type;
		}

	protected:
		JSONImpl() = default;
		Type _type;
	};

}


#endif //JSON_JSONVALUE_H
