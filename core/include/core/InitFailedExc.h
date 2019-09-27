#pragma once

#include <core_export.h>
#include <exception>

namespace cl {
	namespace core {
		struct CORE_EXPORT InitializationFailed : public std::exception {
			InitializationFailed(const char* msg) : std::exception(msg) {}
		};
	}
}