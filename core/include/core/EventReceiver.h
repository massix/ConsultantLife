#pragma once

#include <core_export.h>

namespace cl {
	namespace core {
		class CORE_EXPORT EventReceiver {
		public:
			virtual void eventCallback() = 0;
		};
	}
}