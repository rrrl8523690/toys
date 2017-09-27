//
// Created by Handa Wang on 9/24/17.
//

#ifndef JSON_JSONVALUE_H
#define JSON_JSONVALUE_H


#include <vector>
#include <string>

namespace toy {
	class JSONValue {
	public:
		using string_t = std::wstring;

//		JSONValue(const JSONValue &other) = delete;


		// The derived classes are responsible to delete _valuePtr.
		virtual ~JSONValue() {
		}

		enum class Type {
			NUL, INT, DOUBLE, STRING, ARRAY, OBJECT
		};

		Type type() const {
			return _type;
		}

		JSONValue &operator=(JSONValue value) {
			reset(std::move(value));
			return *this;
		}

		virtual int *getInt() {
			return nullptr;
		}

		virtual double *getDouble() {
			return nullptr;
		}

		virtual std::vector<JSONValue> *getArray() {
			return nullptr;
		}

	protected:
		JSONValue() = default;

		Type _type;
		void *_valuePtr;
	private:
		void reset(JSONValue value) {
			this->swap(value);
		}

		void swap(JSONValue &other) {
			std::swap(_type, other._type);
			std::swap(_valuePtr, other._valuePtr);
		}
	};

	class JSONInt : public JSONValue {
	public:
		JSONInt(int val) {
			_type = Type::INT;
			_valuePtr = new int(val);
		}

		~JSONInt() {
			delete static_cast<int *>(_valuePtr);
		}
	};

	class JSONDouble : public JSONValue {
	public:
		JSONDouble(double val) {
			_type = Type::DOUBLE;
			_valuePtr = new double(val);
		}

		~JSONDouble() {
			delete static_cast<double *>(_valuePtr);
		}
	};

	class JSONString : public JSONValue {
	public:
		JSONString(string_t str) {
			_type = Type::STRING;
			_valuePtr = new string_t(move(str));
		}

		template<typename Char>
		JSONString(const Char *str) {
			_type = Type::STRING;
			auto tempStr = std::basic_string<Char>(str);
			_valuePtr = new string_t(tempStr.begin(), tempStr.end());
		}

		template<typename String>
		JSONString(String str) {
			_type = Type::STRING;
			_valuePtr = new string_t(std::begin(str), std::end(str));
		}

		~JSONString() {
			delete static_cast<string_t *>(_valuePtr);
		}
	};

	class JSONArray : public JSONValue {
	public:
		JSONArray(std::vector<JSONValue> array) {
			_type = Type::ARRAY;
			_valuePtr = new std::vector<JSONValue>(std::move(array));
		}

		~JSONArray() {
			delete static_cast<std::vector<JSONValue> *> (_valuePtr);
		}
	};

	// TODO: implement JSONObject
//	class JSONObject :
}


#endif //JSON_JSONVALUE_H
