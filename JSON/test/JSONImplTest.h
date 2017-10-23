//
// Created by Handa Wang on 9/26/17.
//

#ifndef JSON_JSONVALUETEST_H
#define JSON_JSONVALUETEST_H

#include "Test.h"
#include "JSONImpl.h"

TEST(JSON_VALUE) {
	toy::JSONInt intVal(25);
	EXPECT(intVal.type() == toy::JSONValue::Type::INT);

	toy::JSONDouble doubleVal(25.0);
	EXPECT(doubleVal.type() == toy::JSONValue::Type::DOUBLE);

	toy::JSONString strVal("A json string");
	EXPECT(strVal.type() == toy::JSONValue::Type::STRING);

}

#endif //JSON_JSONVALUETEST_H
