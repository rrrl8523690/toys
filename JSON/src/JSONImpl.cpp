//
// Created by Handa Wang on 9/24/17.
//

#include "../include/JSONImpl.h"

namespace toy {
	namespace json_detail {
		void JSONImpl::throwTypeErrorException(const std::string &methodName) const {
			throw std::logic_error("Wrong Type when calling " + methodName + "\n");
		}

		int *JSONImpl::getInt() {
			throwTypeErrorException(__FUNCTION__);
			return nullptr;
		}

		double *JSONImpl::getDouble() {
			throwTypeErrorException(__FUNCTION__);
			return nullptr;
		}

		JSONImpl::string_t *JSONImpl::getString() {
			throwTypeErrorException(__FUNCTION__);
			return nullptr;
		}

		std::vector<JSON> *JSONImpl::getArray() {
			throwTypeErrorException(__FUNCTION__);
			return nullptr;
		};

		std::map<JSONImpl::string_t, JSON> *JSONImpl::getMap() {
			throwTypeErrorException(__FUNCTION__);
			return nullptr;
		};

		int *JSONIntImpl::getInt() {
			return &_val;
		}
	}
}
