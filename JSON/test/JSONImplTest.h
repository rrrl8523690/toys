//
// Created by Handa Wang on 9/26/17.
//

#ifndef JSON_JSONVALUETEST_H
#define JSON_JSONVALUETEST_H

#include "Test.h"
#include "JSON.h"

class JSONIntFixture1 : public toy::TestFixture {

public:
	JSONIntFixture1() : json_int_1_(toy::JSON::createInt(1)) {}

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

#endif //JSON_JSONVALUETEST_H
