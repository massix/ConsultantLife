#pragma once

#include <core_export.h>
#include <functional>
#include <map>
#include <vector>

extern "C" {
	struct ALLEGRO_EVENT_QUEUE;
	typedef unsigned int ALLEGRO_EVENT_TYPE;
	struct ALLEGRO_EVENT_SOURCE;
};


namespace cl {
	namespace core {
		class Event;

		class CORE_EXPORT EventQueue {
		public:
			EventQueue();
			virtual ~EventQueue();
			void registerEventSource(ALLEGRO_EVENT_SOURCE* source);
			void registerForEvent(uint32_t eventType, std::function< void(Event&) > callback);
			void startLoop();
			void endLoop();
			void waitForEvent();
			bool isEmpty();

		private:
			bool looping;
			ALLEGRO_EVENT_QUEUE* eq;
			std::map <uint32_t, std::vector<std::function<void(Event&)>>> receivers;
		};
	}
}