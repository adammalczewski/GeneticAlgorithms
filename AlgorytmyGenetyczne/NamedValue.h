#pragma once
#include <string>

namespace excel {
	
	class NamedValue {
	public:

		NamedValue(std::string name, int value) {
			this->name = name;
			this->value = value;
		}

		std::string name;
		int value;

	};

}
