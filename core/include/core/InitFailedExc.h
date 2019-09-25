#pragma once

#include <exception>

namespace cl {
	namespace core {
		struct InitializationFailed : public std::exception {
			InitializationFailed(const char* msg) : std::exception(msg) {}
		};
	}
}