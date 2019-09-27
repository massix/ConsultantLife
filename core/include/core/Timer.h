#pragma once
#include <core_export.h>

extern "C" {
	struct ALLEGRO_TIMER;
	struct ALLEGRO_EVENT_SOURCE;
}

namespace cl {
	namespace core {
		class CORE_EXPORT Timer {
		public:
			Timer(float fps);
			virtual ~Timer();
			ALLEGRO_EVENT_SOURCE* getEventSource();
			void start();
			void stop();
			bool isRunning();
			bool operator==(ALLEGRO_TIMER*);
			bool operator==(Timer const&);
			operator ALLEGRO_TIMER*();


		private:
			bool running;
			ALLEGRO_TIMER* timer;
		};
	}
}