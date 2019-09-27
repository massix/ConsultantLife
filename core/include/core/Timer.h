#pragma once

extern "C" {
	struct ALLEGRO_TIMER;
	struct ALLEGRO_EVENT_SOURCE;
}

namespace cl {
	namespace core {
		class Timer {
		public:
			Timer(float fps);
			virtual ~Timer();
			ALLEGRO_EVENT_SOURCE* getEventSource();
			void start();
			void stop();
			bool operator==(ALLEGRO_TIMER*);
			bool operator==(Timer const&);
			operator ALLEGRO_TIMER*();


		private:
			ALLEGRO_TIMER* timer;
		};
	}
}