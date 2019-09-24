#pragma once

#include <core_export.h>
#include <string>
#include <sstream>

namespace cl {
	namespace core {
		struct CORE_EXPORT Position {
			int32_t x;
			int32_t y;

			Position(int32_t x, int32_t y) {
				this->x = x;
				this->y = y;
			};

			Position() {
				this->x = 0;
				this->y = 0;
			}

			operator std::string() const {
				std::ostringstream stream;
				stream << "x: " << this->x << " y: " << this->y;
				return stream.str();
			}
		};

		struct CORE_EXPORT Size {
			uint32_t width;
			uint32_t height;

			Size(uint32_t width, uint32_t height) {
				this->width = width;
				this->height = height;
			};

			Size() {
				this->width = 0;
				this->height = 0;
			};

			operator std::string() const {
				std::ostringstream stream;
				stream << "width: " << this->width << " height: " << this->height;
				return stream.str();
			}
		};
	}
}
