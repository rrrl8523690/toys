//
// Created by Handa Wang on 9/26/17.
//

#ifndef JSON_JSONVALUETEST_H
#define JSON_JSONVALUETEST_H

#include "Test.h"
#include "JSON.h"
#include <iostream>

class JSONIntFixture1 : public toy::TestFixture {
public:
	JSONIntFixture1() : json_int_1_(toy::JSON(1)) {}

	toy::JSON json_int_1_;
};

TEST(JSON_INT, JSONIntFixture1) {
	toy::JSON &json = fixture()->json_int_1_;

	EXPECT(json.type() == toy::JSONType::INT);
	EXPECT(json.toString() == "1"); // Test toString()

	toy::JSON copied_json = json;
	EXPECT(copied_json.toString() == "1"); // Test copy constructor

	toy::JSON moved_json = std::move(copied_json); // Test move constructor
	EXPECT(moved_json.toString() == "1");

	moved_json = std::move(json); // Test move operator=
	EXPECT(moved_json.toString() == "1");
}

class JSONStringFixture : public toy::TestFixture {
public:
	JSONStringFixture() : json_string_empty(toy::JSON("")),
	                      json_string_asdf(toy::JSON("asdfghjkl")) {}

	toy::JSON json_string_empty, json_string_asdf;
};

TEST(JSON_STRING, JSONStringFixture) {
	toy::JSON &json1 = fixture()->json_string_empty, &json2 = fixture()->json_string_asdf;
	EXPECT(json1.type() == toy::JSONType::STRING);
	EXPECT(json2.type() == toy::JSONType::STRING);
	EXPECT(json1.toString() == "\"\"");
	EXPECT(json2.toString() == "\"asdfghjkl\"");
	json1 = json2;
	EXPECT(json1.toString() == json2.toString());
	json1 = std::move(json2);
	json2 = json1;
	EXPECT(json1.toString() == json2.toString());
}

TEST(JSON_OBJECT) {
	auto object = toy::JSON::createObject();
	EXPECT(object.type() == toy::JSONType::OBJECT);
	object["key"] = toy::JSON("value");
	EXPECT(object["key"].toString() == "\"value\"");
}

#endif //JSON_JSONVALUETEST_H
