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
	class JSONImpl {
	public:
		~JSONImpl() = default;

		virtual JSONImpl *copy() const = 0;

		virtual std::string toString() = 0;
	};
	namespace {
		class JSONIntImpl : public JSONImpl {
		public:
			JSONIntImpl() = default;

			JSONIntImpl(int value);

			virtual JSONImpl *copy() const override;

			virtual std::string toString() override;

		private:
			int value_;
		};
	}
}


#endif //JSON_JSONVALUE_H
