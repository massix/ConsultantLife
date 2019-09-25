#pragma once

#include <core_export.h>
#include <core/EventReceiver.h>
#include <vector>

namespace cl {
	namespace core {
		class CORE_EXPORT EventSender {
		public:
			virtual void registerReceiver(EventReceiver const& receiver) = 0;
			virtual void fireEvent() = 0;

		private:
			std::vector<EventReceiver const&> receivers;
		};
	}
}