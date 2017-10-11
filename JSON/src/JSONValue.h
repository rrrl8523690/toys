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
	class JSONValue {
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

		virtual string_t *getString() {
			return nullptr;
		}

		virtual std::vector<JSONValue *> *getArray() {
			return nullptr;
		}

		virtual std::map<string_t, JSONValue *> *getMap() {
			return nullptr;
		};

	protected:
		JSONValue() = default;

		Type _type;
		void *_valuePtr;
	private:
		void reset(JSONValue *value) {
			std::swap(this->_type, value->_type);
			std::swap(this->_valuePtr, value->_valuePtr);
		}

	};

	class JSONInt : public JSONValue {
	public:
		explicit JSONInt(int val) {
			_type = Type::INT;
			_valuePtr = new int(val);
		}

		~JSONInt() override {
			delete getInt();
		}

		int *getInt() override {
			return static_cast<int *>(_valuePtr);
		}
	};

	class JSONDouble : public JSONValue {
	public:
		explicit JSONDouble(double val) {
			_type = Type::DOUBLE;
			_valuePtr = new double(val);
		}

		~JSONDouble() override {
			delete getDouble();
		}

		double *getDouble() override {
			return static_cast<double *>(_valuePtr);
		}
	};

	class JSONString : public JSONValue {
	public:
		explicit JSONString(string_t str) {
			_type = Type::STRING;
			_valuePtr = new string_t(move(str));
		}

		template<typename Char>
		explicit JSONString(const Char *str) {
			_type = Type::STRING;
			auto tempStr = std::basic_string<Char>(str);
			_valuePtr = new string_t(tempStr.begin(), tempStr.end());
		}

		template<typename String>
		explicit JSONString(String str) {
			_type = Type::STRING;
			_valuePtr = new string_t(std::begin(str), std::end(str));
		}

		~JSONString() override {
			delete getString();
		}

		string_t *getString() override {
			return static_cast<string_t *>(_valuePtr);
		}
	};

	class JSONArray : public JSONValue {
	public:
		explicit JSONArray(std::vector<JSONValue *> array) {
			_type = Type::ARRAY;
			_valuePtr = new std::vector<JSONValue *>(std::move(array));
		}

		~JSONArray() override {
			auto array = getArray();
			for (auto &elem : (*array)) {
				delete elem;
			}
			delete array;
		}

		std::vector<JSONValue *> *getArray() override {
			return static_cast<std::vector<JSONValue *> *> (_valuePtr);
		}
	};

	// TODO: implement JSONObject
	class JSONObject : public JSONValue {
	public:
		JSONObject(std::map<string_t, JSONValue> map) {
			_type = Type::OBJECT;
			_valuePtr = new std::map<string_t, JSONValue>(std::move(map));
		}

		~JSONObject() {
			delete getMap();
		}

		std::map<string_t, JSONValue> *getMap() override {
			return static_cast<std::map<string_t, JSONValue> *>(_valuePtr);
		}
	};
}


#endif //JSON_JSONVALUE_H
